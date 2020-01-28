require_extension('C');
require(insn.rvc_rd() != 0);
WRITE_RD(CHERI_MODE_LOAD(int32, X_SP, insn.rvc_lwsp_imm()));
