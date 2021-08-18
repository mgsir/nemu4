static inline def_EHelper(jal){
  rtl_addi(s,ddest,&cpu.pc,4);
  rtl_addi(s,&cpu.pc,&cpu.pc,id_src1->imm);
  
  rtl_j(s,cpu.pc);
  print_asm_template2(jal);
}

static inline def_EHelper(jalr){

  word_t t = cpu.pc + 4;
  word_t temp = cpu.gpr[id_src1->reg]._32 + id_src2->imm;
  temp = temp & 0xfffffffe;
  rtl_li(s,&cpu.pc,temp);
  rtl_li(s,ddest,t);

  rtl_j(s,cpu.pc);
  print_asm_template3(jalr);
}



