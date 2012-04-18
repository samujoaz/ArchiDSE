#include    "../core_common.inc"
/* ldiv() is the same as __divmodsi4() in libgcc */

	.section .text
	.global ldiv
ldiv:
;; save clobbers first
#if 0 /* defined(__MSP430X__) */
        XPUSHM  #4, r11
#else
        push    r11
        push    r10
        push    r9
        push    r8
#endif
;; mov registers.
        mov     r13, r11	;; denom
        mov     r12, r10
        mov     r15, r13	;; num
        mov     r14, r12
;; divide
        XCALL   #__divmodsi4
;; result is in there already...
;; restore regs and return.
#if 0 /* defined(__MSP430X__) */
        XPOPM   #4, r11
        XRET
#elif defined(__MSP430_SAVE_PROLOGUE__)
        br      #__epilogue_restorer + 4 * 2
#else
        pop     r8
        pop     r9
        pop     r10
        pop     r11
        ret
#endif
