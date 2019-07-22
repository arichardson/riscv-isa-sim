// See LICENSE_CHERI for license details.

reg_t cursor = CS1.base + CS1.offset;

cheri_reg_t temp = CS1;
temp.base = cursor;
temp.length = RS2;
temp.offset = 0;

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
else if (!cc128_is_representable(CS1.sealed, temp.base, temp.length, temp.offset, temp.offset)) {
  CHERI->raise_trap(CAUSE_CHERI_BOUNDS_FAULT, insn.cs1());
}
else {
  WRITE_CD(temp);
}
