// See LICENSE_CHERI for license details.

if (CS1.tag && CS1.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
else {
  cheri_reg_t temp = CS1;
  temp.flags = RS2;
  WRITE_CD(temp);
}
