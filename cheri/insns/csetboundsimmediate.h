// See LICENSE_CHERI for license details.

cheri_length_t new_length = insn.i_imm() & 0x0FFF; // remove the sign extension from i_imm
cheri_length_t new_top = CS1.cursor + new_length;
cheri_length_t old_top = CS1.cursor;

if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed()) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS1.cursor < CS1.base) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (new_top > old_top) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else {
  cap_register_t temp_cap_reg;
  convertCheriReg(&temp_cap_reg, &CS1);
  cc128_setbounds(&temp_cap_reg, CS1.cursor, new_top);
  cheri_reg_t temp_cheri_reg;
  retrieveCheriReg(&temp_cheri_reg, &temp_cap_reg);
  WRITE_CD(temp_cheri_reg);
}
