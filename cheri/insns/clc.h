// See LICENSE_CHERI for license details.

reg_t addr  = READ_REG(insn.cs1()) + insn.i_imm();

reg_t paddr = CHERI->get_mmu()->translate(addr, 1, LOAD);

cheri_reg_t cd = CHERI->get_mmu()->load_cheri_reg(paddr);

if (!CHERI->cheriMem_getTag(paddr)) {
#if DEBUG
  printf("CHERI: Memory tag is not set\n");
#endif

  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs2());
} else {
  cd.tag = 1;
  WRITE_CD(cd);
}

