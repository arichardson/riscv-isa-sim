// See LICENSE_CHERI for license details.

if (CS1.length() >= MAX_CHERI_LENGTH) {
  WRITE_RD(UINT64_MAX);
} else {
  WRITE_RD(CS1.length());
}
