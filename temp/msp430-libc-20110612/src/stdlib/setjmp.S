/* Copyright (C) 2001 Dmitry Diky <diwil@mail.ru>

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
author gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.  */
/*
    2009-01-25 Sergey A. Borshch (sb-sf@users-sourceforge.net)
     - 430X compability added.
     - storage order changed, code improved:
        now: 87 cycles, 76 bytes (430) / 98 cycles, 78 bytes (430X)
        was: 101 cycles, 98 bytes (430) / 120 cycles, 108 bytes (430X)
*/

/*
extern int setjmp(jmp_buf __jmpb);
extern void longjmp(jmp_buf __jmpb, int __ret) __ATTR_NORETURN__;
*/
#include    "../core_common.inc"
	.section .text
	.global	setjmp
	.global longjmp
setjmp:
        XPOP    PUSH_BYTES * 10(r15)        ; save return address and adjust sp
        XMOVA   r1,     PUSH_BYTES * 0(r15) ; stack pointer
        XMOVA   r2,     PUSH_BYTES * 1(r15) ; status register
        XMOVA   r4,     PUSH_BYTES * 2(r15)
        XMOVA   r5,     PUSH_BYTES * 3(r15)
        XMOVA   r6,     PUSH_BYTES * 4(r15)
        XMOVA   r7,     PUSH_BYTES * 5(r15)
        XMOVA   r8,     PUSH_BYTES * 6(r15)
        XMOVA   r9,     PUSH_BYTES * 7(r15)
        XMOVA   r10,    PUSH_BYTES * 8(r15)
        XMOVA   r11,    PUSH_BYTES * 9(r15)
        XMOVA   #0,     r15 ;   return value
        XBR     -PUSH_BYTES(r1)
        
longjmp:
        XMOVA   r15,    r13
        XMOVA   r14,    r15     ; r15 now contains a return value
        XMOVA   @r13+,  r1      ; restore registers
        XMOVA   @R13+,  r2
        XMOVA   @R13+,  r4
        XMOVA   @R13+,  r5
        XMOVA   @R13+,  r6
        XMOVA   @R13+,  r7
        XMOVA   @R13+,  r8
        XMOVA   @R13+,  r9
        XMOVA   @R13+,  r10
        XMOVA   @R13+,  r11
        XBR     @R13            ; jump...
