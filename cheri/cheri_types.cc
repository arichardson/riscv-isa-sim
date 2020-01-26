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
#include "cheri_types.h"

#include "cheri-compressed-cap/cheri_compressed_cap.h"

struct cap_register cheri_reg_t::cap_lib() const {
  struct cap_register cap;
  cap._cr_cursor       = cursor();
  cap.cr_base          = base();
  cap._cr_top          = top();
  cap.cr_perms         = perms;
  cap.cr_uperms        = uperms;
  cap.cr_otype         = otype;
  cap.cr_flags         = flags;
  cap.cr_reserved      = reserved;
  cap.cr_tag           = tag;
  return cap;
}

void cheri_reg_t::set_cap_lib(const struct cap_register &cap) {
  _cursor  = cap._cr_cursor;
  _base    = cap.cr_base;
  _top     = cap._cr_top;
  perms    = cap.cr_perms;
  uperms   = cap.cr_uperms;
  otype    = cap.cr_otype;
  flags    = cap.cr_flags;
  reserved = cap.cr_reserved;
  tag      = cap.cr_tag;
}

cheri_reg_t::cheri_reg_t(const cheri_reg_inmem_t &inmem, bool _tag) {
  struct cap_register temp;
  decompress_128cap(inmem.pesbt, inmem.cursor, &temp);
  temp.cr_tag = _tag;
  set_cap_lib(temp);
}

cheri_reg_inmem_t cheri_reg_t::inmem() const {
  struct cap_register cap = cap_lib();
  return (cheri_reg_inmem_t) {
    .cursor = cursor(),
    .pesbt = compress_128cap(&cap)
  };
}

void cheri_reg_t::set_bounds(uint64_t new_base, cheri_length_t new_top) {
  reserved = 0;
  struct cap_register cap = cap_lib();
  cc128_setbounds(&cap, new_base, new_top);
  set_cap_lib(cap);
}

void cheri_reg_t::set_cursor(uint64_t new_cursor) {
  reserved = 0;
  if (!cc128_is_representable_new_addr(sealed(), base(), length(), cursor(), new_cursor)) {
    cheri_reg_inmem_t newmem = inmem();
    newmem.cursor = new_cursor;
    *this = cheri_reg_t(newmem, false);
  } else {
    _cursor = new_cursor;
  }
}
#endif
