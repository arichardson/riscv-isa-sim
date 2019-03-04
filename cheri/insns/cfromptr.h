// See LICENSE_CHERI for license details.

if (RS2 == 0) WRITE_CD(CHERI_NULL_CAP);
else if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
/* FIXME */
// else if (!newcap.exact) WRITE_CD(nullWithAddr(CS1.base + RS2));
else {
  cheri_reg_t temp = CS1;
  temp.offset = RS2;
  WRITE_CD(temp);
}
