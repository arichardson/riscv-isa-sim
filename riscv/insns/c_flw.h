require_extension('C');
if (xlen == 32) {
  require_extension('F');
  require_fp;
  WRITE_RVC_FRS2S(f32(CHERI_MODE_LOAD(uint32, insn.rvc_rs1s(), insn.rvc_lw_imm())));
} else { // c.ld
  WRITE_RVC_RS2S(CHERI_MODE_LOAD(int64, insn.rvc_rs1s(), insn.rvc_ld_imm()));
}
