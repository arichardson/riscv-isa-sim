require_extension('D');
require_fp;
CHERI_MODE_STORE(uint64, insn.rs1(), insn.s_imm(), FRS2.v[0]);
