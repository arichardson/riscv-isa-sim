// See LICENSE_CHERI for license details.

if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS1.base + CS1.offset < CS1.base) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS1.base + CS1.offset + RS2 < CS1.base + CS1.offset) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1()); //Addition overflow detection
else if (CS1.base + CS1.offset + RS2 > CS1.base + CS1.length) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else {
  cap_register_t temp_cap_reg;
  convertCheriReg(&temp_cap_reg, &CS1);
  cc128_setbounds(&temp_cap_reg, CS1.base+CS1.offset, CS1.base + CS1.offset +RS2);
  cheri_reg_t temp_cheri_reg;
  retrieveCheriReg(&temp_cheri_reg, &temp_cap_reg);
  WRITE_CD(temp_cheri_reg);
}
