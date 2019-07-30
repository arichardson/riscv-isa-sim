// See LICENSE_CHERI for license details.

cheri_reg_t cb_val = CS1;
reg_t cb_base = cb_val.base;
cheri_length_t cb_top = cb_val.base + cb_val.length;
reg_t cb_ptr = cb_val.base + cb_val.offset;

if (!cb_val.tag) {
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
} else if (CS1.sealed) {
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
} else if ((CS1.perms & BIT(CHERI_PERMIT_EXECUTE)) != BIT(CHERI_PERMIT_EXECUTE)) {
#if DEBUG
  printf("CHERI: Trying to execute with no cap LOAD permissions\n");
#endif //DEBUG
  CHERI->raise_trap(CAUSE_CHERI_PERMIT_EXECUTE_FAULT, insn.cs1());
} else if (cb_ptr < cb_base) {
#if DEBUG
  printf("CHERI: Trying to execute with wrong bounds\n");
#endif //DEBUG
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
} else if (cb_ptr + 4 > cb_top) {
#if DEBUG
  printf("CHERI: Trying to execute with wrong bounds\n");
#endif //DEBUG
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
}
// FIXME
// else if (cb_ptr % 4) != 0 then
// SignalException(AdEL)
else {
#if DEBUG
  if(cb_ptr % 4 != 0) {
    fprintf(stderr, "cjalr: ERROR jump to unaligned PC not supported!!!")
  }
#endif //DEBUG
  cheri_reg_t temp = PCC;

  PCC = cb_val;
  /* offset of PCC will be in pc */
  PCC.offset = 0;

  // Link cap
  temp.offset = pc+4;

#ifdef CHERI_MERGED_RF
  WRITE_CD_MERGED(temp);
#else /* CHERI_MERGED_RF */
  WRITE_CD(temp);
#endif /* CHERI_MERGED_RF */

#if DEBUG
  printf("CHERI: cjalr- - linkreg = %lu jumping to %lu\n", temp.offset, PCC.base
         + cb_val.offset);
#endif //DEBUG

  set_pc(PCC.base + cb_val.offset);
}
