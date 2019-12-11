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
#ifndef _RISCV_CHERI_H
#define _RISCV_CHERI_H

#include "extension.h"
#include "cheri_trap.h"
#include "cheri-compressed-cap/cheri_compressed_cap.h"
#include "tags.h"

#define DEBUG 0
#define BIT(x) (1ull << (x))
#define MASK(n) ((BIT(n)-1ull))

#define CHERI (static_cast<cheri_t*>(p->get_extension()))
#define CHERI_STATE CHERI->state
#define NUM_CHERI_SCR_REGS 32

#define SCR CHERI->get_scr(insn.chs(), p)
#define PCC CHERI->get_scr(CHERI_SCR_PCC, p)
#define DDC CHERI_STATE.scrs_reg_file[CHERI_SCR_DDC]

#define SET_SCR(index, val) CHERI->set_scr(index, val, p)
#define GET_SCR(index) CHERI->get_scr(index, p)

#ifdef CHERI_MERGED_RF
#define NUM_CHERI_REGS 32

#define CD  STATE.XPR[insn.cd()]
#define CS1 STATE.XPR[insn.cs1()]
#define CS2 STATE.XPR[insn.cs2()]

#define WRITE_CD(val) ({ \
  STATE.XPR.write(insn.cd(), val); \
  if (p->rvfi_dii && (insn.cd() != 0)) { \
    p->rvfi_dii_output.rvfi_dii_rd_wdata = val.base + val.offset; \
    p->rvfi_dii_output.rvfi_dii_rd_addr = insn.cd(); \
  } \
  if(DEBUG) { \
    fprintf(stderr, "x%lu <- t:%u s:%u perms:0x%08x type:0x%016x offset:0x%016lx base:0x%016lx length:0x%1lx %016lx\n", insn.cd(), val.tag, val.sealed, val.perms, val.otype, val.offset, val.base, (uint64_t) (val.length >> 64), (uint64_t) val.length & UINT64_MAX); \
  } \
})
#else/* CHERI_MERGED_RF */

#define NUM_CHERI_REGS 32

#define CD  CHERI_STATE.reg_file[insn.cd()]
#define CS1 CHERI_STATE.reg_file[insn.cs1()]
#define CS2 CHERI_STATE.reg_file[insn.cs2()]

#define WRITE_CD(val) CHERI_STATE.reg_file[insn.cd()] =  val
#endif /* CHERI_MERGED_RF */

#ifdef ENABLE_CHERI128
#define CHERI_CAPSIZE_BYTES 16
#else
#define CHERI_CAPSIZE_BYTES 32
#endif /* ENABLE_CHERI128 */

extern const char *cheri_reg_names[32];

/* 256-bit Caps register format *
 * -------------------------------------------------------------------------
 * | length | base | offset | uperms | perms | S | reserved | otype | Tag  |
 * -------------------------------------------------------------------------
 * |  64    |  64  |   64   |   16   |  15   | 1 |   7     |   24   |  1   |
 * -------------------------------------------------------------------------
 */

struct cheri_state {
  cheri_reg_t reg_file[NUM_CHERI_REGS];

  cheri_reg_t scrs_reg_file[NUM_CHERI_SCR_REGS];
};

typedef struct cheri_state cheri_state_t;

class cheri_t : public extension_t {
 public:

  cheri_t() {
  }

  ~cheri_t() {
  }

  /* Override extension functions */
  void reset();

  void register_insn(insn_desc_t desc);
  mmu_t* get_mmu(void);

  /* Allocate tag_bits memory to cover all memory */
  void create_tagged_memory(size_t memsz);
  void cheriMem_setTag(reg_t addr);
  bool cheriMem_getTag(reg_t addr);
  void cheriMem_clearTag(reg_t addr);

  uint32_t get_clen() {
    return clen;
  };
  reg_t get_ccsr() {
    return ccsr;
  };
  void set_ccsr(reg_t c) {
    ccsr = c;
  };

  bool get_mode() {
    return !!CHERI_STATE.scrs_reg_file[CHERI_SCR_PCC].flags;
  };

  void raise_trap(reg_t trap_code, reg_t trap_reg) {
    set_ccsr((trap_code << 8) | trap_reg);
    throw trap_cheri_trap();
  };

  std::vector<insn_desc_t> get_instructions();
  std::vector<disasm_insn_t*> get_disasms();

  cheri_state_t state;

  void set_scr(int index, cheri_reg_t val, processor_t* proc);

  cheri_reg_t get_scr(int index, processor_t* proc);

 private:
  /* FIXME: For now assume DRAM size is 2GiB, the default for Spike */
  tags_t<bool, (BIT(31) / sizeof(cheri_reg_inmem_t))> mem_tags;
  uint32_t clen = 0;
  reg_t ccsr = 0;
  std::vector<insn_desc_t> instructions;
};

void convertCheriReg(cap_register_t *destination, const cheri_reg_t *source);

void retrieveCheriReg(cheri_reg_t *destination, const cap_register_t *source);

bool cheri_is_representable(uint32_t sealed, uint64_t base, cheri_length_t length, uint64_t offset);

#endif /* _RISCV_CHERI_H */
#endif /* ENABLE_CHERI */
