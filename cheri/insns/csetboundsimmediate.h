// See LICENSE_CHERI for license details.

//fprintf(stderr, "CHERI: set bounds immediate  base 0x%016lx offset 0x%016lx immdeiate 0x%lx length 0x%016lx.\n", CS1.base, CS1.offset, insn.i_imm(), CS1.length);

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
}
else if (CS1.sealed) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset < CS1.base) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset + (insn.i_imm()) < CS1.base + CS1.offset) { //check if the base+offset+immediate overflows or not
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else if (CS1.base + CS1.offset + (insn.i_imm()) > CS1.base + CS1.length) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
else {
  cheri_reg_t temp = CS1;
  temp.base = CS1.base + CS1.offset;
  temp.length = insn.i_imm();
  temp.offset = 0;
  WRITE_CD(temp);
}
