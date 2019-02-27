// See LICENSE_CHERI for license details.

if (CS1.tag && CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
/* FIXME */
// else if (not exact set offset) WRITE_CD(null_with_addr(CS1.base + RS2));
else {
  cheri_reg_t temp = CS1;
  temp.offset = RS2;
  WRITE_CD(temp);
}
