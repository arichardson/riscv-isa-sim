// See LICENSE for license details.

#include "insn_template.h"
#include "extension.h"

reg_t rv32_NAME(processor_t* p, insn_t insn, reg_t pc_addr)
{
  int xlen = 32;
  auto *ext = p->get_extension();
  reg_t pc = ext ? ext->to_arch_pc(pc_addr) : pc_addr;
  reg_t npc = sext_xlen(pc + insn_length(OPCODE));
  #include "insns/NAME.h"
  trace_opcode(p, OPCODE, insn);
  return ext ? ext->from_arch_pc(npc) : npc;
}

reg_t rv64_NAME(processor_t* p, insn_t insn, reg_t pc_addr)
{
  int xlen = 64;
  auto *ext = p->get_extension();
  reg_t pc = ext ? ext->to_arch_pc(pc_addr) : pc_addr;
  reg_t npc = sext_xlen(pc + insn_length(OPCODE));
  #include "insns/NAME.h"
  trace_opcode(p, OPCODE, insn);
  return ext ? ext->from_arch_pc(npc) : npc;
}
