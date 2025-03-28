#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <string.h>
#include "MIPS_Instruction.h"
#include "global_data.h"

// ADD.c
void add_reg_assm(void);
void add_reg_bin(void);

// ADDI.c
void addi_immd_assm(void);
void addi_immd_bin(void);

// AND.c
void and_reg_assm(void);
void and_reg_bin(void);

// ANDI.c
void andi_immd_assm(void);
void andi_immd_bin(void);

// BEQ.c
void beq_immd_assm(void);
void beq_immd_bin(void);

// BNE.c
void bne_immd_assm(void);
void bne_immd_bin(void);

// DIV.c
void div_reg_assm(void);
void div_reg_bin(void);

// LUI.c
void lui_immd_assm(void);
void lui_immd_bin(void);

//LW.c
void lw_immd_assm(void);
void lw_immd_bin(void);

// MFHI.c
void mfhi_reg_assm(void);
void mfhi_reg_bin(void);

// MFLO.c
void mflo_reg_assm(void);
void mflo_reg_bin(void);

// MULT.c
void mult_reg_assm(void);
void mult_reg_bin(void);

// OR.c
void or_reg_assm(void);
void or_reg_bin(void);

// ORI.c
void ori_immd_assm(void);
void ori_immd_bin(void);

// SLT.c
void slt_reg_assm(void);
void slt_reg_bin(void);

// SLTI.c
void slti_immd_assm(void);
void slti_immd_bin(void);

// SUB.c
void sub_reg_assm(void);
void sub_reg_bin(void);

//SW.c
void sw_immd_assm(void);
void sw_immd_bin(void);

#endif