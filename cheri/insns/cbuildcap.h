// See LICENSE_CHERI for license details.

cheri_reg_t auth = (insn.cs1() == 0) ? DDC : CS1;
reg_t authidx = (insn.cs1() == 0) ? (0x20 | CHERI_SCR_DDC) : insn.cs1();

if (!auth.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, authidx);
} else if (auth.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, authidx);
} else if (CS2.base() < auth.base()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, authidx);
} else if (CS2.top() > auth.top()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, authidx);
} else if (CS2.base() > CS2.top()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
} else if ((auth.perms & CS2.perms) != CS2.perms) {
  CHERI->raise_trap(CAUSE_CHERI_ACCESSPERM_FAULT, authidx);
} else {
  cheri_reg_t cap = auth;
  cap.set_bounds(CS2.base(), CS2.top());
  cap.set_cursor(CS2.cursor());
  cap.flags = CS2.flags;
  cap.uperms = CS2.uperms;
  cap.perms = CS2.perms;
  /* Untagged input was representable, so output should be */
  assert(cap.base() == CS2.base());
  assert(cap.top() == CS2.top());
  assert(cap.cursor() == CS2.cursor());
  WRITE_CD(cap);
}
