// See LICENSE_CHERI for license details.

if (!CS1.tag)
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed)
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS2.base < CS1.base)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS2.base + CS2.length > CS1.base + CS1.length)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS2.length < 0)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
else if ((CS1.perms & CS2.perms) != CS2.perms)
  CHERI->raise_trap(CAUSE_CHERI_ACCESSPERM_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS2;
  temp.sealed = 0;
  temp.otype = OTYPE_UNSEALED;
  temp.tag = 1;
  WRITE_CD(temp);
}
