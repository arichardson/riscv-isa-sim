// See LICENSE_CHERI for license details.

if (!CS1.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS1;
  temp.perms = CS1.perms & (RS2 & MASK(CHERI_PERM_BITS));
  temp.uperms = CS1.uperms & ((RS2 >> CHERI_PERM_BITS) & MASK(CHERI_USER_PERM_BITS));
  WRITE_CD(temp);
}
