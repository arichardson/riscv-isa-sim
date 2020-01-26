// See LICENSE_CHERI for license details.

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
} else if (CS1.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else if (!CS2.sealed()) {
  WRITE_CD(cheri_reg_t(UINT64_MAX));
} else if (CS2.otype < CS1.base()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
} else if (CS2.otype >= CS1.top()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
} else {
  cheri_reg_t temp = CS1;
  temp.set_cursor(CS2.otype);
  /* CS1 was tagged and CS2.otype in bounds */
  assert(CS1.tag);
  WRITE_CD(temp);
}
