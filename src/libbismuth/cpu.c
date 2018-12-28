#include <stdio.h>
#include <string.h>
#include <libbismuth/libbismuth.h>

#define TRAP        do { printf("Bad opcode: 0x%02x at 0x%02x%04x\n", op, cpu.pbr, pcBak); getchar(); } while (0)
#define ADDR_A()    do { addr = biMemoryRead16(ctx, cpu.pbr, cpu.pc); cpu.pc += 2; } while (0)

void biRunCycles(BiContext* ctx, size_t cycles)
{
    BiCPU cpu;
    uint16_t pcBak;
    uint16_t addr;
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
        case OP_BRA_R:
            TRAP;
            break;
        case OP_STA_DXI:
            TRAP;
            break;
        case OP_BRL_RL:
            TRAP;
            break;
        case OP_STA_DS:
            TRAP;
            break;
        case OP_STY_D:
            TRAP;
            break;
        case OP_STA_D:
            TRAP;
            break;
        case OP_STX_D:
            TRAP;
            break;
        case OP_STA_DL:
            TRAP;
            break;
        case OP_DEY:
            TRAP;
            break;
        case OP_BIT_IMM:
            TRAP;
            break;
        case OP_TXA:
            TRAP;
            break;
        case OP_PHB_S:
            TRAP;
            break;
        case OP_STY_A:
            TRAP;
            break;
        case OP_STA_A:
            TRAP;
            break;
        case OP_STX_A:
            TRAP;
            break;
        case OP_STA_AL:
            TRAP;
            break;
        case OP_BCC_R:
            TRAP;
            break;
        case OP_STA_DYI:
            TRAP;
            break;
        case OP_STA_DI:
            TRAP;
            break;
        case OP_STA_DYSI:
            TRAP;
            break;
        case OP_STY_DX:
            TRAP;
            break;
        case OP_STA_DX:
            TRAP;
            break;
        case OP_STX_DY:
            TRAP;
            break;
        case OP_STA_DYL:
            TRAP;
            break;
        case OP_TYA:
            TRAP;
            break;
        case OP_STA_AY:
            TRAP;
            break;
        case OP_TXS:
            TRAP;
            break;
        case OP_TXY:
            TRAP;
            break;
        case OP_STZ_A:
            ADDR_A();
            biMemoryWrite16(ctx, cpu.dbr, addr, 0);
            break;
        case OP_STA_AX:
            TRAP;
            break;
        case OP_STZ_AX:
            TRAP;
            break;
        case OP_STA_AXL:
            TRAP;
            break;
        case OP_LDY_MM:
            TRAP;
            break;
        case OP_LDA_DXI:
            TRAP;
            break;
        case OP_LDX_IMM:
            TRAP;
            break;
        case OP_LDA_DS:
            TRAP;
            break;
        case OP_LDY_D:
            TRAP;
            break;
        case OP_LDA_D:
            TRAP;
            break;
        case OP_LDX_D:
            TRAP;
            break;
        case OP_LDA_DL:
            TRAP;
            break;
        case OP_TAY:
            TRAP;
            break;
        case OP_LDA_IMM:
            TRAP;
            break;
        case OP_TAX:
            TRAP;
            break;
        case OP_PLB_S:
            TRAP;
            break;
        case OP_LDY_A:
            TRAP;
            break;
        case OP_LDA_A:
            TRAP;
            break;
        case OP_LDX_A:
            TRAP;
            break;
        case OP_LDA_AL:
            TRAP;
            break;
        case OP_BCS_R:
            TRAP;
            break;
        case OP_LDA_DYI:
            TRAP;
            break;
        case OP_LDA_DI:
            TRAP;
            break;
        case OP_LDA_DYSI:
            TRAP;
            break;
        case OP_LDY_DX:
            TRAP;
            break;
        case OP_LDA_DX:
            TRAP;
            break;
        case OP_LDX_DY:
            TRAP;
            break;
        case OP_LDA_DYL:
            TRAP;
            break;
        case OP_CLV:
            TRAP;
            break;
        case OP_LDA_AY:
            TRAP;
            break;
        case OP_TSX:
            TRAP;
            break;
        case OP_TYX:
            TRAP;
            break;
        case OP_LDY_AX:
            TRAP;
            break;
        case OP_LDA_AX:
            TRAP;
            break;
        case OP_LDX_AY:
            TRAP;
            break;
        case OP_LDA_AXL:
            TRAP;
            break;
        case OP_CPY_IMM:
            TRAP;
            break;
        case OP_CMP_DXI:
            TRAP;
            break;
        case OP_REP_IMM:
            TRAP;
            break;
        case OP_CMP_DS:
            TRAP;
            break;
        case OP_CPY_D:
            TRAP;
            break;
        case OP_CMP_D:
            TRAP;
            break;
        case OP_DEC_D:
            TRAP;
            break;
        case OP_CMP_DL:
            TRAP;
            break;
        case OP_INY:
            TRAP;
            break;
        case OP_CMP_IMM:
            TRAP;
            break;
        case OP_DEX:
            TRAP;
            break;
        case OP_WAI:
            TRAP;
            break;
        case OP_CPY_A:
            TRAP;
            break;
        case OP_CMP_A:
            TRAP;
            break;
        case OP_DEC_A:
            TRAP;
            break;
        case OP_CMP_AL:
            TRAP;
            break;
        case OP_BNE_R:
            TRAP;
            break;
        case OP_CMP_DYI:
            TRAP;
            break;
        case OP_CMP_DI:
            TRAP;
            break;
        case OP_CMP_DYSI:
            TRAP;
            break;
        case OP_PEI_S:
            TRAP;
            break;
        case OP_CMP_DX:
            TRAP;
            break;
        case OP_DEC_DX:
            TRAP;
            break;
        case OP_CMP_DYL:
            TRAP;
            break;
        case OP_CLD:
            TRAP;
            break;
        case OP_CMP_AY:
            TRAP;
            break;
        case OP_PHX_S:
            TRAP;
            break;
        case OP_STP:
            TRAP;
            break;
        case OP_JML_AI:
            TRAP;
            break;
        case OP_CMP_AX:
            TRAP;
            break;
        case OP_DEC_AX:
            TRAP;
            break;
        case OP_CML_AXL:
            TRAP;
            break;
        case OP_CPX_IMM:
            TRAP;
            break;
        case OP_SBC_DXI:
            TRAP;
            break;
        case OP_SEP_IMM:
            TRAP;
            break;
        case OP_SBC_DS:
            TRAP;
            break;
        case OP_CPX_D:
            TRAP;
            break;
        case OP_SBC_D:
            TRAP;
            break;
        case OP_INC_D:
            TRAP;
            break;
        case OP_SBC_DL:
            TRAP;
            break;
        case OP_INX:
            TRAP;
            break;
        case OP_SBC_IMM:
            TRAP;
            break;
        case OP_NOP:
            TRAP;
            break;
        case OP_XBA:
            TRAP;
            break;
        case OP_CPX_A:
            TRAP;
            break;
        case OP_SBC_A:
            TRAP;
            break;
        case OP_INC_A:
            TRAP;
            break;
        case OP_SBC_AL:
            TRAP;
            break;
        case OP_BEQ_R:
            TRAP;
            break;
        case OP_SBC_DYI:
            TRAP;
            break;
        case OP_SBC_DI:
            TRAP;
            break;
        case OP_SBC_DYSI:
            TRAP;
            break;
        case OP_PEA_S:
            TRAP;
            break;
        case OP_SBC_DX:
            TRAP;
            break;
        case OP_INC_DX:
            TRAP;
            break;
        case OP_SBC_DYL:
            TRAP;
            break;
        case OP_SED:
            TRAP;
            break;
        case OP_SBC_AY:
            TRAP;
            break;
        case OP_PLX_S:
            TRAP;
            break;
        case OP_XCE:
            TRAP;
            break;
        case OP_JSR_AXI:
            TRAP;
            break;
        case OP_SBC_AX:
            TRAP;
            break;
        case OP_INC_AX:
            TRAP;
            break;
        case OP_SBC_AXL:
            TRAP;
            break;
        }
    }

    memcpy(&ctx->cpu, &cpu, sizeof(cpu));
}
