// See LICENSE_CHERI for license details.

cheri_reg_t auth = (insn.cs1() == 0) ? DDC : CS1;
reg_t authidx = ((insn.cs1() == 0) << 5) | insn.cs1();

if (RS2 == 0) {
  WRITE_CD(cheri_reg_t());
} else if (!auth.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, authidx);
} else if (auth.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, authidx);
} else {
  cheri_reg_t cap = auth;
  auth.set_offset(RS2);
  WRITE_CD(auth);
}
