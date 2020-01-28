require_extension('C');
require_extension('D');
require_fp;
WRITE_FRD(f64(CHERI_MODE_LOAD(uint64, X_SP, insn.rvc_ldsp_imm())));
