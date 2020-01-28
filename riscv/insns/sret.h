require_extension('S');
require_privilege(get_field(STATE.mstatus, MSTATUS_TSR) ? PRV_M : PRV_S);
reg_t sepc = p->get_state()->sepc;
set_pc_and_serialize(sepc);
reg_t s = STATE.mstatus;
reg_t prev_prv = get_field(s, MSTATUS_SPP);
s = set_field(s, MSTATUS_SIE, get_field(s, MSTATUS_SPIE));
s = set_field(s, MSTATUS_SPIE, 1);
s = set_field(s, MSTATUS_SPP, PRV_U);
p->set_privilege(prev_prv);
p->set_csr(CSR_MSTATUS, s);

#ifdef ENABLE_CHERI
SET_SCR(CHERI_SCR_PCC, GET_SCR(CHERI_SCR_SEPCC));
#endif
