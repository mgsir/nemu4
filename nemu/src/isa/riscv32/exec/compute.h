static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm << 12); // low bit was setten as zero
  print_asm_template2(lui);
}

static inline def_EHelper(addi){
  rtl_addi(s,ddest,dsrc1,id_src2->imm );
  print_asm_template3(addi);
}

static inline def_EHelper(auipc){
  rtl_addi(s,ddest,&cpu.pc,id_src1->imm << 12);
  print_asm_template2(auipc);
}


static inline def_EHelper(jal){

  rtl_addi(s,ddest,&cpu.pc,4);
  rtl_addi(s,&cpu.pc,&cpu.pc,id_src1->imm);
  s->is_jmp = 1;
  print_asm_template2(jal);
}

static inline def_EHelper(jalr){

  word_t t = cpu.pc + 4;
  rtl_addi(s,&cpu.pc,ddest,id_src1->imm);
  rtl_li(s,ddest,t);
  s->is_jmp = 1;
  print_asm_template3(jalr);
}









