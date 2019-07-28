// See LICENSE_CHERI for license details.

// FIXME: This instruction implementation is not complete

reg_t addr = READ_REG(insn.cs1()) + insn.s_imm();

#ifdef CHERI_MERGED_RF
  cheri_reg_t cs = READ_REG_MERGED(insn.cs2());
#else
  cheri_reg_t cs = CHERI_STATE.reg_file[insn.cs2()];
#endif /* CHERI_MERGED_RF */

reg_t paddr = CHERI->get_mmu()->translate(addr, 1, STORE);

if (cs.tag) {
  CHERI->cheriMem_setTag(paddr);
  /* Zero tag for saving in memory */
  cs.tag = 0;
} else {
#if DEBUG
  printf("CHERI: Trying to store untagged cap register\n");
#endif

  //CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs2());
}

CHERI->get_mmu()->store_cheri_reg(paddr, cs);
