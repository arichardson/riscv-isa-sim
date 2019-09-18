// See LICENSE_CHERI for license details.

cheri_reg_t tmp = (insn.cs1() == 0)? DDC : CS1;

if (
  tmp.tag != CS2.tag ||
  CS2.base < tmp.base ||
  CS2.length > tmp.length ||
  (CS2.perms & tmp.perms) != CS2.perms
) {
  WRITE_RD(0);
} else {
  WRITE_RD(1);
}
