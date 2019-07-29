// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs1() == 0)? DDC : CS1;
tmp.offset = RS2;

if (RS2 == 0) {
  WRITE_CD(CHERI_NULL_CAP);
} else if (!tmp.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
}
else if (tmp.otype != OTYPE_UNSEALED) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
else {
  if(!cheri_is_representable(tmp.sealed, tmp.base, tmp.length, tmp.offset)) {
    tmp = CHERI_NULL_CAP;
    tmp.offset = CS1.base + RS2;
  }
  WRITE_CD(tmp);
}
