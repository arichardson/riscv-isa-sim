// See LICENSE_CHERI for license details.

cheri_reg_t temp = SCR;

bool read_only = false;
bool needASR = true;

switch(insn.chs()) {
  case CHERI_SCR_PCC:
    read_only = true;
  case CHERI_SCR_DDC:
    needASR = false;
  case CHERI_SCR_UTCC:
  case CHERI_SCR_UTDC:
  case CHERI_SCR_USCRATCHC:
  case CHERI_SCR_UEPCC:
  case CHERI_SCR_STCC:
  case CHERI_SCR_STDC:
  case CHERI_SCR_SSCRATCHC:
  case CHERI_SCR_SEPCC:
  case CHERI_SCR_MTCC:
  case CHERI_SCR_MTDC:
  case CHERI_SCR_MSCRATCHC:
  case CHERI_SCR_MEPCC:
    if((read_only && insn.cs1() != 0) ||
      //TODO add check if current privilege is user privilege or not.
      (needASR && !(PCC.perms & BIT(CHERI_PERMIT_ACCESS_SYSTEM_REGISTERS)))
      ) {
      CHERI->raise_trap(CAUSE_CHERI_ACCESSPERM_FAULT, insn.chs());
    } else {
      /* If source register is c0, don't write CSR (used to read CSR) */
      if (insn.cs1())
        SET_SCR(insn.chs(), CS1);

      /* If destination register is c0, do nothing */
      if (insn.cd())
        WRITE_CD(temp);
    }
    break;

  default:
    throw trap_illegal_instruction(0);
    break;
}
