// See LICENSE_CHERI for license details.

if (!CS2.tag) CHERI->raise_trap(CAUSE_CHERI_TAG_FAULT, insn.cs2());
else if (!CS1.tag) WRITE_RD(0);
else if (CS1.sealed) CHERI->raise_trap(CAUSE_CHERI_SEAL_FAULT, insn.cs1());
else WRITE_RD(CS1.base + CS1.offset - CS2.base);
