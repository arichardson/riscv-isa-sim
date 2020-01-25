// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs1() == 0)? DDC : CS1;
reg_t idx = ((insn.cs1() == 0) << 5) | insn.cs1();
reg_t new_cursor = tmp.base + RS2;

if (RS2 == 0) {
  WRITE_CD(CHERI_NULL_CAP);
} else if (!tmp.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, idx);
}
else if (tmp.otype != OTYPE_UNSEALED) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, idx);
}
else {
  if(!cheri_is_representable(tmp.sealed(), tmp.base, tmp.length, tmp.cursor, new_cursor)) {
    tmp = CHERI_NULL_CAP;
  }
  tmp.cursor = tmp.base + RS2;
  WRITE_CD(tmp);
}
