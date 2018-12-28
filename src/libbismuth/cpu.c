#include <stdio.h>
#include <string.h>
#include <libbismuth/libbismuth.h>

#define TRAP    do { printf("Bad opcode: 0x%02x at 0x%02x%04x\n", op, cpu.pbr, pcBak); getchar(); } while (0);

void biRunCycles(BiContext* ctx, size_t cycles)
{
    BiCPU cpu;
    uint16_t pcBak;
    uint8_t op;

    memcpy(&cpu, &ctx->cpu, sizeof(cpu));
    for (size_t cycleCounter = 0; cycleCounter < cycles; ++cycleCounter)
    {
        pcBak = cpu.pc;
        op = biMemoryRead8(ctx, cpu.pbr, cpu.pc);
        cpu.pc++;
        switch (op)
        {
        default:
            TRAP;
            break;
        case OP_BRK_S:
            TRAP;
            break;
        case OP_ORA_DXI:
            TRAP;
            break;
        case OP_COP_S:
            TRAP;
            break;
        case OP_ORA_DS:
            TRAP;
            break;
        case OP_TBS_D:
            TRAP;
            break;
        case OP_ORA_D:
            TRAP;
            break;
        case OP_ASL_D:
            TRAP;
            break;
        case OP_ORA_DL:
            TRAP;
            break;
        case OP_PHP_S:
            TRAP;
            break;
        case OP_ORA_IMM:
            TRAP;
            break;
        case OP_ASL_AC:
            TRAP;
            break;
        case OP_PHD_S:
            TRAP;
            break;
        case OP_TSB_A:
            TRAP;
            break;
        case OP_ORA_A:
            TRAP;
            break;
        case OP_ASL_A:
            TRAP;
            break;
        case OP_ORA_AL:
            TRAP;
            break;
        case OP_BPL_R:
            TRAP;
            break;
        case OP_ORA_DYI:
            TRAP;
            break;
        case OP_ORA_DI:
            TRAP;
            break;
        case OP_ORA_DYSI:
            TRAP;
            break;
        case OP_TRB_D:
            TRAP;
            break;
        case OP_ORA_DX:
            TRAP;
            break;
        case OP_ASL_DX:
            TRAP;
            break;
        case OP_ORA_DYL:
            TRAP;
            break;
        case OP_CLC:
            TRAP;
            break;
        case OP_ORA_AY:
            TRAP;
            break;
        case OP_INC_AC:
            TRAP;
            break;
        case OP_TCS:
            TRAP;
            break;
        case OP_TRB_A:
            TRAP;
            break;
        case OP_ORA_AX:
            TRAP;
            break;
        case OP_ASL_AX:
            TRAP;
            break;
        case OP_ORA_AXL:
            TRAP;
            break;
        case OP_JSR_A:
            TRAP;
            break;
        case OP_AND_DXI:
            TRAP;
            break;
        case OP_JSL_AL:
            TRAP;
            break;
        case OP_AND_DS:
            TRAP;
            break;
        case OP_BIT_D:
            TRAP;
            break;
        case OP_AND_D:
            TRAP;
            break;
        case OP_ROL_D:
            TRAP;
            break;
        case OP_AND_DL:
            TRAP;
            break;
        case OP_PLP_S:
            TRAP;
            break;
        case OP_AND_IMM:
            TRAP;
            break;
        case OP_ROL_AC:
            TRAP;
            break;
        case OP_PLD_S:
            TRAP;
            break;
        case OP_BIT_A:
            TRAP;
            break;
        case OP_AND_A:
            TRAP;
            break;
        case OP_ROL_A:
            TRAP;
            break;
        case OP_AND_AL:
            TRAP;
            break;
        case OP_BMI_R:
            TRAP;
            break;
        case OP_AND_DYI:
            TRAP;
            break;
        case OP_AND_DI:
            TRAP;
            break;
        case OP_AND_DYSI:
            TRAP;
            break;
        case OP_BIT_DX:
            TRAP;
            break;
        case OP_AND_DX:
            TRAP;
            break;
        case OP_ROL_DX:
            TRAP;
            break;
        case OP_AND_DYL:
            TRAP;
            break;
        case OP_SEC :
            TRAP;
            break;
        case OP_AND_AY:
            TRAP;
            break;
        case OP_DEC_AC:
            TRAP;
            break;
        case OP_TSC :
            TRAP;
            break;
        case OP_BIT_AX:
            TRAP;
            break;
        case OP_AND_AX:
            TRAP;
            break;
        case OP_ROL_AX:
            TRAP;
            break;
        case OP_AND_AXL:
            TRAP;
            break;
        case OP_RTI_S:
            TRAP;
            break;
        case OP_EOR_DXI:
            TRAP;
            break;
        case OP_WDM :
            TRAP;
            break;
        case OP_EOR_DS:
            TRAP;
            break;
        case OP_MVP :
            TRAP;
            break;
        case OP_EOR_D:
            TRAP;
            break;
        case OP_LSR_D:
            TRAP;
            break;
        case OP_EOR_DL:
            TRAP;
            break;
        case OP_PHA_S:
            TRAP;
            break;
        case OP_EOR_IMM:
            TRAP;
            break;
        case OP_LSR_AC:
            TRAP;
            break;
        case OP_PHK_S:
            TRAP;
            break;
        case OP_JMP_A:
            TRAP;
            break;
        case OP_EOR_A:
            TRAP;
            break;
        case OP_LSR_A:
            TRAP;
            break;
        case OP_EOR_AL:
            TRAP;
            break;
        case OP_BVC_R:
            TRAP;
            break;
        case OP_EOR_DYI:
            TRAP;
            break;
        case OP_EOR_DI:
            TRAP;
            break;
        case OP_EOR_DYSI:
            TRAP;
            break;
        case OP_MVN :
            TRAP;
            break;
        case OP_EOR_DX:
            TRAP;
            break;
        case OP_LSR_DX:
            TRAP;
            break;
        case OP_EOR_DYL:
            TRAP;
            break;
        case OP_CLI :
            TRAP;
            break;
        case OP_EOR_AY:
            TRAP;
            break;
        case OP_PHY_S:
            TRAP;
            break;
        case OP_TCD :
            TRAP;
            break;
        case OP_JMP_AL:
            TRAP;
            break;
        case OP_EOR_AX:
            TRAP;
            break;
        case OP_LSR_AX:
            TRAP;
            break;
        case OP_EOR_AXL:
            TRAP;
            break;
        case OP_RTS_S:
            TRAP;
            break;
        case OP_ADC_DXI:
            TRAP;
            break;
        case OP_PER_S:
            TRAP;
            break;
        case OP_ADC_DS:
            TRAP;
            break;
        case OP_STZ_D:
            TRAP;
            break;
        case OP_ADC_D:
            TRAP;
            break;
        case OP_ROR_D:
            TRAP;
            break;
        case OP_ADC_DL:
            TRAP;
            break;
        case OP_PLA_S:
            TRAP;
            break;
        case OP_ADC_IMM:
            TRAP;
            break;
        case OP_ROR_AC:
            TRAP;
            break;
        case OP_RTL_S:
            TRAP;
            break;
        case OP_JMP_AI:
            TRAP;
            break;
        case OP_ADC_A:
            TRAP;
            break;
        case OP_ROR_A:
            TRAP;
            break;
        case OP_ADC_AL:
            TRAP;
            break;
        case OP_BVS_R:
            TRAP;
            break;
        case OP_ADC_DYI:
            TRAP;
            break;
        case OP_ADC_DI:
            TRAP;
            break;
        case OP_ADC_DYSI:
            TRAP;
            break;
        case OP_STZ_DX:
            TRAP;
            break;
        case OP_ADC_DX:
            TRAP;
            break;
        case OP_ROR_DX:
            TRAP;
            break;
        case OP_ADC_DYL:
            TRAP;
            break;
        case OP_SEI:
            cpu.p |= CPU_FLAG_I;
            break;
        case OP_ADC_AY:
            TRAP;
            break;
        case OP_PLY_S:
            TRAP;
            break;
        case OP_TDC:
            TRAP;
            break;
        case OP_JMP_AXI:
            TRAP;
            break;
        case OP_ADC_AX:
            TRAP;
            break;
        case OP_ROR_AX:
            TRAP;
            break;
        case OP_ADC_AXL:
            TRAP;
            break;
        }
    }

    memcpy(&ctx->cpu, &cpu, sizeof(cpu));
}
