require_extension('D');
require_fp;
WRITE_FRD(f64(CHERI_MODE_LOAD(uint64, insn.rs1(), insn.i_imm())));
