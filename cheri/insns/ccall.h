// See LICENSE_CHERI for license details.

long unsigned int new_pc = CS2.base + CS2.offset;
new_pc &= ~1;

if (!CS2.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cd());
else if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (!CS2.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cd());
else if (!CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS2.otype != CS1.otype) CHERI->raise_trap(CAUSE_CHERI_TYPE_FAULT, insn.cd());
else if (!(CS1.perms & BIT(CHERI_PERMIT_CCALL))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_CCALL_FAULT, insn.cs1());
else if (!(CS2.perms & BIT(CHERI_PERMIT_CCALL))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_CCALL_FAULT, insn.cs2());
else if (!(CS2.perms & BIT(CHERI_PERMIT_EXECUTE))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_EXECUTE_FAULT, insn.cd());
else if ((CS1.perms & BIT(CHERI_PERMIT_EXECUTE))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_EXECUTE_FAULT, insn.cs1());
else if (new_pc < CS2.base) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cd());
else if (new_pc + 2 > CS2.base + CS2.length) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cd()); // 2 needs to be 4 if not compressed
else {
  #if DEBUG
  printf("CHERI: CCall wants to jump to %lu\n", new_pc);
  #endif
  cheri_reg_t CS2_tmp = CS2;
  CS2_tmp.offset = new_pc - CS2.base; //TODO think about overflow and alignment (otherwise this could be unrepresentable)
  SET_SCR(CHERI_SCR_PCC, CS2_tmp);
  set_pc(new_pc);

  /* IDC */
  cheri_reg_t CS1_tmp = CS1;
  CS1_tmp.sealed = false;
  CS1_tmp.otype = -1;
  CHERI_STATE.reg_file[31] = CS1_tmp; //TODO define IDC=31 elsewhere
}
