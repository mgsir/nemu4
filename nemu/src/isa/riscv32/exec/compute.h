static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm); // low bit was setten as zero
  print_asm_template2(lui);
}

static inline def_EHelper(addi){
  rtl_addi(s,ddest,dsrc1,id_src2->imm );
  print_asm_template3(addi);
}


static inline def_EHelper(add){
  rtl_add(s,ddest,dsrc1,dsrc2);
  print_asm_template3(add);
}

static inline def_EHelper(sub){
  rtl_sub(s,ddest,dsrc1,dsrc2);
  print_asm_template3(sub);
}
static inline def_EHelper(auipc){
  rtl_addi(s,ddest,&cpu.pc,id_src1->imm);
  print_asm_template2(auipc);
}


static inline def_EHelper(sll){
  rtl_shl(s,ddest,dsrc1,dsrc2);
  print_asm_template3(sll)
}

static inline def_EHelper(slli){
  rtl_shli(s,ddest,dsrc1,id_src2->imm & 0x01f);
  print_asm_template3(slli)
}

static inline def_EHelper(srl){
  rtl_shr(s,ddest,dsrc1,dsrc2);
  print_asm_template3(srl)
}

static inline def_EHelper(srli){
  rtl_shri(s,ddest,dsrc1,id_src2->imm & 0x01f);
  print_asm_template3(srli)
}


static inline def_EHelper(sra){
  rtl_sar(s,ddest,dsrc1,dsrc2);
  print_asm_template3(sra)
}

static inline def_EHelper(srai){
  rtl_sari(s,ddest,dsrc1,id_src2->imm & 0x01f);
  print_asm_template3(srai)
}

static inline def_EHelper(sltiu){
  rtlreg_t temp = id_src2->imm;
  rtl_zext(s,&temp,&temp,12);
  cpu.gpr[*ddest]._32 = (cpu.gpr[*dsrc1]._32 < temp);
  print_asm_template3(stliu)
}

static inline def_EHelper(xor){
  rtl_xor(s,ddest,dsrc1,dsrc2);
  print_asm_template3(xor)
}





