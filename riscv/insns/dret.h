require(STATE.debug_mode);
reg_t dpc = STATE.dpc;
if (auto *ext = p->get_extension()) dpc = ext->from_arch_pc(dpc);
set_pc_and_serialize(dpc);
p->set_privilege(STATE.dcsr.prv);

/* We're not in Debug Mode anymore. */
STATE.debug_mode = false;

if (STATE.dcsr.step)
  STATE.single_step = STATE.STEP_STEPPING;
