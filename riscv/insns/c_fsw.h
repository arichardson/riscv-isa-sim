require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  CHERI_MODE_STORE(uint32, insn.rvc_rs1s(), insn.rvc_lw_imm(), RVC_FRS2S.v[0]);
} else { // c.sd
  CHERI_MODE_STORE(uint64, insn.rvc_rs1s(), insn.rvc_ld_imm(), RVC_RS2S);
}
