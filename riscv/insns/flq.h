require_extension('Q');
require_fp;
WRITE_FRD(CHERI_MODE_LOAD(float128, insn.rs1(), insn.i_imm()));
