// See LICENSE_CHERI for license details.

uint64_t new_cursor = CS1.cursor + RS2;

//fprintf(stderr, "cincoffset: base 0x%lx oldoffset 0x%lx rs2 0x%lx newoffset 0x%lx tag %d seal %d\n", CS1.base, CS1.offset, RS2, new_offset, CS1.tag, CS1.sealed());

if (CS1.tag && CS1.sealed()) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  if (!cheri_is_representable(CS1.sealed(), CS1.base, CS1.length, CS1.cursor, new_cursor)) {
    temp = CHERI_NULL_CAP;
  }
  temp.cursor = new_cursor;
  WRITE_CD(temp);
}
