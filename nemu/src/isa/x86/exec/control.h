#include "cc.h"

static inline def_EHelper(jmp) {
  // the target address is calculated at the decode stage
  rtl_j(s, s->jmp_pc);

  print_asm("jmp %x", s->jmp_pc);
}

static inline def_EHelper(jcc) {
  // the target address is calculated at the decode stage
  uint32_t cc = s->opcode & 0xf;
  rtl_setcc(s, s0, cc);
  rtl_jrelop(s, RELOP_NE, s0, rz, s->jmp_pc);

  print_asm("j%s %x", get_cc_name(cc), s->jmp_pc);
}

static inline def_EHelper(jmp_rm) {
  rtl_jr(s, ddest);

  print_asm("jmp *%s", id_dest->str);
}

static inline def_EHelper(call) {
  // the target address is calculated at the decode stage
  //paddr_write(reg_l(R_ESP),s->seq_pc,s->width);
  rtl_j(s,s->jmp_pc);
  print_asm("call %x", s->jmp_pc);
}

static inline def_EHelper(ret) {
  uintptr_t addr0 = reg_l(R_ESP);
  rtlreg_t *addr = (void *)addr0;

  puts("123\n");
  rtl_j(s, *addr);
  print_asm("ret");
}

static inline def_EHelper(ret_imm) {
  TODO();
  print_asm("ret %s", id_dest->str);
}

static inline def_EHelper(call_rm) {
  TODO();
  print_asm("call *%s", id_dest->str);
}
