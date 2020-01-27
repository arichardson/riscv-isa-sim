// See LICENSE_CHERI for license details.

cheri_length_t new_top = (cheri_length_t)CS1.cursor() + RS2;

if (!CS1.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
} else if (CS1.sealed()) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else if (CS1.cursor() < CS1.base()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
} else if (new_top > CS1.top()) {
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
} else {
  cheri_reg_t cap = CS1;
  cap.set_bounds(CS1.cursor(), new_top);
  if (cap.base() != CS1.cursor() || cap.top() != new_top) {
    CHERI->raise_trap(CAUSE_CHERI_BOUNDS_FAULT, insn.cs1());
  } else {
    WRITE_CD(cap);
  }
}
