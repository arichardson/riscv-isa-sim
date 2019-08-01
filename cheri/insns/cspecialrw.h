// See LICENSE_CHERI for license details.

cheri_reg_t temp = CSR;

bool read_only = false;
bool needASR = true;

switch(insn.chs()) {
  case CHERI_CSR_PCC:
    read_only = true;
  case CHERI_CSR_DDC:
    needASR = false;
  case CHERI_CSR_UTCC:
  case CHERI_CSR_UTDC:
  case CHERI_CSR_USCRATCHC:
  case CHERI_CSR_UEPCC:
  case CHERI_CSR_STCC:
  case CHERI_CSR_STDC:
  case CHERI_CSR_SSCRATCHC:
  case CHERI_CSR_SEPCC:
  case CHERI_CSR_MTCC:
  case CHERI_CSR_MTDC:
  case CHERI_CSR_MSCRATCHC:
  case CHERI_CSR_MEPCC:
    if((read_only && insn.cs1() != 0) ||
      //TODO add check if current privilege is user privilege or not.
      (needASR && !(PCC.perms & BIT(CHERI_PERMIT_ACCESS_SYSTEM_REGISTERS)))
      ) {
      CHERI->raise_trap(CAUSE_CHERI_ACCESSPERM_FAULT, insn.chs());
    } else {
      /* If source register is c0, don't write CSR (used to read CSR) */
      if (insn.cs1())
        CSR = CS1;

      /* If destination register is c0, do nothing */
      if (insn.cd())
        WRITE_CD(temp);
    }
    break;

  default:
    throw trap_illegal_instruction(0);
    break;
}
