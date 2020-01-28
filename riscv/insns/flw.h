require_extension('F');
require_fp;
WRITE_FRD(f32(CHERI_MODE_LOAD(uint32, insn.rs1(), insn.i_imm())));
