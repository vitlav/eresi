/*
**
** $Id: asm_sparc_fmovsr.c,v 1.5 2007-06-16 20:24:25 strauss Exp $
**
*/
#include "libasm.h"

int
asm_sparc_fmovsr(asm_instr * ins, u_char * buf, u_int len,
		 asm_processor * proc)
{
  struct s_decode_format3 opcode;
  struct s_asm_proc_sparc *inter;
  sparc_convert_format3(&opcode, buf);

  inter = proc->internals;
  ins->type = ASM_TYPE_ASSIGN | ASM_TYPE_TEST;

  ins->instr = inter->fmovr_table[(((opcode.opf & 0x1f) - 6) * 8)
				  + opcode.rcond];
  ins->nb_op = 3;
  asm_sparc_op_fetch(&ins->op1, buf, ASM_SP_OTYPE_FREGISTER, ins);
  ins->op1.base_reg = opcode.rd;
  asm_sparc_op_fetch(&ins->op2, buf, ASM_SP_OTYPE_FREGISTER, ins);
  ins->op2.base_reg = opcode.rs2;
  asm_sparc_op_fetch(&ins->op3, buf, ASM_SP_OTYPE_REGISTER, ins);
  ins->op3.base_reg = opcode.rs1;
  
  return 4;
}
