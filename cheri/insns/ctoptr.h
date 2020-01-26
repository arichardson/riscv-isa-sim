// See LICENSE_CHERI for license details.

cheri_reg_t auth = (insn.cs2() == 0) ? DDC : CS2;
reg_t authidx = ((insn.cs2() == 0) << 5) | insn.cs2();

if (!auth.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, authidx);
} else if (CS1.tag && CS1.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else {
  WRITE_RD(CS1.tag ? CS1.cursor() - auth.base() : 0);
}
