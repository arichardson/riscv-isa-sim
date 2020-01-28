require_extension('C');
require_extension('D');
require_fp;
WRITE_RVC_FRS2S(f64(CHERI_MODE_LOAD(uint64, insn.rvc_rs1s(), insn.rvc_ld_imm())));
