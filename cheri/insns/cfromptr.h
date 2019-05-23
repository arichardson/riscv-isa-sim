// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs1() == 0)? DDC : CS1;

if (RS2 == 0) {
  WRITE_CD(CHERI_NULL_CAP);
} else if (!tmp.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
}
else if (tmp.otype != OTYPE_UNSEALED) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
}
/* FIXME */
// else if (!newcap.exact) WRITE_CD(nullWithAddr(CS1.base + RS2));
else {
  cheri_reg_t temp = tmp;
  temp.offset = RS2;
  WRITE_CD(temp);
}
