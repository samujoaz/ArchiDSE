/* Copyright (c) 2009, Sergey A. Borshch
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

#ifndef  __CORE_COMMON_H__
#define  __CORE_COMMON_H__
#if defined (__ASSEMBLER__)

/*
 * if __MSP430X2__ defined, __MSP430X__ is defined too
 * so we check for __MSP430X__ only
 */

/* pab 20100724 Disable MSP430X recognition: the required supporting
 * infrastructure has not been integrated into mpsgcc4. */

#if 0 /* defined(__MSP430X__) */
  #if defined(__MSP430X_ADDR_16BIT__)
    #define XBR     br
    #define XCALL   call
    #define XRET    ret
    #define XMOVA   mov
    #define XCMP    cmp
  #else
    #define XBR     bra
    #define XCALL   calla
    #define XRET    reta
    #define XMOVA   mova
    #define XCMP    cmpa
  #endif
  #if defined(__MSP430X_REGS_16BIT__)
    #define XPUSH   pushx.w
    #define XPOP    popx.w
    #define XPUSHM  pushm.w
    #define XPOPM   popm.w
    #define XMOV    movx.w
    .equ    PUSH_BYTES, 2
  #else
    #define XPUSH   pushx.a
    #define XPOP    popx.a
    #define XPUSHM  pushm.a
    #define XPOPM   popm.a
    #define XMOV    movx.a
    .equ    PUSH_BYTES, 4
  #endif
#else
  #define XBR     br
  #define XCALL   call
  #define XRET    ret
  #define XMOV    mov
  #define XCMP    cmp
  #define XPUSH   push
  #define XPOP    pop
  #define XMOVA   mov
  .equ    PUSH_BYTES, 2
#endif

#endif  /* __ASSEMBLER__ */

#endif  /* __CORE_COMMON_H__ */
