// See LICENSE_CHERI for license details.

uint64_t cursor = CS1.base + CS1.offset;

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
else if (temp.base < CS1.base) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (temp.base + temp.length > CS1.base + CS1.length) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (!cheri_is_representable(CS1.sealed, temp.base, temp.length, temp.offset)) {
  CHERI->raise_trap(CAUSE_CHERI_BOUNDS_FAULT, insn.cs1());
}
else {
  WRITE_CD(temp);
}
