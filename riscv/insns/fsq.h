require_extension('Q');
require_fp;
CHERI_MODE_STORE(float128, insn.rs1(), insn.s_imm(), FRS2);
