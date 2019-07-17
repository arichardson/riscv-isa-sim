// See LICENSE_CHERI for license details.

if (CS1.tag && CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.base = CS1.base;
  temp.length = CS1.length;
  temp.offset = RS2 - CS1.base;
  if(temp.offset >= CS1.length) {
    temp.tag = 0; 
  }
  WRITE_CD(temp);
}
