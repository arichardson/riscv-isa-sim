require_extension('C');
require_extension('D');
require_fp;
CHERI_MODE_STORE(uint64, X_SP, insn.rvc_sdsp_imm(), RVC_FRS2.v[0]);
