// See LICENSE_CHERI for license details.

if (CHERI->get_mode()) {
  CHERI->cap_store_cap(CS1, insn.cs1(), insn.s_imm(), CS2);
} else {
  CHERI->ddc_store_cap(RS1 + insn.s_imm(), CS2);
}
