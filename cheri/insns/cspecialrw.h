// See LICENSE_CHERI for license details.

cheri_reg_t temp = CSR;

switch(insn.chs()) {
  case CHERI_CSR_PCC:
  case CHERI_CSR_DDC:
  case CHERI_CSR_UTCC:
  case CHERI_CSR_USCRATCHC:
  case CHERI_CSR_UEPCC:
  case CHERI_CSR_STCC:
  case CHERI_CSR_SSCRATCHC:
  case CHERI_CSR_SEPCC:
  case CHERI_CSR_MTCC:
  case CHERI_CSR_MSCRATCHC:
  case CHERI_CSR_MEPCC:

    /* If source register is c0, don't write CSR (used to read CSR) */
    if (insn.cs1())
      CSR = CS1;

    /* If destination register is c0, do nothing */
    if (insn.cd())
      WRITE_CD(temp);
    break;

  default:
    throw trap_illegal_instruction(0);
    break;
}
