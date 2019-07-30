// See LICENSE_CHERI for license details.

if (CS1.tag && CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.offset = CS1.offset + insn.i_imm();
  if(!cheri_is_representable(temp.sealed, temp.base, temp.length, temp.offset)) {
    temp = CHERI_NULL_CAP;
    temp.offset = CS1.base + CS1.offset + insn.i_imm();
  }
  WRITE_CD(temp);
}
