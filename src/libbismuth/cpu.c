#include <stdio.h>
#include <string.h>
#include <libbismuth/libbismuth.h>

#define TRAP        do { printf("Bad opcode: 0x%02x at 0x%02x%04x\n", op, cpu.pbr, pcBak); getchar(); } while (0)
#define READ_A24()  do { a24 = biMemoryRead16(ctx, cpu.pbr, cpu.pc); a24 |= (biMemoryRead8(ctx, cpu.pbr, cpu.pc + 2) << 8); cpu.pc += 3; } while (0)
#define READ_A16()  do { a16 = biMemoryRead16(ctx, cpu.pbr, cpu.pc); cpu.pc += 2; } while (0)
#define READ_A8()   do { a8 = biMemoryRead8(ctx, cpu.pbr, cpu.pc); cpu.pc += 1; } while (0)

#define ADC8(a, b) do {                                                     \
    tmp32 = (uint8_t)a + (uint8_t)b + !!(cpu.p & CPU_FLAG_C);               \
    cpu.p &= ~(CPU_FLAG_C | CPU_FLAG_V | CPU_FLAG_Z | CPU_FLAG_N);          \
    r8 = tmp32 & 0xff;                                                      \
    if (r8 == 0) cpu.p |= CPU_FLAG_Z;                                       \
    if (r8 & 0x80) cpu.p |= CPU_FLAG_N;                                     \
    if (tmp32 & 0x100) cpu.p |= CPU_FLAG_C;                                 \
    if ((r8 ^ (uint8_t)a) & (r8 ^ (uint8_t)b) & 0x80) cpu.p |= CPU_FLAG_V;  \
} while (0)

#define ADC16(a, b) do {                                                        \
    tmp32 = (uint16_t)a + (uint16_t)b + !!(cpu.p & CPU_FLAG_C);                 \
    cpu.p &= ~(CPU_FLAG_C | CPU_FLAG_V | CPU_FLAG_Z | CPU_FLAG_N);              \
    r16 = tmp32 & 0xffff;                                                       \
    if (r16 == 0) cpu.p |= CPU_FLAG_Z;                                          \
    if (r16 & 0x8000) cpu.p |= CPU_FLAG_N;                                      \
    if (tmp32 & 0x10000) cpu.p |= CPU_FLAG_C;                                   \
    if ((r16 ^ (uint8_t)a) & (r16 ^ (uint8_t)b) & 0x8000) cpu.p |= CPU_FLAG_V;  \
} while (0)

#define FLAGS8_NZ(v) do {                   \
    cpu.p &= ~(CPU_FLAG_N | CPU_FLAG_Z);    \
    if (v == 0)                             \
    {                                       \
        cpu.p |= CPU_FLAG_Z;                \
    }                                       \
    else if (v & 0x80)                      \
    {                                       \
        cpu.p |= CPU_FLAG_N;                \
    }                                       \
} while (0)

#define FLAGS16_NZ(v) do {                  \
    cpu.p &= ~(CPU_FLAG_N | CPU_FLAG_Z);    \
    if (v == 0)                             \
    {                                       \
        cpu.p |= CPU_FLAG_Z;                \
    }                                       \
    else if (v & 0x8000)                    \
    {                                       \
        cpu.p |= CPU_FLAG_N;                \
    }                                       \
} while (0)

#define PUSH8(v) do {                       \
    biMemoryWrite8(ctx, 0, cpu.s, v);       \
    cpu.s -= 1;                             \
} while (0)

#define PUSH16(v) do {                      \
    biMemoryWrite16(ctx, 0, cpu.s, v);      \
    cpu.s -= 2;                             \
} while (0)

void biRunCycles(BiContext* ctx, size_t cycles)
{
    BiCPU cpu;
    uint16_t pcBak;
    uint16_t op;
    uint32_t a24;
    uint16_t a16;
    uint8_t a8;
    uint8_t r8;
    uint16_t r16;
    uint32_t tmp32;

    memcpy(&cpu, &ctx->cpu, sizeof(cpu));
    for (size_t cycleCounter = 0; cycleCounter < cycles; ++cycleCounter)
    {
        pcBak = cpu.pc;
        op = biMemoryRead8(ctx, cpu.pbr, cpu.pc);
        op |= ((cpu.p << 4) & 0x300);
        cpu.pc++;
        switch (op)
        {
        default:
            TRAP;
            break;
        case OP_BRK_S:
        case OP_BRK_S_X:
        case OP_BRK_S_M:
        case OP_BRK_S_MX:
            TRAP;
            break;
        case OP_ORA_DXI:
        case OP_ORA_DXI_X:
        case OP_ORA_DXI_M:
        case OP_ORA_DXI_MX:
            TRAP;
            break;
        case OP_COP_S:
        case OP_COP_S_X:
        case OP_COP_S_M:
        case OP_COP_S_MX:
            TRAP;
            break;
        case OP_ORA_DS:
        case OP_ORA_DS_X:
        case OP_ORA_DS_M:
        case OP_ORA_DS_MX:
            TRAP;
            break;
        case OP_TBS_D:
        case OP_TBS_D_X:
        case OP_TBS_D_M:
        case OP_TBS_D_MX:
            TRAP;
            break;
        case OP_ORA_D:
        case OP_ORA_D_X:
        case OP_ORA_D_M:
        case OP_ORA_D_MX:
            TRAP;
            break;
        case OP_ASL_D:
        case OP_ASL_D_X:
        case OP_ASL_D_M:
        case OP_ASL_D_MX:
            TRAP;
            break;
        case OP_ORA_DL:
        case OP_ORA_DL_X:
        case OP_ORA_DL_M:
        case OP_ORA_DL_MX:
            TRAP;
            break;
        case OP_PHP_S:
        case OP_PHP_S_X:
        case OP_PHP_S_M:
        case OP_PHP_S_MX:
            PUSH8(cpu.p);
            break;
        case OP_ORA_IMM:
        case OP_ORA_IMM_X:
        case OP_ORA_IMM_M:
        case OP_ORA_IMM_MX:
            TRAP;
            break;
        case OP_ASL_AC:
        case OP_ASL_AC_X:
        case OP_ASL_AC_M:
        case OP_ASL_AC_MX:
            TRAP;
            break;
        case OP_PHD_S:
        case OP_PHD_S_X:
        case OP_PHD_S_M:
        case OP_PHD_S_MX:
            TRAP;
            break;
        case OP_TSB_A:
        case OP_TSB_A_X:
        case OP_TSB_A_M:
        case OP_TSB_A_MX:
            TRAP;
            break;
        case OP_ORA_A:
        case OP_ORA_A_X:
        case OP_ORA_A_M:
        case OP_ORA_A_MX:
            TRAP;
            break;
        case OP_ASL_A:
        case OP_ASL_A_X:
        case OP_ASL_A_M:
        case OP_ASL_A_MX:
            TRAP;
            break;
        case OP_ORA_AL:
        case OP_ORA_AL_X:
        case OP_ORA_AL_M:
        case OP_ORA_AL_MX:
            TRAP;
            break;
        case OP_BPL_R:
        case OP_BPL_R_X:
        case OP_BPL_R_M:
        case OP_BPL_R_MX:
            READ_A8();
            if (!(cpu.p & CPU_FLAG_N))
                cpu.pc += (int8_t)a8;
            break;
        case OP_ORA_DYI:
        case OP_ORA_DYI_X:
        case OP_ORA_DYI_M:
        case OP_ORA_DYI_MX:
            TRAP;
            break;
        case OP_ORA_DI:
        case OP_ORA_DI_X:
        case OP_ORA_DI_M:
        case OP_ORA_DI_MX:
            TRAP;
            break;
        case OP_ORA_DYSI:
        case OP_ORA_DYSI_X:
        case OP_ORA_DYSI_M:
        case OP_ORA_DYSI_MX:
            TRAP;
            break;
        case OP_TRB_D:
        case OP_TRB_D_X:
        case OP_TRB_D_M:
        case OP_TRB_D_MX:
            TRAP;
            break;
        case OP_ORA_DX:
        case OP_ORA_DX_X:
        case OP_ORA_DX_M:
        case OP_ORA_DX_MX:
            TRAP;
            break;
        case OP_ASL_DX:
        case OP_ASL_DX_X:
        case OP_ASL_DX_M:
        case OP_ASL_DX_MX:
            TRAP;
            break;
        case OP_ORA_DYL:
        case OP_ORA_DYL_X:
        case OP_ORA_DYL_M:
        case OP_ORA_DYL_MX:
            TRAP;
            break;
        case OP_CLC:
        case OP_CLC_X:
        case OP_CLC_M:
        case OP_CLC_MX:
            cpu.p &= ~CPU_FLAG_C;
            break;
        case OP_ORA_AY:
        case OP_ORA_AY_X:
        case OP_ORA_AY_M:
        case OP_ORA_AY_MX:
            TRAP;
            break;
        case OP_INC_AC:
        case OP_INC_AC_X:
        case OP_INC_AC_M:
        case OP_INC_AC_MX:
            TRAP;
            break;
        case OP_TCS:
        case OP_TCS_X:
        case OP_TCS_M:
        case OP_TCS_MX:
            cpu.s = cpu.ac.u16;
            FLAGS16_NZ(cpu.ac.u16);
            break;
        case OP_TRB_A:
        case OP_TRB_A_X:
        case OP_TRB_A_M:
        case OP_TRB_A_MX:
            TRAP;
            break;
        case OP_ORA_AX:
        case OP_ORA_AX_X:
        case OP_ORA_AX_M:
        case OP_ORA_AX_MX:
            TRAP;
            break;
        case OP_ASL_AX:
        case OP_ASL_AX_X:
        case OP_ASL_AX_M:
        case OP_ASL_AX_MX:
            TRAP;
            break;
        case OP_ORA_AXL:
        case OP_ORA_AXL_X:
        case OP_ORA_AXL_M:
        case OP_ORA_AXL_MX:
            TRAP;
            break;
        case OP_JSR_A:
        case OP_JSR_A_X:
        case OP_JSR_A_M:
        case OP_JSR_A_MX:
            READ_A16();
            PUSH16(cpu.pc - 1);
            cpu.pc = a16;
            break;
        case OP_AND_DXI:
        case OP_AND_DXI_X:
        case OP_AND_DXI_M:
        case OP_AND_DXI_MX:
            TRAP;
            break;
        case OP_JSL_AL:
        case OP_JSL_AL_X:
        case OP_JSL_AL_M:
        case OP_JSL_AL_MX:
            TRAP;
            break;
        case OP_AND_DS:
        case OP_AND_DS_X:
        case OP_AND_DS_M:
        case OP_AND_DS_MX:
            TRAP;
            break;
        case OP_BIT_D:
        case OP_BIT_D_X:
        case OP_BIT_D_M:
        case OP_BIT_D_MX:
            TRAP;
            break;
        case OP_AND_D:
        case OP_AND_D_X:
        case OP_AND_D_M:
        case OP_AND_D_MX:
            TRAP;
            break;
        case OP_ROL_D:
        case OP_ROL_D_X:
        case OP_ROL_D_M:
        case OP_ROL_D_MX:
            TRAP;
            break;
        case OP_AND_DL:
        case OP_AND_DL_X:
        case OP_AND_DL_M:
        case OP_AND_DL_MX:
            TRAP;
            break;
        case OP_PLP_S:
        case OP_PLP_S_X:
        case OP_PLP_S_M:
        case OP_PLP_S_MX:
            TRAP;
            break;
        case OP_AND_IMM:
        case OP_AND_IMM_X:
        case OP_AND_IMM_M:
        case OP_AND_IMM_MX:
            TRAP;
            break;
        case OP_ROL_AC:
        case OP_ROL_AC_X:
        case OP_ROL_AC_M:
        case OP_ROL_AC_MX:
            TRAP;
            break;
        case OP_PLD_S:
        case OP_PLD_S_X:
        case OP_PLD_S_M:
        case OP_PLD_S_MX:
            TRAP;
            break;
        case OP_BIT_A:
        case OP_BIT_A_X:
        case OP_BIT_A_M:
        case OP_BIT_A_MX:
            TRAP;
            break;
        case OP_AND_A:
        case OP_AND_A_X:
        case OP_AND_A_M:
        case OP_AND_A_MX:
            TRAP;
            break;
        case OP_ROL_A:
        case OP_ROL_A_X:
        case OP_ROL_A_M:
        case OP_ROL_A_MX:
            TRAP;
            break;
        case OP_AND_AL:
        case OP_AND_AL_X:
        case OP_AND_AL_M:
        case OP_AND_AL_MX:
            TRAP;
            break;
        case OP_BMI_R:
        case OP_BMI_R_X:
        case OP_BMI_R_M:
        case OP_BMI_R_MX:
            TRAP;
            break;
        case OP_AND_DYI:
        case OP_AND_DYI_X:
        case OP_AND_DYI_M:
        case OP_AND_DYI_MX:
            TRAP;
            break;
        case OP_AND_DI:
        case OP_AND_DI_X:
        case OP_AND_DI_M:
        case OP_AND_DI_MX:
            TRAP;
            break;
        case OP_AND_DYSI:
        case OP_AND_DYSI_X:
        case OP_AND_DYSI_M:
        case OP_AND_DYSI_MX:
            TRAP;
            break;
        case OP_BIT_DX:
        case OP_BIT_DX_X:
        case OP_BIT_DX_M:
        case OP_BIT_DX_MX:
            TRAP;
            break;
        case OP_AND_DX:
        case OP_AND_DX_X:
        case OP_AND_DX_M:
        case OP_AND_DX_MX:
            TRAP;
            break;
        case OP_ROL_DX:
        case OP_ROL_DX_X:
        case OP_ROL_DX_M:
        case OP_ROL_DX_MX:
            TRAP;
            break;
        case OP_AND_DYL:
        case OP_AND_DYL_X:
        case OP_AND_DYL_M:
        case OP_AND_DYL_MX:
            TRAP;
            break;
        case OP_SEC:
        case OP_SEC_X:
        case OP_SEC_M:
        case OP_SEC_MX:
            cpu.p |= CPU_FLAG_C;
            break;
        case OP_AND_AY:
        case OP_AND_AY_X:
        case OP_AND_AY_M:
        case OP_AND_AY_MX:
            TRAP;
            break;
        case OP_DEC_AC:
        case OP_DEC_AC_X:
        case OP_DEC_AC_M:
        case OP_DEC_AC_MX:
            TRAP;
            break;
        case OP_TSC:
        case OP_TSC_X:
        case OP_TSC_M:
        case OP_TSC_MX:
            TRAP;
            break;
        case OP_BIT_AX:
        case OP_BIT_AX_X:
        case OP_BIT_AX_M:
        case OP_BIT_AX_MX:
            TRAP;
            break;
        case OP_AND_AX:
        case OP_AND_AX_X:
        case OP_AND_AX_M:
        case OP_AND_AX_MX:
            TRAP;
            break;
        case OP_ROL_AX:
        case OP_ROL_AX_X:
        case OP_ROL_AX_M:
        case OP_ROL_AX_MX:
            TRAP;
            break;
        case OP_AND_AXL:
        case OP_AND_AXL_X:
        case OP_AND_AXL_M:
        case OP_AND_AXL_MX:
            TRAP;
            break;
        case OP_RTI_S:
        case OP_RTI_S_X:
        case OP_RTI_S_M:
        case OP_RTI_S_MX:
            TRAP;
            break;
        case OP_EOR_DXI:
        case OP_EOR_DXI_X:
        case OP_EOR_DXI_M:
        case OP_EOR_DXI_MX:
            TRAP;
            break;
        case OP_WDM:
        case OP_WDM_X:
        case OP_WDM_M:
        case OP_WDM_MX:
            TRAP;
            break;
        case OP_EOR_DS:
        case OP_EOR_DS_X:
        case OP_EOR_DS_M:
        case OP_EOR_DS_MX:
            TRAP;
            break;
        case OP_MVP:
        case OP_MVP_X:
        case OP_MVP_M:
        case OP_MVP_MX:
            TRAP;
            break;
        case OP_EOR_D:
        case OP_EOR_D_X:
        case OP_EOR_D_M:
        case OP_EOR_D_MX:
            TRAP;
            break;
        case OP_LSR_D:
        case OP_LSR_D_X:
        case OP_LSR_D_M:
        case OP_LSR_D_MX:
            TRAP;
            break;
        case OP_EOR_DL:
        case OP_EOR_DL_X:
        case OP_EOR_DL_M:
        case OP_EOR_DL_MX:
            TRAP;
            break;
        case OP_PHA_S:
        case OP_PHA_S_X:
        case OP_PHA_S_M:
        case OP_PHA_S_MX:
            TRAP;
            break;
        case OP_EOR_IMM:
        case OP_EOR_IMM_X:
        case OP_EOR_IMM_M:
        case OP_EOR_IMM_MX:
            TRAP;
            break;
        case OP_LSR_AC:
        case OP_LSR_AC_X:
        case OP_LSR_AC_M:
        case OP_LSR_AC_MX:
            TRAP;
            break;
        case OP_PHK_S:
        case OP_PHK_S_X:
        case OP_PHK_S_M:
        case OP_PHK_S_MX:
            TRAP;
            break;
        case OP_JMP_A:
        case OP_JMP_A_X:
        case OP_JMP_A_M:
        case OP_JMP_A_MX:
            TRAP;
            break;
        case OP_EOR_A:
        case OP_EOR_A_X:
        case OP_EOR_A_M:
        case OP_EOR_A_MX:
            TRAP;
            break;
        case OP_LSR_A:
        case OP_LSR_A_X:
        case OP_LSR_A_M:
        case OP_LSR_A_MX:
            TRAP;
            break;
        case OP_EOR_AL:
        case OP_EOR_AL_X:
        case OP_EOR_AL_M:
        case OP_EOR_AL_MX:
            TRAP;
            break;
        case OP_BVC_R:
        case OP_BVC_R_X:
        case OP_BVC_R_M:
        case OP_BVC_R_MX:
            TRAP;
            break;
        case OP_EOR_DYI:
        case OP_EOR_DYI_X:
        case OP_EOR_DYI_M:
        case OP_EOR_DYI_MX:
            TRAP;
            break;
        case OP_EOR_DI:
        case OP_EOR_DI_X:
        case OP_EOR_DI_M:
        case OP_EOR_DI_MX:
            TRAP;
            break;
        case OP_EOR_DYSI:
        case OP_EOR_DYSI_X:
        case OP_EOR_DYSI_M:
        case OP_EOR_DYSI_MX:
            TRAP;
            break;
        case OP_MVN:
        case OP_MVN_X:
        case OP_MVN_M:
        case OP_MVN_MX:
            TRAP;
            break;
        case OP_EOR_DX:
        case OP_EOR_DX_X:
        case OP_EOR_DX_M:
        case OP_EOR_DX_MX:
            TRAP;
            break;
        case OP_LSR_DX:
        case OP_LSR_DX_X:
        case OP_LSR_DX_M:
        case OP_LSR_DX_MX:
            TRAP;
            break;
        case OP_EOR_DYL:
        case OP_EOR_DYL_X:
        case OP_EOR_DYL_M:
        case OP_EOR_DYL_MX:
            TRAP;
            break;
        case OP_CLI:
        case OP_CLI_X:
        case OP_CLI_M:
        case OP_CLI_MX:
            TRAP;
            break;
        case OP_EOR_AY:
        case OP_EOR_AY_X:
        case OP_EOR_AY_M:
        case OP_EOR_AY_MX:
            TRAP;
            break;
        case OP_PHY_S:
        case OP_PHY_S_X:
        case OP_PHY_S_M:
        case OP_PHY_S_MX:
            TRAP;
            break;
        case OP_TCD:
        case OP_TCD_X:
        case OP_TCD_M:
        case OP_TCD_MX:
            cpu.d = cpu.ac.u16;
            FLAGS16_NZ(cpu.d);
            break;
        case OP_JMP_AL:
        case OP_JMP_AL_X:
        case OP_JMP_AL_M:
        case OP_JMP_AL_MX:
            TRAP;
            break;
        case OP_EOR_AX:
        case OP_EOR_AX_X:
        case OP_EOR_AX_M:
        case OP_EOR_AX_MX:
            TRAP;
            break;
        case OP_LSR_AX:
        case OP_LSR_AX_X:
        case OP_LSR_AX_M:
        case OP_LSR_AX_MX:
            TRAP;
            break;
        case OP_EOR_AXL:
        case OP_EOR_AXL_X:
        case OP_EOR_AXL_M:
        case OP_EOR_AXL_MX:
            TRAP;
            break;
        case OP_RTS_S:
        case OP_RTS_S_X:
        case OP_RTS_S_M:
        case OP_RTS_S_MX:
            TRAP;
            break;
        case OP_ADC_DXI:
        case OP_ADC_DXI_X:
        case OP_ADC_DXI_M:
        case OP_ADC_DXI_MX:
            TRAP;
            break;
        case OP_PER_S:
        case OP_PER_S_X:
        case OP_PER_S_M:
        case OP_PER_S_MX:
            TRAP;
            break;
        case OP_ADC_DS:
        case OP_ADC_DS_X:
        case OP_ADC_DS_M:
        case OP_ADC_DS_MX:
            TRAP;
            break;
        case OP_STZ_D:
        case OP_STZ_D_X:
        case OP_STZ_D_M:
        case OP_STZ_D_MX:
            TRAP;
            break;
        case OP_ADC_D:
        case OP_ADC_D_X:
        case OP_ADC_D_M:
        case OP_ADC_D_MX:
            TRAP;
            break;
        case OP_ROR_D:
        case OP_ROR_D_X:
        case OP_ROR_D_M:
        case OP_ROR_D_MX:
            TRAP;
            break;
        case OP_ADC_DL:
        case OP_ADC_DL_X:
        case OP_ADC_DL_M:
        case OP_ADC_DL_MX:
            TRAP;
            break;
        case OP_PLA_S:
        case OP_PLA_S_X:
        case OP_PLA_S_M:
        case OP_PLA_S_MX:
            TRAP;
            break;
        case OP_ADC_IMM:
        case OP_ADC_IMM_X:
        case OP_ADC_IMM_M:
        case OP_ADC_IMM_MX:
            TRAP;
            break;
        case OP_ROR_AC:
        case OP_ROR_AC_X:
        case OP_ROR_AC_M:
        case OP_ROR_AC_MX:
            TRAP;
            break;
        case OP_RTL_S:
        case OP_RTL_S_X:
        case OP_RTL_S_M:
        case OP_RTL_S_MX:
            TRAP;
            break;
        case OP_JMP_AI:
        case OP_JMP_AI_X:
        case OP_JMP_AI_M:
        case OP_JMP_AI_MX:
            TRAP;
            break;
        case OP_ADC_A:
        case OP_ADC_A_X:
        case OP_ADC_A_M:
        case OP_ADC_A_MX:
            TRAP;
            break;
        case OP_ROR_A:
        case OP_ROR_A_X:
        case OP_ROR_A_M:
        case OP_ROR_A_MX:
            TRAP;
            break;
        case OP_ADC_AL:
        case OP_ADC_AL_X:
        case OP_ADC_AL_M:
        case OP_ADC_AL_MX:
            TRAP;
            break;
        case OP_BVS_R:
        case OP_BVS_R_X:
        case OP_BVS_R_M:
        case OP_BVS_R_MX:
            TRAP;
            break;
        case OP_ADC_DYI:
        case OP_ADC_DYI_X:
        case OP_ADC_DYI_M:
        case OP_ADC_DYI_MX:
            TRAP;
            break;
        case OP_ADC_DI:
        case OP_ADC_DI_X:
        case OP_ADC_DI_M:
        case OP_ADC_DI_MX:
            TRAP;
            break;
        case OP_ADC_DYSI:
        case OP_ADC_DYSI_X:
        case OP_ADC_DYSI_M:
        case OP_ADC_DYSI_MX:
            TRAP;
            break;
        case OP_STZ_DX:
        case OP_STZ_DX_X:
        case OP_STZ_DX_M:
        case OP_STZ_DX_MX:
            TRAP;
            break;
        case OP_ADC_DX:
        case OP_ADC_DX_X:
        case OP_ADC_DX_M:
        case OP_ADC_DX_MX:
            TRAP;
            break;
        case OP_ROR_DX:
        case OP_ROR_DX_X:
        case OP_ROR_DX_M:
        case OP_ROR_DX_MX:
            TRAP;
            break;
        case OP_ADC_DYL:
        case OP_ADC_DYL_X:
        case OP_ADC_DYL_M:
        case OP_ADC_DYL_MX:
            TRAP;
            break;
        case OP_SEI:
        case OP_SEI_X:
        case OP_SEI_M:
        case OP_SEI_MX:
            cpu.p |= CPU_FLAG_I;
            break;
        case OP_ADC_AY:
        case OP_ADC_AY_X:
        case OP_ADC_AY_M:
        case OP_ADC_AY_MX:
            TRAP;
            break;
        case OP_PLY_S:
        case OP_PLY_S_X:
        case OP_PLY_S_M:
        case OP_PLY_S_MX:
            TRAP;
            break;
        case OP_TDC:
        case OP_TDC_X:
        case OP_TDC_M:
        case OP_TDC_MX:
            TRAP;
            break;
        case OP_JMP_AXI:
        case OP_JMP_AXI_X:
        case OP_JMP_AXI_M:
        case OP_JMP_AXI_MX:
            TRAP;
            break;
        case OP_ADC_AX:
        case OP_ADC_AX_X:
        case OP_ADC_AX_M:
        case OP_ADC_AX_MX:
            TRAP;
            break;
        case OP_ROR_AX:
        case OP_ROR_AX_X:
        case OP_ROR_AX_M:
        case OP_ROR_AX_MX:
            TRAP;
            break;
        case OP_ADC_AXL:
        case OP_ADC_AXL_X:
        case OP_ADC_AXL_M:
        case OP_ADC_AXL_MX:
            TRAP;
            break;
        case OP_BRA_R:
        case OP_BRA_R_X:
        case OP_BRA_R_M:
        case OP_BRA_R_MX:
            TRAP;
            break;
        case OP_STA_DXI:
        case OP_STA_DXI_X:
        case OP_STA_DXI_M:
        case OP_STA_DXI_MX:
            TRAP;
            break;
        case OP_BRL_RL:
        case OP_BRL_RL_X:
        case OP_BRL_RL_M:
        case OP_BRL_RL_MX:
            TRAP;
            break;
        case OP_STA_DS:
        case OP_STA_DS_X:
        case OP_STA_DS_M:
        case OP_STA_DS_MX:
            TRAP;
            break;
        case OP_STY_D:
        case OP_STY_D_X:
        case OP_STY_D_M:
        case OP_STY_D_MX:
            TRAP;
            break;
        case OP_STA_D:
        case OP_STA_D_X:
        case OP_STA_D_M:
        case OP_STA_D_MX:
            TRAP;
            break;
        case OP_STX_D:
        case OP_STX_D_X:
        case OP_STX_D_M:
        case OP_STX_D_MX:
            TRAP;
            break;
        case OP_STA_DL:
        case OP_STA_DL_X:
        case OP_STA_DL_M:
        case OP_STA_DL_MX:
            TRAP;
            break;
        case OP_DEY:
        case OP_DEY_X:
        case OP_DEY_M:
        case OP_DEY_MX:
            TRAP;
            break;
        case OP_BIT_IMM:
        case OP_BIT_IMM_X:
        case OP_BIT_IMM_M:
        case OP_BIT_IMM_MX:
            TRAP;
            break;
        case OP_TXA:
        case OP_TXA_X:
        case OP_TXA_M:
        case OP_TXA_MX:
            TRAP;
            break;
        case OP_PHB_S:
        case OP_PHB_S_X:
        case OP_PHB_S_M:
        case OP_PHB_S_MX:
            TRAP;
            break;
        case OP_STY_A:
        case OP_STY_A_X:
        case OP_STY_A_M:
        case OP_STY_A_MX:
            TRAP;
            break;
        case OP_STA_A:
        case OP_STA_A_X:
            READ_A16();
            biMemoryWrite16(ctx, cpu.dbr, a16, cpu.ac.u16);
            break;
        case OP_STA_A_M:
        case OP_STA_A_MX:
            READ_A16();
            biMemoryWrite8(ctx, cpu.dbr, a16, cpu.ac.lo_u8);
            break;
        case OP_STX_A:
        case OP_STX_A_X:
        case OP_STX_A_M:
        case OP_STX_A_MX:
            TRAP;
            break;
        case OP_STA_AL:
        case OP_STA_AL_X:
            READ_A16();
            READ_A8();
            biMemoryWrite16(ctx, a8, a16, cpu.ac.u16);
            break;
        case OP_STA_AL_M:
        case OP_STA_AL_MX:
            READ_A16();
            READ_A8();
            biMemoryWrite8(ctx, a8, a16, cpu.ac.lo_u8);
            break;
        case OP_BCC_R:
        case OP_BCC_R_X:
        case OP_BCC_R_M:
        case OP_BCC_R_MX:
            TRAP;
            break;
        case OP_STA_DYI:
        case OP_STA_DYI_X:
        case OP_STA_DYI_M:
        case OP_STA_DYI_MX:
            TRAP;
            break;
        case OP_STA_DI:
        case OP_STA_DI_X:
        case OP_STA_DI_M:
        case OP_STA_DI_MX:
            TRAP;
            break;
        case OP_STA_DYSI:
        case OP_STA_DYSI_X:
        case OP_STA_DYSI_M:
        case OP_STA_DYSI_MX:
            TRAP;
            break;
        case OP_STY_DX:
        case OP_STY_DX_X:
        case OP_STY_DX_M:
        case OP_STY_DX_MX:
            TRAP;
            break;
        case OP_STA_DX:
        case OP_STA_DX_X:
        case OP_STA_DX_M:
        case OP_STA_DX_MX:
            TRAP;
            break;
        case OP_STX_DY:
        case OP_STX_DY_X:
        case OP_STX_DY_M:
        case OP_STX_DY_MX:
            TRAP;
            break;
        case OP_STA_DYL:
        case OP_STA_DYL_X:
        case OP_STA_DYL_M:
        case OP_STA_DYL_MX:
            TRAP;
            break;
        case OP_TYA:
        case OP_TYA_X:
            cpu.ac.u16 = cpu.y.u16;
            FLAGS16_NZ(cpu.ac.u16);
            break;
        case OP_TYA_M:
        case OP_TYA_MX:
            cpu.ac.lo_u8 = cpu.y.lo_u8;
            FLAGS8_NZ(cpu.ac.lo_u8);
            break;
        case OP_STA_AY:
        case OP_STA_AY_X:
        case OP_STA_AY_M:
        case OP_STA_AY_MX:
            TRAP;
            break;
        case OP_TXS:
        case OP_TXS_X:
        case OP_TXS_M:
        case OP_TXS_MX:
            TRAP;
            break;
        case OP_TXY:
        case OP_TXY_X:
        case OP_TXY_M:
        case OP_TXY_MX:
            TRAP;
            break;
        case OP_STZ_A:
        case OP_STZ_A_X:
            READ_A16();
            biMemoryWrite16(ctx, cpu.dbr, a16, 0);
            break;
        case OP_STZ_A_M:
        case OP_STZ_A_MX:
            READ_A16();
            biMemoryWrite8(ctx, cpu.dbr, a16, 0);
            break;
        case OP_STA_AX:
        case OP_STA_AX_X:
        case OP_STA_AX_M:
        case OP_STA_AX_MX:
            TRAP;
            break;
        case OP_STZ_AX:
        case OP_STZ_AX_X:
        case OP_STZ_AX_M:
        case OP_STZ_AX_MX:
            TRAP;
            break;
        case OP_STA_AXL:
        case OP_STA_AXL_X:
            READ_A24();
            a24 += cpu.x.u16;
            biMemoryLinearWrite16(ctx, a24, cpu.ac.u16);
            break;
        case OP_STA_AXL_M:
        case OP_STA_AXL_MX:
            READ_A24();
            a24 += cpu.x.u16;
            biMemoryLinearWrite8(ctx, a24, cpu.ac.lo_u8);
            break;
        case OP_LDY_IMM:
        case OP_LDY_IMM_M:
            READ_A16();
            cpu.y.u16 = a16;
            FLAGS16_NZ(a16);
            break;
        case OP_LDY_IMM_X:
        case OP_LDY_IMM_MX:
            READ_A8();
            cpu.y.u16 = a8;
            FLAGS8_NZ(a8);
            break;
        case OP_LDA_DXI:
        case OP_LDA_DXI_X:
        case OP_LDA_DXI_M:
        case OP_LDA_DXI_MX:
            TRAP;
            break;
        case OP_LDX_IMM:
        case OP_LDX_IMM_M:
            READ_A16();
            cpu.x.u16 = a16;
            FLAGS16_NZ(a16);
            break;
        case OP_LDX_IMM_X:
        case OP_LDX_IMM_MX:
            READ_A8();
            cpu.x.u16 = a8;
            FLAGS8_NZ(a8);
            break;
        case OP_LDA_DS:
        case OP_LDA_DS_X:
        case OP_LDA_DS_M:
        case OP_LDA_DS_MX:
            TRAP;
            break;
        case OP_LDY_D:
        case OP_LDY_D_X:
        case OP_LDY_D_M:
        case OP_LDY_D_MX:
            TRAP;
            break;
        case OP_LDA_D:
        case OP_LDA_D_X:
        case OP_LDA_D_M:
        case OP_LDA_D_MX:
            TRAP;
            break;
        case OP_LDX_D:
        case OP_LDX_D_X:
        case OP_LDX_D_M:
        case OP_LDX_D_MX:
            TRAP;
            break;
        case OP_LDA_DL:
        case OP_LDA_DL_X:
        case OP_LDA_DL_M:
        case OP_LDA_DL_MX:
            TRAP;
            break;
        case OP_TAY:
            cpu.y.u16 = cpu.ac.u16;
            FLAGS16_NZ(cpu.y.u16);
            break;
        case OP_TAY_M:
            cpu.y.u16 = cpu.ac.lo_u8;
            FLAGS16_NZ(cpu.y.u16);
            break;
        case OP_TAY_X:
        case OP_TAY_MX:
            cpu.y.lo_u8 = cpu.ac.lo_u8;
            FLAGS8_NZ(cpu.y.lo_u8);
            break;
        case OP_LDA_IMM:
        case OP_LDA_IMM_X:
            READ_A16();
            cpu.ac.u16 = a16;
            FLAGS16_NZ(a16);
            break;
        case OP_LDA_IMM_M:
        case OP_LDA_IMM_MX:
            READ_A8();
            cpu.ac.lo_u8 = a8;
            FLAGS8_NZ(a8);
            break;
        case OP_TAX:
        case OP_TAX_X:
        case OP_TAX_M:
        case OP_TAX_MX:
            TRAP;
            break;
        case OP_PLB_S:
        case OP_PLB_S_X:
        case OP_PLB_S_M:
        case OP_PLB_S_MX:
            TRAP;
            break;
        case OP_LDY_A:
        case OP_LDY_A_X:
        case OP_LDY_A_M:
        case OP_LDY_A_MX:
            TRAP;
            break;
        case OP_LDA_A:
        case OP_LDA_A_X:
        case OP_LDA_A_M:
        case OP_LDA_A_MX:
            TRAP;
            break;
        case OP_LDX_A:
        case OP_LDX_A_X:
        case OP_LDX_A_M:
        case OP_LDX_A_MX:
            TRAP;
            break;
        case OP_LDA_AL:
        case OP_LDA_AL_X:
        case OP_LDA_AL_M:
        case OP_LDA_AL_MX:
            TRAP;
            break;
        case OP_BCS_R:
        case OP_BCS_R_X:
        case OP_BCS_R_M:
        case OP_BCS_R_MX:
            TRAP;
            break;
        case OP_LDA_DYI:
        case OP_LDA_DYI_X:
        case OP_LDA_DYI_M:
        case OP_LDA_DYI_MX:
            TRAP;
            break;
        case OP_LDA_DI:
        case OP_LDA_DI_X:
        case OP_LDA_DI_M:
        case OP_LDA_DI_MX:
            TRAP;
            break;
        case OP_LDA_DYSI:
        case OP_LDA_DYSI_X:
        case OP_LDA_DYSI_M:
        case OP_LDA_DYSI_MX:
            TRAP;
            break;
        case OP_LDY_DX:
        case OP_LDY_DX_X:
        case OP_LDY_DX_M:
        case OP_LDY_DX_MX:
            TRAP;
            break;
        case OP_LDA_DX:
        case OP_LDA_DX_X:
        case OP_LDA_DX_M:
        case OP_LDA_DX_MX:
            TRAP;
            break;
        case OP_LDX_DY:
        case OP_LDX_DY_X:
        case OP_LDX_DY_M:
        case OP_LDX_DY_MX:
            TRAP;
            break;
        case OP_LDA_DYL:
        case OP_LDA_DYL_X:
        case OP_LDA_DYL_M:
        case OP_LDA_DYL_MX:
            TRAP;
            break;
        case OP_CLV:
        case OP_CLV_X:
        case OP_CLV_M:
        case OP_CLV_MX:
            TRAP;
            break;
        case OP_LDA_AY:
        case OP_LDA_AY_X:
        case OP_LDA_AY_M:
        case OP_LDA_AY_MX:
            TRAP;
            break;
        case OP_TSX:
        case OP_TSX_X:
        case OP_TSX_M:
        case OP_TSX_MX:
            TRAP;
            break;
        case OP_TYX:
        case OP_TYX_X:
        case OP_TYX_M:
        case OP_TYX_MX:
            TRAP;
            break;
        case OP_LDY_AX:
        case OP_LDY_AX_X:
        case OP_LDY_AX_M:
        case OP_LDY_AX_MX:
            TRAP;
            break;
        case OP_LDA_AX:
        case OP_LDA_AX_X:
        case OP_LDA_AX_M:
        case OP_LDA_AX_MX:
            TRAP;
            break;
        case OP_LDX_AY:
        case OP_LDX_AY_X:
        case OP_LDX_AY_M:
        case OP_LDX_AY_MX:
            TRAP;
            break;
        case OP_LDA_AXL:
        case OP_LDA_AXL_X:
        case OP_LDA_AXL_M:
        case OP_LDA_AXL_MX:
            TRAP;
            break;
        case OP_CPY_IMM:
        case OP_CPY_IMM_X:
        case OP_CPY_IMM_M:
        case OP_CPY_IMM_MX:
            TRAP;
            break;
        case OP_CMP_DXI:
        case OP_CMP_DXI_X:
        case OP_CMP_DXI_M:
        case OP_CMP_DXI_MX:
            TRAP;
            break;
        case OP_REP_IMM:
        case OP_REP_IMM_X:
        case OP_REP_IMM_M:
        case OP_REP_IMM_MX:
            READ_A8();
            cpu.p &= ~a8;
            if (cpu.e)
            {
                cpu.p |= (CPU_FLAG_M | CPU_FLAG_X);
            }
            break;
        case OP_CMP_DS:
        case OP_CMP_DS_X:
        case OP_CMP_DS_M:
        case OP_CMP_DS_MX:
            TRAP;
            break;
        case OP_CPY_D:
        case OP_CPY_D_X:
        case OP_CPY_D_M:
        case OP_CPY_D_MX:
            TRAP;
            break;
        case OP_CMP_D:
        case OP_CMP_D_X:
        case OP_CMP_D_M:
        case OP_CMP_D_MX:
            TRAP;
            break;
        case OP_DEC_D:
        case OP_DEC_D_X:
        case OP_DEC_D_M:
        case OP_DEC_D_MX:
            TRAP;
            break;
        case OP_CMP_DL:
        case OP_CMP_DL_X:
        case OP_CMP_DL_M:
        case OP_CMP_DL_MX:
            TRAP;
            break;
        case OP_INY:
        case OP_INY_X:
        case OP_INY_M:
        case OP_INY_MX:
            TRAP;
            break;
        case OP_CMP_IMM:
        case OP_CMP_IMM_X:
        case OP_CMP_IMM_M:
        case OP_CMP_IMM_MX:
            TRAP;
            break;
        case OP_DEX:
        case OP_DEX_M:
            cpu.x.u16--;
            FLAGS16_NZ(cpu.x.u16);
            break;
        case OP_DEX_X:
        case OP_DEX_MX:
            cpu.x.lo_u8--;
            FLAGS8_NZ(cpu.x.lo_u8);
            break;
        case OP_WAI:
        case OP_WAI_X:
        case OP_WAI_M:
        case OP_WAI_MX:
            TRAP;
            break;
        case OP_CPY_A:
        case OP_CPY_A_X:
        case OP_CPY_A_M:
        case OP_CPY_A_MX:
            TRAP;
            break;
        case OP_CMP_A:
        case OP_CMP_A_X:
        case OP_CMP_A_M:
        case OP_CMP_A_MX:
            TRAP;
            break;
        case OP_DEC_A:
        case OP_DEC_A_X:
        case OP_DEC_A_M:
        case OP_DEC_A_MX:
            TRAP;
            break;
        case OP_CMP_AL:
        case OP_CMP_AL_X:
        case OP_CMP_AL_M:
        case OP_CMP_AL_MX:
            TRAP;
            break;
        case OP_BNE_R:
        case OP_BNE_R_X:
        case OP_BNE_R_M:
        case OP_BNE_R_MX:
            TRAP;
            break;
        case OP_CMP_DYI:
        case OP_CMP_DYI_X:
        case OP_CMP_DYI_M:
        case OP_CMP_DYI_MX:
            TRAP;
            break;
        case OP_CMP_DI:
        case OP_CMP_DI_X:
        case OP_CMP_DI_M:
        case OP_CMP_DI_MX:
            TRAP;
            break;
        case OP_CMP_DYSI:
        case OP_CMP_DYSI_X:
        case OP_CMP_DYSI_M:
        case OP_CMP_DYSI_MX:
            TRAP;
            break;
        case OP_PEI_S:
        case OP_PEI_S_X:
        case OP_PEI_S_M:
        case OP_PEI_S_MX:
            TRAP;
            break;
        case OP_CMP_DX:
        case OP_CMP_DX_X:
        case OP_CMP_DX_M:
        case OP_CMP_DX_MX:
            TRAP;
            break;
        case OP_DEC_DX:
        case OP_DEC_DX_X:
        case OP_DEC_DX_M:
        case OP_DEC_DX_MX:
            TRAP;
            break;
        case OP_CMP_DYL:
        case OP_CMP_DYL_X:
        case OP_CMP_DYL_M:
        case OP_CMP_DYL_MX:
            TRAP;
            break;
        case OP_CLD:
        case OP_CLD_X:
        case OP_CLD_M:
        case OP_CLD_MX:
            TRAP;
            break;
        case OP_CMP_AY:
        case OP_CMP_AY_X:
        case OP_CMP_AY_M:
        case OP_CMP_AY_MX:
            TRAP;
            break;
        case OP_PHX_S:
        case OP_PHX_S_X:
        case OP_PHX_S_M:
        case OP_PHX_S_MX:
            TRAP;
            break;
        case OP_STP:
        case OP_STP_X:
        case OP_STP_M:
        case OP_STP_MX:
            TRAP;
            break;
        case OP_JML_AI:
        case OP_JML_AI_X:
        case OP_JML_AI_M:
        case OP_JML_AI_MX:
            TRAP;
            break;
        case OP_CMP_AX:
        case OP_CMP_AX_X:
        case OP_CMP_AX_M:
        case OP_CMP_AX_MX:
            TRAP;
            break;
        case OP_DEC_AX:
        case OP_DEC_AX_X:
        case OP_DEC_AX_M:
        case OP_DEC_AX_MX:
            TRAP;
            break;
        case OP_CML_AXL:
        case OP_CML_AXL_X:
        case OP_CML_AXL_M:
        case OP_CML_AXL_MX:
            TRAP;
            break;
        case OP_CPX_IMM:
        case OP_CPX_IMM_X:
        case OP_CPX_IMM_M:
        case OP_CPX_IMM_MX:
            TRAP;
            break;
        case OP_SBC_DXI:
        case OP_SBC_DXI_X:
        case OP_SBC_DXI_M:
        case OP_SBC_DXI_MX:
            TRAP;
            break;
        case OP_SEP_IMM:
        case OP_SEP_IMM_X:
        case OP_SEP_IMM_M:
        case OP_SEP_IMM_MX:
            READ_A8();
            cpu.p |= a8;
            break;
        case OP_SBC_DS:
        case OP_SBC_DS_X:
        case OP_SBC_DS_M:
        case OP_SBC_DS_MX:
            TRAP;
            break;
        case OP_CPX_D:
        case OP_CPX_D_X:
        case OP_CPX_D_M:
        case OP_CPX_D_MX:
            TRAP;
            break;
        case OP_SBC_D:
        case OP_SBC_D_X:
        case OP_SBC_D_M:
        case OP_SBC_D_MX:
            TRAP;
            break;
        case OP_INC_D:
        case OP_INC_D_X:
        case OP_INC_D_M:
        case OP_INC_D_MX:
            TRAP;
            break;
        case OP_SBC_DL:
        case OP_SBC_DL_X:
        case OP_SBC_DL_M:
        case OP_SBC_DL_MX:
            TRAP;
            break;
        case OP_INX:
        case OP_INX_X:
        case OP_INX_M:
        case OP_INX_MX:
            TRAP;
            break;
        case OP_SBC_IMM:
        case OP_SBC_IMM_X:
            READ_A16();
            ADC16(cpu.ac.u16, ~a16);
            cpu.ac.u16 = r16;
            break;
        case OP_SBC_IMM_M:
        case OP_SBC_IMM_MX:
            READ_A8();
            ADC8(cpu.ac.lo_u8, ~a8);
            cpu.ac.lo_u8 = r8;
            break;
        case OP_NOP:
        case OP_NOP_X:
        case OP_NOP_M:
        case OP_NOP_MX:
            TRAP;
            break;
        case OP_XBA:
        case OP_XBA_X:
        case OP_XBA_M:
        case OP_XBA_MX:
            TRAP;
            break;
        case OP_CPX_A:
        case OP_CPX_A_X:
        case OP_CPX_A_M:
        case OP_CPX_A_MX:
            TRAP;
            break;
        case OP_SBC_A:
        case OP_SBC_A_X:
        case OP_SBC_A_M:
        case OP_SBC_A_MX:
            TRAP;
            break;
        case OP_INC_A:
        case OP_INC_A_X:
        case OP_INC_A_M:
        case OP_INC_A_MX:
            TRAP;
            break;
        case OP_SBC_AL:
        case OP_SBC_AL_X:
        case OP_SBC_AL_M:
        case OP_SBC_AL_MX:
            TRAP;
            break;
        case OP_BEQ_R:
        case OP_BEQ_R_X:
        case OP_BEQ_R_M:
        case OP_BEQ_R_MX:
            TRAP;
            break;
        case OP_SBC_DYI:
        case OP_SBC_DYI_X:
        case OP_SBC_DYI_M:
        case OP_SBC_DYI_MX:
            TRAP;
            break;
        case OP_SBC_DI:
        case OP_SBC_DI_X:
        case OP_SBC_DI_M:
        case OP_SBC_DI_MX:
            TRAP;
            break;
        case OP_SBC_DYSI:
        case OP_SBC_DYSI_X:
        case OP_SBC_DYSI_M:
        case OP_SBC_DYSI_MX:
            TRAP;
            break;
        case OP_PEA_S:
        case OP_PEA_S_X:
        case OP_PEA_S_M:
        case OP_PEA_S_MX:
            TRAP;
            break;
        case OP_SBC_DX:
        case OP_SBC_DX_X:
        case OP_SBC_DX_M:
        case OP_SBC_DX_MX:
            TRAP;
            break;
        case OP_INC_DX:
        case OP_INC_DX_X:
        case OP_INC_DX_M:
        case OP_INC_DX_MX:
            TRAP;
            break;
        case OP_SBC_DYL:
        case OP_SBC_DYL_X:
        case OP_SBC_DYL_M:
        case OP_SBC_DYL_MX:
            TRAP;
            break;
        case OP_SED:
        case OP_SED_X:
        case OP_SED_M:
        case OP_SED_MX:
            TRAP;
            break;
        case OP_SBC_AY:
        case OP_SBC_AY_X:
        case OP_SBC_AY_M:
        case OP_SBC_AY_MX:
            TRAP;
            break;
        case OP_PLX_S:
        case OP_PLX_S_X:
        case OP_PLX_S_M:
        case OP_PLX_S_MX:
            TRAP;
            break;
        case OP_XCE:
        case OP_XCE_X:
        case OP_XCE_M:
        case OP_XCE_MX:
            a8 = cpu.e;
            cpu.e = cpu.p & CPU_FLAG_C;
            cpu.p &= ~CPU_FLAG_C;
            cpu.p |= a8;
            if (cpu.e)
            {
                cpu.p |= (CPU_FLAG_M | CPU_FLAG_X);
            }
            break;
        case OP_JSR_AXI:
        case OP_JSR_AXI_X:
        case OP_JSR_AXI_M:
        case OP_JSR_AXI_MX:
            TRAP;
            break;
        case OP_SBC_AX:
        case OP_SBC_AX_X:
        case OP_SBC_AX_M:
        case OP_SBC_AX_MX:
            TRAP;
            break;
        case OP_INC_AX:
        case OP_INC_AX_X:
        case OP_INC_AX_M:
        case OP_INC_AX_MX:
            TRAP;
            break;
        case OP_SBC_AXL:
        case OP_SBC_AXL_X:
        case OP_SBC_AXL_M:
        case OP_SBC_AXL_MX:
            TRAP;
            break;
        }
    }

    memcpy(&ctx->cpu, &cpu, sizeof(cpu));
}
