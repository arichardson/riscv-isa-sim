// See LICENSE_CHERI for license details.

reg_t ret_value = 0;

/* L2 cache counters starts from 14 */
if (insn.i_imm() >= 14)
  MMU.get_l2cache()->read_counter(&ret_value, insn.i_imm());
else
  MMU.get_tracer()->read_counter(&ret_value, insn.i_imm());

WRITE_RD(ret_value);
