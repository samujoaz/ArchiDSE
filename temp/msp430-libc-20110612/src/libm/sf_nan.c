/*
 * nanf () returns a nan.
 * Added by Cygnus Support.
 */

#include "fdlibm.h"

	float nanf(
#if 4 <= __GNUC__
const char *tagp
#endif /* 4 <= __GNUC__ */
)
{
	float x;

	SET_FLOAT_WORD(x,0x7fc00000);
	return x;
}

#ifdef _DOUBLE_IS_32BITS
	double nan (
#if 4 <= __GNUC__
const char *tagp
#endif /* 4 <= __GNUC__ */
)
{
	return (double) nanf(
#if 4 <= __GNUC__
          tagp
#endif
);
}

#endif /* defined(_DOUBLE_IS_32BITS) */

