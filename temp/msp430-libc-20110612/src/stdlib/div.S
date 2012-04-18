#include    "../core_common.inc"
/* ldiv() is the same as __divmodsi4() in libgcc */

	.section .text
	.global div
div:
;; save clobbers first
#if 0 /* defined(__MSP430X__) */
        XPUSHM  #2, r11
#else
        push    r11
        push    r10
#endif
;; mov registers.
        mov     r14, r10	;; denom
        mov     r15, r12	;; num
;; divide
        XCALL   #__divmodhi4
        mov     r14, r15
        mov     r12, r14
;; result is in there already...
;; restore regs and return.
#if 0 /* defined(__MSP430X__) */
        XPOPM   #2, r11
        XRET
#elif defined(__MSP430_SAVE_PROLOGUE__)
        br      #__epilogue_restorer + 6 * 2
#else
        pop     r10
        pop     r11
        ret
#endif
