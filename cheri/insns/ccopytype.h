// See LICENSE_CHERI for license details.

if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (!CS2.sealed) {
  cheri_reg_t temp = CHERI_NULL_CAP;
  temp.offset = UINT64_MAX;
  WRITE_CD(temp);
}
else if (CS2.otype < CS1.base) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS2.otype >= CS1.base + CS1.length) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.offset = CS2.otype - CS1.base;
  WRITE_CD(temp);
}
