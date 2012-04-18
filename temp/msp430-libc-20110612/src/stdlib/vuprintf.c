/* Copyright (c) 2006-2011
 *     Chris Liechti <cliechti@gmx.net>
 *     Peter A. Bigot <pabigot@users.sourceforge.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *
 * Implement a reentrant vuprintf. This function is called by all the different
 * (v)(u)(s)printf functions from the mspgcc libc.
 *
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>


/**
 * Internal state tracking.
 * Saves memory and parameters when compacted in a bit field.
 */
typedef struct
{
  unsigned is_long:1;		///< process a long integer
  unsigned is_signed:1;		///< process a signed number
  unsigned left_align:1;	///< if != 0 pad on right side, else on left side
  unsigned is_alternate_form:1;	///< alternate output
  unsigned emit_hex_prefix:1;	///< emit a prefix 0x
  unsigned fill_zero:1;		///< pad left with zero instead of space
  unsigned uppercase:1;		///< print hex digits in upper case
  char sign_char;		///< character to emit as sign (NUL no emit)
} flags_t;

/** Maximum number of characters in any (numeric) prefix */
#define MAX_PREFIX_CHARS 2

/**
 * Helper function to generate anything that precedes leading zeros.
 *
 * @param write_char    [in] function used to write characters
 * @param flags         [in] flags that specify how the field is aligned
 * @return the number of characters that were written
 */
static int
build_numeric_prefix (char *prefix_buffer, flags_t flags)
{
  char *p = prefix_buffer;
  if (flags.emit_hex_prefix)
    {
      *p++ = '0';
      *p++ = (flags.uppercase ? 'X' : 'x');
    }
  else if (flags.sign_char)
    *p++ = flags.sign_char;
  return p - prefix_buffer;
}

/**
 * Helper function to print strings and fill to the defined width, with the
 * given fill character.
 *
 * @param write_char    [in] function used to write characters
 * @param char_p        [in] the string that is written
 * @param width         [in] field width. 0 is without limitation of width.
 * @param flags         [in] flags that specify how the field is aligned
 * @return the number of characters that were written
 */
static int
print_field (int (*write_char) (int), const char *char_p, unsigned int width,
	     flags_t flags)
{
  int character_count = 0;
  char prefix_buffer[MAX_PREFIX_CHARS];
  int prefix_idx = 0;
  int prefix_len = build_numeric_prefix (prefix_buffer, flags);

  // if right aligned, pad
  if (!flags.left_align)
    {
      char leading_fill = ' ';
      unsigned int len = strlen (char_p);

      if (prefix_len <= width)
	width -= prefix_len;
      else
	width = 0;

      // emit numeric prefix prior to padded zeros
      if (flags.fill_zero)
	{
	  leading_fill = '0';
	  character_count += prefix_len;
	  while (prefix_idx < prefix_len)
	    write_char (prefix_buffer[prefix_idx++]);
	}

      while (len < width)
	{
	  write_char (leading_fill);
	  character_count++;
	  len++;
	}
    }

  // emit any unemitted prefix
  while (prefix_idx < prefix_len)
    {
      character_count++;
      write_char (prefix_buffer[prefix_idx++]);
    }

  // output the buffer contents
  while (*char_p)
    {
      write_char (*char_p);
      char_p++;
      character_count++;
    }
  // if left aligned, pad
  while (character_count < width)
    {
      write_char (' ');
      character_count++;
    }
  // return how many characters have been output
  return character_count;
}


/**
 * Reentrant formated print.
 *
 * Supported '%' format characters:
 * - 's'  const char *  null terminated string as text or "(null)"
 * - 'x'  int/long      hexadecimal '0xnn'
 * - 'X'  int/long      hexadecimal '0XNN'
 * - 'u'  int/long      unsigned decimal
 * - 'd'  int/long      signed decimal
 * - 'i'  int/long      signed decimal
 * - 'p'  pointer       pointer value is printed as "0xnnnn"
 * - 'c'  char          single character
 *
 * Supported flags:
 * - '#'  use alternate form.
 * - 'l'  use long instead of int for numbers
 * - '-'  align left
 * - ' '  prefix non-negative numbers with single space
 * - '+'  prefix non-negative numbers with plus
 * - '0'  pad with '0' instead of ' '
 * - '*'  fetch width from the argument list (unsigned int)
 *
 * The field width (e.g. "%10s") can also be specified.
 *
 * Unsupported are:
 * - Precision (e.g. "%.2s")
 * - octal numbers (format char: o)
 * - float numbers (format char: e E f F g G a A)
 * - write-back character count ("%n")
 *
 * @param write_char    [in] function used to write characters
 * @param format        [in] format string
 * @param args          [in] variable argument list
 * @return the number of characters that were written
 */
/*@-compdef@*/
int
vuprintf (int (*write_char) (int), const char *format, va_list args)
{
  int character_count = 0;
  enum
  { DIRECT, FORMATING } mode = DIRECT;
  unsigned int width = 0;
  flags_t flags;
  char *char_p;
  char character;
  int radix;
  long number;
  char buffer[12];		// used to print numbers: long = 10 + sign + null

  while ((character = *format))
    {				// test and save character
      if (mode == DIRECT)
	{
	  // output characters from the format string directly, except the
	  // '%' sign which changes the mode
	  if (character == '%')
	    {
	      width = 0;
	      memset (&flags, 0, sizeof (flags));
	      mode = FORMATING;
	    }
	  else
	    {
	      goto write_character;
	    }
	}
      else
	{			//FORMATING
	  // process format characters
	  switch (character)
	    {
	      // output '%' itself
	    case '%':
	      goto write_character;	// character is already the %

	      // alternate form flag
	    case '#':
	      flags.is_alternate_form = true;
	      break;

	      // interpret next number as long integer
	    case 'l':
	      flags.is_long = true;
	      break;

	      // left align instead of right align
	    case '-':
	      flags.left_align = true;
	      break;

	      // emit a + before a positive number
	    case '+':
	      flags.sign_char = '+';
	      break;

	      // emit a space before a positive number
	    case ' ':
	      // + overrides space as a flag character
	      if ('+' != flags.sign_char)
		{
		  flags.sign_char = ' ';
		}
	      break;

	      // fetch length from argument list instead of the format
	      // string itself
	    case '*':
	      {
		int val = va_arg (args, int);

		if (val >= 0)
		  width = val;
		else
		  {
		    flags.left_align = true;
		    width = -val;
		  }
		break;
	      }

	      // format field width. zero needs special treatment
	      // as when it occurs as first number it is the
	      // flag to pad with zeroes instead of spaces
	    case '0':
	      // a leading zero means filling with zeros
	      // it must be a leading zero if 'width' is zero
	      // otherwise it is in a number as in "10"
	      if (width == 0)
		{
		  flags.fill_zero = !flags.left_align;
		}
	      /*@fallthrough@ */
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
	      width *= 10;
	      width += *format - '0';
	      break;

	      // placeholder for one character
	    case 'c':
	      character = va_arg (args, int);
	      goto write_character;

	      // placeholder for arbitrary length null terminated
	      // string
	    case 's':
	      char_p = va_arg (args, char *);
	      /* Note: Zero-padding on strings is undefined; it
	       * is legitimate to zero-pad */
	      character_count += print_field (write_char,
					      (char_p !=
					       NULL) ? char_p : "(null)",
					      width, flags);
	      mode = DIRECT;
	      break;

	      // placeholder for an address
	      // addresses are automatically in alternate form and
	      // hexadecimal.
	    case 'p':
	      number = (intptr_t) va_arg (args, void *);
	      number &= UINTPTR_MAX;
	      radix = 16;
	      flags.is_alternate_form = true;
	      goto emit_number;

	      // placeholder for hexadecimal output
	    case 'X':
	      flags.uppercase = true;
	      /*@fallthrough@ */
	    case 'x':
	      radix = 16;
	      goto fetch_number;

	      // placeholder for signed numbers
	    case 'd':
	    case 'i':
	      flags.is_signed = true;
	      /*@fallthrough@ */
	      // placeholder for unsigned numbers
	    case 'u':
	      radix = 10;
	      // label for number outputs including argument fetching
	    fetch_number:
	      if (flags.is_long)
		{
		  number = va_arg (args, long);
		}
	      else
		{
		  if (flags.is_signed)
		    {
		      number = va_arg (args, int);
		    }
		  else
		    {
		      number = va_arg (args, unsigned int);
		    }
		}
	      // label for number outputs excluding argument fetching
	      // 'number' already contains the value
	    emit_number:
	      // only non-zero numbers get hex alternate form
	      if (radix == 16 && 0 != number && flags.is_alternate_form)
		flags.emit_hex_prefix = true;
	      if (flags.is_signed && number < 0)
		{
		  // save sign for radix 10 conversion
		  flags.sign_char = '-';
		  number = -number;
		}

	      // go to the end of the buffer and null terminate
	      char_p = &buffer[sizeof (buffer) - 1];
	      *char_p-- = '\0';
	      // divide and save digits, fill from the lowest
	      // significant digit
	      do
		{
		  int digit = (unsigned long) number % radix;
		  if (digit < 10)
		    {
		      *char_p-- = digit + '0';
		    }
		  else
		    {
		      *char_p-- =
			digit + (flags.uppercase ? ('A' - 10) : ('a' - 10));
		    }
		  number = ((unsigned long) number) / radix;
		}
	      while ((unsigned long) number > 0);

	      // only decimal numbers get signs
	      if (radix != 10)
		{
		  flags.sign_char = 0;
		}

	      // write padded result
	      character_count += print_field (write_char,
					      1 + char_p, width, flags);
	      mode = DIRECT;
	      break;

	    default:
	      /*@fallthrough@ */
	      // entry point for printing a single character
	    write_character:
	      write_char (character);
	      character_count++;
	      mode = DIRECT;
	    }
	}
      format++;
    }
  return character_count;
}
