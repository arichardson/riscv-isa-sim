require_extension('C');
require_extension('D');
require_fp;
CHERI_MODE_STORE(uint64, insn.rvc_rs1s(), insn.rvc_ld_imm(), RVC_FRS2S.v[0]);
