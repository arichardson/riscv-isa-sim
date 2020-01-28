require_extension('F');
require_fp;
CHERI_MODE_STORE(uint32, insn.rs1(), insn.s_imm(), FRS2.v[0]);
