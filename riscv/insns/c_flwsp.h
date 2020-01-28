require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  WRITE_FRD(f32(CHERI_MODE_LOAD(uint32, X_SP, insn.rvc_lwsp_imm())));
} else { // c.ldsp
  require(insn.rvc_rd() != 0);
  WRITE_RD(CHERI_MODE_LOAD(int64, X_SP, insn.rvc_ldsp_imm()));
}
