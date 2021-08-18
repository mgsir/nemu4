#include <cpu/exec.h>
#include "rtl.h"

// decode operand helper
#define def_DopHelper(name) \
  void concat(decode_op_, name) (DecodeExecState *s, Operand *op, word_t val, bool load_val)

static inline def_DopHelper(i) {
  op->type = OP_TYPE_IMM;
 
  // if(val & 0x00100000){
  //   val = val | 0xfff00000;
  //   printf("123");
  // }
  op->imm = val;
  // printf(" : 0x%08x\n",(int)val);
  print_Dop(op->str, OP_STR_SIZE, "%d", op->imm);
}

static inline def_DopHelper(r) {
  op->type = OP_TYPE_REG;
  op->reg = val;
  op->preg = &reg_l(val);

  print_Dop(op->str, OP_STR_SIZE, "%s", reg_name(op->reg));
}

static inline def_DHelper(I) {
  decode_op_r(s, id_src1, s->isa.instr.i.rs1, true);
  decode_op_i(s, id_src2, s->isa.instr.i.simm11_0, true);
  decode_op_r(s, id_dest, s->isa.instr.i.rd, false);
}

static inline def_DHelper(U) {
  decode_op_i(s, id_src1, s->isa.instr.u.imm31_12 << 12, true);
  decode_op_r(s, id_dest, s->isa.instr.u.rd, false);

  print_Dop(id_src1->str, OP_STR_SIZE, "0x%x", s->isa.instr.u.imm31_12);
}

static inline def_DHelper(S) {
  decode_op_r(s, id_src1, s->isa.instr.s.rs1, true);
  sword_t simm = (s->isa.instr.s.simm11_5 << 5) | s->isa.instr.s.imm4_0;
  decode_op_i(s, id_src2, simm, true);
  decode_op_r(s, id_dest, s->isa.instr.s.rs2, true);
}

static inline def_DHelper(J) {
  sword_t simm = (s->isa.instr.j.imm19_12 << 12 ) | (s->isa.instr.j.imm_11 << 11) | (s->isa.instr.j.imm10_1 << 1) | (s->isa.instr.j.imm_20 << 20); 
  printf(":: 0x%08x\n",simm );
  decode_op_i(s, id_src1,simm , true);
  decode_op_r(s, id_dest, s->isa.instr.j.rd, false);
}

