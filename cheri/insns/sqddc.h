/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2018 Hesham Almatary <Hesham.Almatary@cl.cam.ac.uk>
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of the
 * DARPA SSITH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


if (!DDC.tag) {
#if DEBUG
  printf("CHERI: Trying to store via untagged DDC register\n");
#endif

  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, (1 << 5) | CHERI_CSR_DDC);
} else if (DDC.sealed) {
#if DEBUG
  printf("CHERI: Trying to store via a sealed DDC register\n");
#endif
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, CHERI_CSR_DDC);
} else if ((DDC.perms & BIT(CHERI_PERMIT_STORE)) != BIT(CHERI_PERMIT_STORE)) {
#if DEBUG
  printf("CHERI: Trying to store with no DDC STORE permissions\n");
#endif
  CHERI->raise_trap(CAUSE_CHERI_PERMIT_STORE_FAULT, (1 << 5) | CHERI_CSR_DDC);
}

reg_t addr = DDC.base + DDC.offset + RS1;
reg_t paddr = CHERI->get_mmu()->translate(addr, 1, STORE);

if (addr + 8 > DDC.base + DDC.length) {
#if DEBUG
  printf("CHERI: Trying to store with wrong bounds\n");
#endif
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, (1 << 5) | CHERI_CSR_DDC);
} else if (addr < DDC.base) {
#if DEBUG
  printf("CHERI: Trying to store with wrong bounds\n");
#endif
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, (1 << 5) | CHERI_CSR_DDC);
} else {

#if DEBUG
  printf("CHERI: storing cap \n");
#endif
  CHERI->get_mmu()->store_cheri_reg(paddr, CD);
  if (CD.tag) {
    CHERI->cheriMem_setTag(addr);
  } else {
    CHERI->cheriMem_clearTag(addr);
  }
}