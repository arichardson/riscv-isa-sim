// See LICENSE_CHERI for license details.

if (CS1.tag && CS1.sealed()) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  reg_t new_cursor = CS1.base + RS2;
  if (!cheri_is_representable(CS1.sealed(), CS1.base, CS1.length, CS1.cursor, new_cursor)) {
    temp = CHERI_NULL_CAP;
  }
  temp.cursor = new_cursor;
  WRITE_CD(temp);
}
