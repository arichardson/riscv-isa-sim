// See LICENSE_CHERI for license details.

uint64_t new_offset = RS2;

if (CS1.tag && CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (!cheri_is_representable(CS1.sealed, CS1.base, CS1.length, new_offset)) {
  cheri_reg_t temp = CHERI_NULL_CAP;
  temp.base = CS1.base;
  temp.offset = new_offset; //Set temp.address = cb_val.base + rt_val
  WRITE_CD(temp);
}
else {
  cheri_reg_t temp = CS1;
  temp.offset = new_offset;
  WRITE_CD(temp);
}
