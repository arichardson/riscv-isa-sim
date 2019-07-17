// See LICENSE_CHERI for license details.

reg_t cursor = CS1.base + CS1.offset;

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
}
else if (CS1.otype != OTYPE_UNSEALED) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
else if (cursor < CS1.base) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (cursor + RS2 < cursor) {//Check for addition overflow
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (cursor + RS2 > CS1.base + CS1.length) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
/* FIXME */
//else if (!new_cap.exact) CHERI->raise_trap(CAUSE_CHERI_BOUNDS_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.base = CS1.base + CS1.offset;
  temp.length = RS2;
  temp.offset = 0;
  WRITE_CD(temp);
}
