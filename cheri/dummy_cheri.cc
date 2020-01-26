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

#include <config.h>
#ifdef ENABLE_CHERI
#include "cheri.h"
#include "mmu.h"
#include <cstring>
#include <stdio.h>

class dummy_cheri_t : public cheri_t {
 public:
  const char* name() {
    return "cheri";
  }

  dummy_cheri_t() {
    printf("CHERI Extension is Enabled..\n");
  }
};

REGISTER_EXTENSION(cheri, []() {
  return new dummy_cheri_t;
})

void convertCheriReg(cap_register_t *destination, const cheri_reg_t *source) {
  destination->_cr_cursor       = source->cursor;
  destination->cr_base          = source->base;
  destination->_cr_top          = ((cheri_length_t) source->base) + source->length;
  destination->cr_perms         = source->perms;
  destination->cr_uperms        = source->uperms;
  destination->cr_otype         = source->otype;
  destination->cr_flags         = source->flags;
  destination->cr_reserved      = source->reserved;
  destination->cr_tag           = source->tag;
}

void retrieveCheriReg(cheri_reg_t *destination, const cap_register_t *source) {
  destination->cursor = source->_cr_cursor;
  destination->base   = source->cr_base;
  destination->length = source->length();
  destination->perms  = source->cr_perms;
  destination->uperms = source->cr_uperms;
  destination->otype  = source->cr_otype;
  destination->flags  = source->cr_flags;
  destination->reserved = source->cr_reserved;
  destination->tag    = source->cr_tag;
}

bool cheri_is_representable(uint32_t sealed, uint64_t base, cheri_length_t length, uint64_t old_cursor, uint64_t new_cursor) {
#if DEBUG
  fprintf(stderr, "dummy_cheri.cc: Checking representability s:%u base:0x%016lx length:0x%1lx %016lx offset: 0x%016lx\n", sealed, base, (uint64_t)(length >> 64), (uint64_t)(length & UINT64_MAX), offset);
#endif //DEBUG
  return cc128_is_representable_new_addr(sealed, base, length, old_cursor, new_cursor);
}

#endif /*ENABLE_CHERI*/
