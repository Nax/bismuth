#ifndef LIBBISMUTH_OP_H
#define LIBBISMUTH_OP_H

#define OP_BRK_S        0x00
#define OP_ORA_DXI      0x01
#define OP_COP_S        0x02
#define OP_ORA_DS       0x03
#define OP_TBS_D        0x04
#define OP_ORA_D        0x05
#define OP_ASL_D        0x06
#define OP_ORA_DL       0x07
#define OP_PHP_S        0x08
#define OP_ORA_IMM      0x09
#define OP_ASL_AC       0x0a
#define OP_PHD_S        0x0b
#define OP_TSB_A        0x0c
#define OP_ORA_A        0x0d
#define OP_ASL_A        0x0e
#define OP_ORA_AL       0x0f
#define OP_BPL_R        0x10
#define OP_ORA_DYI      0x11
#define OP_ORA_DI       0x12
#define OP_ORA_DYSI     0x13
#define OP_TRB_D        0x14
#define OP_ORA_DX       0x15
#define OP_ASL_DX       0x16
#define OP_ORA_DYL      0x17
#define OP_CLC          0x18
#define OP_ORA_AY       0x19
#define OP_INC_AC       0x1a
#define OP_TCS          0x1b
#define OP_TRB_A        0x1c
#define OP_ORA_AX       0x1d
#define OP_ASL_AX       0x1e
#define OP_ORA_AXL      0x1f
#define OP_JSR_A        0x20
#define OP_AND_DXI      0x21
#define OP_JSL_AL       0x22
#define OP_AND_DS       0x23
#define OP_BIT_D        0x24
#define OP_AND_D        0x25
#define OP_ROL_D        0x26
#define OP_AND_DL       0x27
#define OP_PLP_S        0x28
#define OP_AND_IMM      0x29
#define OP_ROL_AC       0x2a
#define OP_PLD_S        0x2b
#define OP_BIT_A        0x2c
#define OP_AND_A        0x2d
#define OP_ROL_A        0x2e
#define OP_AND_AL       0x2f
#define OP_BMI_R        0x30
#define OP_AND_DYI      0x31
#define OP_AND_DI       0x32
#define OP_AND_DYSI     0x33
#define OP_BIT_DX       0x34
#define OP_AND_DX       0x35
#define OP_ROL_DX       0x36
#define OP_AND_DYL      0x37
#define OP_SEC          0x38
#define OP_AND_AY       0x39
#define OP_DEC_AC       0x3a
#define OP_TSC          0x3b
#define OP_BIT_AX       0x3c
#define OP_AND_AX       0x3d
#define OP_ROL_AX       0x3e
#define OP_AND_AXL      0x3f
#define OP_RTI_S        0x40
#define OP_EOR_DXI      0x41
#define OP_WDM          0x42
#define OP_EOR_DS       0x43
#define OP_MVP          0x44
#define OP_EOR_D        0x45
#define OP_LSR_D        0x46
#define OP_EOR_DL       0x47
#define OP_PHA_S        0x48
#define OP_EOR_IMM      0x49
#define OP_LSR_AC       0x4a
#define OP_PHK_S        0x4b
#define OP_JMP_A        0x4c
#define OP_EOR_A        0x4d
#define OP_LSR_A        0x4e
#define OP_EOR_AL       0x4f
#define OP_BVC_R        0x50
#define OP_EOR_DYI      0x51
#define OP_EOR_DI       0x52
#define OP_EOR_DYSI     0x53
#define OP_MVN          0x54
#define OP_EOR_DX       0x55
#define OP_LSR_DX       0x56
#define OP_EOR_DYL      0x57
#define OP_CLI          0x58
#define OP_EOR_AY       0x59
#define OP_PHY_S        0x5a
#define OP_TCD          0x5b
#define OP_JMP_AL       0x5c
#define OP_EOR_AX       0x5d
#define OP_LSR_AX       0x5e
#define OP_EOR_AXL      0x5f
#define OP_RTS_S        0x60
#define OP_ADC_DXI      0x61
#define OP_PER_S        0x62
#define OP_ADC_DS       0x63
#define OP_STZ_D        0x64
#define OP_ADC_D        0x65
#define OP_ROR_D        0x66
#define OP_ADC_DL       0x67
#define OP_PLA_S        0x68
#define OP_ADC_IMM      0x69
#define OP_ROR_AC       0x6a
#define OP_RTL_S        0x6b
#define OP_JMP_AI       0x6c
#define OP_ADC_A        0x6d
#define OP_ROR_A        0x6e
#define OP_ADC_AL       0x6f
#define OP_BVS_R        0x70
#define OP_ADC_DYI      0x71
#define OP_ADC_DI       0x72
#define OP_ADC_DYSI     0x73
#define OP_STZ_DX       0x74
#define OP_ADC_DX       0x75
#define OP_ROR_DX       0x76
#define OP_ADC_DYL      0x77
#define OP_SEI          0x78
#define OP_ADC_AY       0x79
#define OP_PLY_S        0x7a
#define OP_TDC          0x7b
#define OP_JMP_AXI      0x7c
#define OP_ADC_AX       0x7d
#define OP_ROR_AX       0x7e
#define OP_ADC_AXL      0x7f

#endif
