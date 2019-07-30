// See LICENSE_CHERI for license details.

cheri_length_t new_length = insn.i_imm() & 0x0FFF; // remove the sign extension from i_imm

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
}
else if (CS1.sealed) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset < CS1.base) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset + new_length < CS1.base + CS1.offset) { //check if the base+offset+immediate overflows or not
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset + new_length > CS1.base + CS1.length) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else {
  cheri_reg_t temp = CS1;
  temp.base = CS1.base + CS1.offset;
  temp.length = new_length;
  temp.offset = 0;
  WRITE_CD(temp);
}
