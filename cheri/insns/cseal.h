// See LICENSE_CHERI for license details.

if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (!CS2.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs2());
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS2.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs2());
else if (!(CS2.perms & BIT(CHERI_PERMIT_SEAL))) CHERI->raise_trap(CAUSE_CHERI_PERMIT_SEAL_FAULT, insn.cs2());
else if (CS2.base + CS2.offset >= CS2.base + CS2.length) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
else if (CS2.base + CS2.offset > OTYPE_MAX) CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
else if (!cheri_is_representable(1, CS1.base, CS1.length, CS1.offset)) CHERI->raise_trap(CAUSE_CHERI_BOUNDS_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.sealed = 1;
  temp.otype = CS2.base + CS2.offset;
  WRITE_CD(temp);
}
