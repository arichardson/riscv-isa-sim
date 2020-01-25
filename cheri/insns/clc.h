// See LICENSE_CHERI for license details.

if (CHERI->get_mode()) {
  WRITE_CD(CHERI->cap_load_cap(CS1, insn.cs1(), insn.i_imm()));
} else {
  WRITE_CD(CHERI->ddc_load_cap(RS1 + insn.i_imm()));
}
