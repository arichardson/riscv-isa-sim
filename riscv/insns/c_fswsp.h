require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  CHERI_MODE_STORE(uint32, X_SP, insn.rvc_swsp_imm(), RVC_FRS2.v[0]);
} else { // c.sdsp
  CHERI_MODE_STORE(uint64, X_SP, insn.rvc_sdsp_imm(), RVC_RS2);
}
