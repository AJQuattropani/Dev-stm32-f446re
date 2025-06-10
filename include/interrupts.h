#pragma once

#include "hardware.h"

/*
 SP is first word in interrupt vector (copied to R13)
 15 words for system exception handles and 98 for interrupt handlers
 1 word for stack pointer
 "Section 9 Interrupts and events" in reference manual
*/
#define ISR_VECTOR_SIZE_W 114

void reset_handler(void);
void default_handler(void);

/* system exception interrupts */
void reset_handler_0x004(void) __attribute__((weak, alias("reset_handler")));
void nmi_handler_0x008(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler_0x00C(void)
    __attribute__((weak, alias("default_handler")));
void memmanage_fault_handler_0x010(void)
    __attribute__((weak, alias("default_handler")));
void bus_fault_handler_0x014(void)
    __attribute__((weak, alias("default_handler")));
void usage_fault_handler_0x018(void)
    __attribute__((weak, alias("default_handler")));

void svcall_handler_0x02C(void) __attribute__((weak, alias("default_handler")));
void debug_handler_0x030(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler_0x038(void) __attribute__((weak, alias("default_handler")));
void systick_handler_0x03C(void) __attribute__((weak, alias("default_handler")));

/* STM interrupts */
void wwdg_handler_0x040(void) __attribute__((weak, alias("default_handler")));
void pvd_handler_0x044(void) __attribute__((weak, alias("default_handler")));
void tampstamp_handler_0x048(void)
    __attribute__((weak, alias("default_handler")));
void rtc_wakeup_handler_0x04C(void)
    __attribute__((weak, alias("default_handler")));
void flash_handler_0x050(void) __attribute__((weak, alias("default_handler")));
void rcc_handler_0x054(void) __attribute__((weak, alias("default_handler")));
void exint_l0_handler_0x058(void)
    __attribute__((weak, alias("default_handler")));
void exint_l1_handler_0x05C(void)
    __attribute__((weak, alias("default_handler")));
void exint_l2_handler_0x060(void)
    __attribute__((weak, alias("default_handler")));
void exint_l3_handler_0x064(void)
    __attribute__((weak, alias("default_handler")));
void exint_l4_handler_0x068(void)
    __attribute__((weak, alias("default_handler")));
void dma_s0_handler_0x06C(void) __attribute__((weak, alias("default_handler")));
void dma_s1_handler_0x070(void) __attribute__((weak, alias("default_handler")));
void dma_s2_handler_0x074(void) __attribute__((weak, alias("default_handler")));
void dma_s3_handler_0x078(void) __attribute__((weak, alias("default_handler")));
void dma_s4_handler_0x07C(void) __attribute__((weak, alias("default_handler")));
void dma_s5_handler_0x080(void) __attribute__((weak, alias("default_handler")));
void dma_s6_handler_0x084(void) __attribute__((weak, alias("default_handler")));
void adc_int_handler_0x088(void) __attribute__((weak, alias("default_handler")));
void can1_tx_handler_0x08C(void) __attribute__((weak, alias("default_handler")));
void can1_rx0_handler_0x090(void)
    __attribute__((weak, alias("default_handler")));
void can1_rx1_handler_0x094(void)
    __attribute__((weak, alias("default_handler")));
void can1_sce_handler_0x098(void)
    __attribute__((weak, alias("default_handler")));
void exti9_5_handler_0x09C(void)
    __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_hdlr_0x0A0(void)
    __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_hdlr_0x0A4(void)
    __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_hdlr_0x0A8(void)
    __attribute__((weak, alias("default_handler")));
void tim1_cc_hdlr_0x0AC(void)
    __attribute__((weak, alias("default_handler")));
void tim2_hdlr_0x0B0(void)
    __attribute__((weak, alias("default_handler")));
void tim3_hdlr_0x0B4(void)
    __attribute__((weak, alias("default_handler")));
void tim4_hdlr_0x0B8(void)
    __attribute__((weak, alias("default_handler")));
void i2c1_ev_hdlr_0x0BC(void)
    __attribute__((weak, alias("default_handler")));
void i2c1_er_hdlr_0x0C0(void)
    __attribute__((weak, alias("default_handler")));
void i2c2_ev_hdlr_0x0C4(void)
    __attribute__((weak, alias("default_handler")));
void i2c2_er_hdlr_0x0C8(void)
    __attribute__((weak, alias("default_handler")));
void spi1_handler_0x0CC(void)
    __attribute__((weak, alias("default_handler")));
void spi2_handler_0x0D0(void)
    __attribute__((weak, alias("default_handler")));
void usart1_handler_0x0D4(void)
    __attribute__((weak, alias("default_handler")));
void usart2_handler_0x0D8(void)
    __attribute__((weak, alias("default_handler")));
void usart3_handler_0x0DC(void)
    __attribute__((weak, alias("default_handler")));
void extint_l15_l10_hdlr_0x0E0(void)
    __attribute__((weak, alias("default_handler")));
void rtc_alarm_ab_ext_hdlr_0x0E4(void)
    __attribute__((weak, alias("default_handler")));
void otg_fs_wkup_handler_0x0E8(void)
    __attribute__((weak, alias("default_handler")));
void tim8_brk_tim12_hdlr_0x0EC(void)
    __attribute__((weak, alias("default_handler")));
void tim8_up_tim13_hdlr_0x0F0(void)
    __attribute__((weak, alias("default_handler")));
void tim8_trg_com_tim14_hdlr_0x0F4(void)
    __attribute__((weak, alias("default_handler")));
void tim8_cc_hdlr_0x0F8(void)
    __attribute__((weak, alias("default_handler")));
void dma1_s7_handler_0x0FC(void)
    __attribute__((weak, alias("default_handler")));
void fmcint_handler_0x100(void)
    __attribute__((weak, alias("default_handler")));
void sdioint_handler_0x104(void)
    __attribute__((weak, alias("default_handler")));
void tim5int_handler_0x108(void)
    __attribute__((weak, alias("default_handler")));
void spi3int_handler_0x10C(void)
    __attribute__((weak, alias("default_handler")));
void uart4int_handler_0x110(void)
    __attribute__((weak, alias("default_handler")));
void uart5int_handler_0x114(void)
    __attribute__((weak, alias("default_handler")));
void tim6_dac_hdlr_0x118(void)
    __attribute__((weak, alias("default_handler")));
void tim7int_handler_0x11C(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s0_handler_0x120(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s1_handler_0x124(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s2_handler_0x128(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s3_handler_0x12C(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s4_handler_0x130(void)
    __attribute__((weak, alias("default_handler")));

void can2_tx_handler_0x13C(void)
    __attribute__((weak, alias("default_handler")));
void can2_rx0_handler_0x140(void)
    __attribute__((weak, alias("default_handler")));
void can2_rx1_handler_0x144(void)
    __attribute__((weak, alias("default_handler")));
void can2_sce_handler_0x148(void)
    __attribute__((weak, alias("default_handler")));
void otg_fs_handler_0x14C(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s5_handler_0x150(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s6_handler_0x154(void)
    __attribute__((weak, alias("default_handler")));
void dma2_s7_handler_0x158(void)
    __attribute__((weak, alias("default_handler")));
void usart6int_handler_0x15C(void)
    __attribute__((weak, alias("default_handler")));
void i2c3_ev_int_hdlr_0x160(void)
    __attribute__((weak, alias("default_handler")));
void i2c3_er_int_hdlr_0x164(void)
    __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_out_hdlr_0x168(void)
    __attribute__((weak, alias("default_handler")));
void otg_hs_ep1_in_hdlr_0x16C(void)
    __attribute__((weak, alias("default_handler")));
void otg_hs_wkup_hdlr_0x170(void)
    __attribute__((weak, alias("default_handler")));
void otg_hs_hdlr_0x174(void)
    __attribute__((weak, alias("default_handler")));
void cdmi_handler_0x178(void)
    __attribute__((weak, alias("default_handler")));
void fpuint_handler_0x184(void)
    __attribute__((weak, alias("default_handler")));
void spi4int_handler_0x190(void)
    __attribute__((weak, alias("default_handler")));
void sai1int_handler_0x19C(void)  
    __attribute__((weak, alias("default_handler")));
void sai2int_handler_0x1AC(void)
    __attribute__((weak, alias("default_handler")));
void quadspiint_handler_0x1B0(void)
    __attribute__((weak, alias("default_handler")));
void hdmi_cec_handler_0x1B4(void)
    __attribute__((weak, alias("default_handler")));
void spdif_rx_handler_0x1B8(void)
    __attribute__((weak, alias("default_handler")));
void fmpi2c1_ev_handler_0x1BC(void)
    __attribute__((weak, alias("default_handler")));
void fmpi2c1_err_handler_0x1C0(void)
    __attribute__((weak, alias("default_handler")));
void lptim1_exti32_handler(void)
    __attribute__((weak, alias("default_handler")));

uint32_t isr_vector[ISR_VECTOR_SIZE_W]
    __attribute__((section(".isr_vector"))) = {
        STACK_POINTER_INIT_ADDRESS, // 0x000
        (uint32_t)&reset_handler_0x004,
        (uint32_t)&nmi_handler_0x008,
        (uint32_t)&hard_fault_handler_0x00C,
        (uint32_t)&memmanage_fault_handler_0x010,
        (uint32_t)&bus_fault_handler_0x014,
        (uint32_t)&usage_fault_handler_0x018,
        0, // 0x01C
        0, // 0x020
        0, // 0x024
        0, // 0x028
        (uint32_t)&svcall_handler_0x02C,
        (uint32_t)&debug_handler_0x030,
        0, // 0x034
        (uint32_t)&pendsv_handler_0x038,
        (uint32_t)&systick_handler_0x03C,
        (uint32_t)&wwdg_handler_0x040,
        (uint32_t)&pvd_handler_0x044,
        (uint32_t)&tampstamp_handler_0x048,
        (uint32_t)&rtc_wakeup_handler_0x04C,
        (uint32_t)&flash_handler_0x050,
        (uint32_t)&rcc_handler_0x054,
        (uint32_t)&exint_l0_handler_0x058,
        (uint32_t)&exint_l1_handler_0x05C,
        (uint32_t)&exint_l2_handler_0x060,
        (uint32_t)&exint_l3_handler_0x064,
        (uint32_t)&exint_l4_handler_0x068,
        (uint32_t)&dma_s0_handler_0x06C,
        (uint32_t)&dma_s1_handler_0x070,
        (uint32_t)&dma_s2_handler_0x074,
        (uint32_t)&dma_s3_handler_0x078,
        (uint32_t)&dma_s4_handler_0x07C,
        (uint32_t)&dma_s5_handler_0x080,
        (uint32_t)&dma_s6_handler_0x084,
        (uint32_t)&adc_int_handler_0x088,
        (uint32_t)&can1_tx_handler_0x08C,
        (uint32_t)&can1_rx0_handler_0x090,
        (uint32_t)&can1_rx1_handler_0x094,
        (uint32_t)&can1_sce_handler_0x098,
        (uint32_t)&exti9_5_handler_0x09C,
        (uint32_t)tim1_brk_tim9_hdlr_0x0A0,
        (uint32_t)tim1_up_tim10_hdlr_0x0A4,
        (uint32_t)tim1_trg_com_tim11_hdlr_0x0A8,
        (uint32_t)tim1_cc_hdlr_0x0AC,
        (uint32_t)tim2_hdlr_0x0B0,
        (uint32_t)tim3_hdlr_0x0B4,
        (uint32_t)tim4_hdlr_0x0B8,
        (uint32_t)i2c1_ev_hdlr_0x0BC,
        (uint32_t)i2c1_er_hdlr_0x0C0,
        (uint32_t)i2c2_ev_hdlr_0x0C4,
        (uint32_t)i2c2_er_hdlr_0x0C8,
        (uint32_t)spi1_handler_0x0CC,
        (uint32_t)spi2_handler_0x0D0,
        (uint32_t)usart1_handler_0x0D4,
        (uint32_t)usart2_handler_0x0D8,
        (uint32_t)usart3_handler_0x0DC,
        (uint32_t)extint_l15_l10_hdlr_0x0E0,
        (uint32_t)&rtc_alarm_ab_ext_hdlr_0x0E4,
        (uint32_t)&otg_fs_wkup_handler_0x0E8,
        (uint32_t)&tim8_brk_tim12_hdlr_0x0EC,
        (uint32_t)&tim8_up_tim13_hdlr_0x0F0,
        (uint32_t)&tim8_trg_com_tim14_hdlr_0x0F4,
        (uint32_t)&tim8_cc_hdlr_0x0F8,
        (uint32_t)&dma1_s7_handler_0x0FC,
        (uint32_t)&fmcint_handler_0x100,
        (uint32_t)&sdioint_handler_0x104,
        (uint32_t)&tim5int_handler_0x108,
        (uint32_t)&spi3int_handler_0x10C,
        (uint32_t)&uart4int_handler_0x110,
        (uint32_t)&uart5int_handler_0x114,
        (uint32_t)&tim6_dac_hdlr_0x118,
        (uint32_t)&tim7int_handler_0x11C,
        (uint32_t)&dma2_s0_handler_0x120,
        (uint32_t)&dma2_s1_handler_0x124,
        (uint32_t)&dma2_s2_handler_0x128,
        (uint32_t)&dma2_s3_handler_0x12C,
        (uint32_t)&dma2_s4_handler_0x130,
        0, // 0x134
        0, // 0x138
        (uint32_t)&can2_tx_handler_0x13C,
        (uint32_t)&can2_rx0_handler_0x140,
        (uint32_t)&can2_rx1_handler_0x144,
        (uint32_t)&can2_sce_handler_0x148,
        (uint32_t)&otg_fs_handler_0x14C,
        (uint32_t)&dma2_s5_handler_0x150,
        (uint32_t)&dma2_s6_handler_0x154,
        (uint32_t)&dma2_s7_handler_0x158,
        (uint32_t)&usart6int_handler_0x15C,
        (uint32_t)&i2c3_ev_int_hdlr_0x160,
        (uint32_t)&i2c3_er_int_hdlr_0x164,
        (uint32_t)&otg_hs_ep1_out_hdlr_0x168,
        (uint32_t)&otg_hs_ep1_in_hdlr_0x16C,
        (uint32_t)&otg_hs_wkup_hdlr_0x170,
        (uint32_t)&otg_hs_hdlr_0x174,
        (uint32_t)&cdmi_handler_0x178,
        0, // 0x17C
        0, // 0x180
        (uint32_t)&fpuint_handler_0x184,
        0, // 0x188
        0, // 0x18C
        (uint32_t)&spi4int_handler_0x190,
        0, // 0x194
        0, // 0x198
        (uint32_t)&sai1int_handler_0x19C,  
        0, // 0x1A0
        0, // 0x1A4
        0, // 0x1A8
        (uint32_t)&sai2int_handler_0x1AC,
        (uint32_t)&quadspiint_handler_0x1B0,
        (uint32_t)&hdmi_cec_handler_0x1B4,
        (uint32_t)&spdif_rx_handler_0x1B8,
        (uint32_t)&fmpi2c1_ev_handler_0x1BC,
        (uint32_t)&fmpi2c1_err_handler_0x1C0,
        (uint32_t)&lptim1_exti32_handler
  // TODO one of the interrupts is missing. figure out which.
};


