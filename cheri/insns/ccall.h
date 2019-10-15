// See LICENSE_CHERI for license details.

if (!CS2.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cd());
else if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (!CS2.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cd());
else if (!CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS2.otype != CS1.otype) CHERI->raise_trap(CAUSE_CHERI_TYPE_FAULT, insn.cd());
else if (!(CS2.perms & BIT(CHERI_PERMIT_EXECUTE))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_EXECUTE_FAULT, insn.cd());
else if ((CS1.perms & BIT(CHERI_PERMIT_EXECUTE))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_EXECUTE_FAULT, insn.cs1());
else if (CS2.base + CS2.offset >= CS2.base + CS2.length) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cd());
else {
  #if DEBUG
  printf("CHERI: CCall wants to jump to %lu\n", CS2.offset);
  #endif
  cheri_reg_t temp = PCC;
  temp.offset = CS2.offset;
  SET_SCR(CHERI_SCR_PCC, temp);

  /* IDC */
  //CHERI_STATE.reg_file[0] = CS1;
  //CS1.sealed = 0;
  //CS1.otype = 0;

  /* Set ra to pc + 4 to mimic jr */
  WRITE_REG(1, pc + 4);

  return temp.offset;
}
