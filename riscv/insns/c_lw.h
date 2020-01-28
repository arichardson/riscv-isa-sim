require_extension('C');
WRITE_RVC_RS2S(CHERI_MODE_LOAD(int32, insn.rvc_rs1s(), insn.rvc_lw_imm()));
