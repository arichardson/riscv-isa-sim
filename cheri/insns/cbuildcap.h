// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs1() == 0)? DDC : CS1;

if (!tmp.tag)
  CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs1());
else if (tmp.sealed())
  CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else if (CS2.base < tmp.base)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS2.base + CS2.length > tmp.base + tmp.length)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs1());
else if (CS2.length < 0)
  CHERI->raise_trap(CAUSE_CHERI_LENGTH_FAULT, insn.cs2());
else if ((tmp.perms & CS2.perms) != CS2.perms)
  CHERI->raise_trap(CAUSE_CHERI_ACCESSPERM_FAULT, insn.cs1());
else {
  cheri_reg_t temp = CS2;
  temp.otype = OTYPE_UNSEALED;
  temp.tag = 1;
  WRITE_CD(temp);
}
