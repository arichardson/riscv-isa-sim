// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs2() == 0)? DDC : CS2;

if (!tmp.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, ((insn.cs2() == 0) << 5) | insn.cs2());
}
else if (CS1.otype != OTYPE_UNSEALED && CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else {
  WRITE_RD(CS1.tag? CS1.cursor - tmp.base : 0);
}
