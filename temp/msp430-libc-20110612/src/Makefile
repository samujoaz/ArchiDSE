#
# MSP430 libc
#
VERSION = 20101010

# installation prefix (set this if you don't install by hand)
ifndef PREFIX
PREFIX = /msp430/install/dev
endif

# name of target architecture (used for conform naming)

target = msp430

prefix_target = $(PREFIX)/${target}
bindir = $(PREFIX)/bin
includedir = ${prefix_target}/include
libdir = ${prefix_target}/lib

SRC_ROOT := .
BUILD_ROOT = ./Build

override CC = msp430-gcc
override AS = msp430-gcc -x assembler-with-cpp
override AR = msp430-ar
RM = rm
MD = mkdir -p $@

COMMON := $(LIB_OPTIONS)
COMMON += -I$(SRC_ROOT)/../include
COMMON += -I$(SRC_ROOT)

override ASFLAGS = $(COMMON)
ASFLAGS += -Wa,-gdwarf-2
#ASFLAGS += -Wa,-ahlmsd=$(<:.S=.lst)
#ASFLAGS += -v
override CFLAGS = $(COMMON)
override CFLAGS += -Wall -Os -gdwarf-2


# further declaration...
SRCDIRS = stdlib
SRCDIRS += string
SRCDIRS += libm
SRCDIRS += misc

VPATH := $(addprefix $(SRC_ROOT)/, $(SRCDIRS))


all: build
print:
	@$(CC) --print-multi-lib
build: build-multilib
install: install-headers install-multilib
clean:
	${RM} -rf $(BUILD_ROOT)

.PHONY: clean clean-multilib

#------- multilib --------
multilib: build-multilib install-multilib
build-multilib: 
	for i in `$(CC) --print-multi-lib 2>/dev/null`; do \
	  dir=`echo $$i | sed -e 's/;.*$$//'` ; \
	  options=`echo $$i | sed -e 's/[^@]*//' -e 's/@/ -/g'`; \
	  $(MAKE) $(MFLAGS) "MULTILIB_DIR=$$dir" "LIB_OPTIONS=$$options" build-libc build-libm ; \
	done; 

install-multilib:
	for i in `$(CC) --print-multi-lib 2>/dev/null`; do \
	  dir=`echo $$i | sed -e 's/;.*$$//'` ; \
	  mkdir -p $(libdir)/$$dir; \
	  $(MAKE) $(MFLAGS) MULTILIB_DIR="$$dir" install-libc install-libm ; \
	done;

.PHONY: clean-multilib clean-libc clean-libm
clean-multilib:
	for i in `$(CC) --print-multi-lib 2>/dev/null`; do \
	  dir=`echo $$i | sed -e 's/;.*$$//'` ; \
	  $(MAKE) $(MFLAGS) "MULTILIB_DIR=$$dir" clean-libc clean-libm; \
	done; 

#--------------- headers ---------------

install-headers: ins-hr ins-hs ins-hb

ins-hr: $(wildcard $(SRC_ROOT)/../include/*.h) ${includedir}
	install -c -m644 $^/

ins-hs: $(wildcard $(SRC_ROOT)/../include/sys/*.h) ${includedir}/sys
	install -c -m644 $^/

ins-hb: $(wildcard $(SRC_ROOT)/../include/bits/*.h) ${includedir}/bits
	install -c -m644 $^/

#--------------- directories ---------------
$(includedir) $(includedir)/bits $(includedir)/sys $(includedir)/msp430:
	$(MD)
#------------------------------------------------------------------------
#------------------------------------------------------------------------
#------------------------------------------------------------------------
#--------------- libc ------------------------
BUILDDIR=$(BUILD_ROOT)/$(MULTILIB_DIR)
LIBC = $(BUILDDIR)/libc.a

libc_c_sources = abs.c atol.c bsearch.c errno.c labs.c \
malloc.c atoi.c strtol.c strtoul.c \
printf.c uprintf.c sprintf.c vuprintf.c puts.c \
rand.c itoa.c ltoa.c utoa.c ultoa.c

libc_asm_sources = abort.S div.S exit.S ldiv.S setjmp.S \
__bswap_32.S __bswap_64.S

libc_str_sources = \
isascii.c memccpy.c strchr.c strncat.c swab.c \
isblank.c memchr.c strcmp.c strncmp.c toascii.c \
bcmp.c iscntrl.c memcmp.c strcpy.c strncpy.c tolower.c \
bcopy.c isdigit.c memcpy.c strcspn.c strpbrk.c toupper.c \
bzero.c islower.c memmove.c strdup.c strrchr.c \
ffs.c isprint.c memset.c strlcat.c strsep.c \
index.c isspace.c rindex.c strlcpy.c strspn.c \
isalnum.c isupper.c strcasecmp.c strlen.c strstr.c \
isalpha.c isxdigit.c strcat.c strncasecmp.c strtok.c \
ispunct.c

LIBC_OBJS = $(addprefix $(BUILDDIR)/,$(libc_str_sources:.c=.o) $(libc_c_sources:.c=.o) $(libc_asm_sources:.S=.o) )
build-libc: create_libdir $(LIBC)

create_libdir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: %.c
	${CC} -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.S
	${AS} -c $(ASFLAGS) $< -o $@

$(LIBC): $(LIBC_OBJS)
	${AR} rc $@ $?

.PHONY: clean-libc
clean-libc:
	${RM} -f $(LIBC) $(LIBC_OBJS)

install-libc: $(LIBC) $(libdir)/$(MULTILIB_DIR)
	install -c -m644 $^/

#------------------------------------------------------------------------
#-------------- Math & FP libs ---------------

math: build-libm

basic_fp = divsf.c fixsfsi.c floatdisf.c gtsf.c mulsf.c \
addsf.c eqsf.c fixunssfdi.c floatsisf.c lesf.c negsf.c \
cmpsf.c fixsfdi.c fixunssfsi.c gesf.c ltsf.c subsf.c nesf.c

fppfunc	= ef_acos.c ef_hypot.c ef_remainder.c kf_sin.c sf_erf.c sf_isinf.c sf_rint.c \
ef_acosh.c ef_j0.c ef_scalb.c kf_tan.c sf_expm1.c sf_isnan.c sf_scalbn.c \
ef_asin.c ef_j1.c ef_sinh.c sf_asinh.c sf_fabs.c sf_ldexp.c sf_signif.c \
ef_atan2.c ef_jn.c ef_sqrt.c sf_atan.c sf_finite.c sf_log1p.c sf_sin.c \
ef_atanh.c ef_log.c erf_gamma.c sf_cbrt.c sf_floor.c sf_logb.c sf_tan.c \
ef_cosh.c ef_log10.c erf_lgamma.c sf_ceil.c sf_frexp.c sf_modf.c sf_tanh.c \
ef_exp.c ef_pow.c kf_cos.c sf_copysign.c sf_ilogb.c sf_nan.c \
ef_fmod.c ef_rem_pio2.c kf_rem_pio2.c sf_cos.c sf_infinity.c sf_nextafter.c


LIBM = $(BUILDDIR)/libm.a
LIBFP = $(BUILDDIR)/libfp.a
LIBM_OBJS = $(addprefix $(BUILDDIR)/,$(notdir $(fppfunc:%.c=%.o)))
LIBFP_OBJS = $(addprefix $(BUILDDIR)/,$(notdir $(basic_fp:%.c=%.o)))

build-libm: create_libdir $(LIBM) $(LIBFP)

$(LIBM): $(LIBM_OBJS)
	${AR} rc $@ $?
$(LIBFP): $(LIBFP_OBJS)
	${AR} rc $@ $?

install-libm: $(LIBM) $(LIBFP) $(libdir)/$(MULTILIB_DIR)
	install -c -m644 $^/

clean-libm:
	${RM} -f $(LIBM) $(LIBFP) $(LIBM_OBJS) $(LIBFP_OBJS)
