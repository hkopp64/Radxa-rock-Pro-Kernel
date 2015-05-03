#ifndef LCD_TJ048NC01CA_H_
#define LCD_TJ048NC01CA_H_
#include <mach/gpio.h>
#include <mach/iomux.h>
#include <linux/delay.h>

/* Base */
#define SCREEN_TYPE		SCREEN_RGB
#define LVDS_FORMAT		LVDS_8BIT_1
#define OUT_FACE		OUT_P888
#define DCLK			23000000
#define LCDC_ACLK       	150000000     //29 lcdc axi DMA Ƶ��

/* Timing */
#define H_PW			1
#define H_BP			120
#define H_VD			800
#define H_FP			20

#define V_PW			1
#define V_BP			20
#define V_VD			480
#define V_FP			4

#define LCD_WIDTH       800    //need modify
#define LCD_HEIGHT      480

/* Other */
#define DCLK_POL		1
#define DEN_POL			0
#define VSYNC_POL		0
#define HSYNC_POL		0

#define SWAP_RB			0
#define SWAP_RG			0
#define SWAP_GB			0


#define TXD_PORT        gLcd_info->txd_pin
#define CLK_PORT        gLcd_info->clk_pin
#define CS_PORT         gLcd_info->cs_pin

#define CS_OUT()        gpio_direction_output(CS_PORT, 0)
#define CS_SET()        gpio_set_value(CS_PORT, GPIO_HIGH)
#define CS_CLR()        gpio_set_value(CS_PORT, GPIO_LOW)
#define CLK_OUT()       gpio_direction_output(CLK_PORT, 0)
#define CLK_SET()       gpio_set_value(CLK_PORT, GPIO_HIGH)
#define CLK_CLR()       gpio_set_value(CLK_PORT, GPIO_LOW)
#define TXD_OUT()       gpio_direction_output(TXD_PORT, 0)
#define TXD_SET()       gpio_set_value(TXD_PORT, GPIO_HIGH)
#define TXD_CLR()       gpio_set_value(TXD_PORT, GPIO_LOW)

#define DRVDelayUs(i)   udelay(i*2)

static struct rk29lcd_info *gLcd_info = NULL;
#define RK_SCREEN_INIT
int rk_lcd_init(void);
int rk_lcd_standby(u8 enable);

void spi_screenreg_set(u32 Addr, u32 Data)
{
    u32 i;

    TXD_OUT();
    CLK_OUT();
    CS_OUT();
    DRVDelayUs(2);
    DRVDelayUs(2);

    CS_SET();
    TXD_CLR();
    CLK_CLR();
    DRVDelayUs(2);

	CS_CLR();
	for(i = 0; i < 7; i++)  //reg
	{
		if(Addr &(1<<(6-i)))
			TXD_SET();
		else
			TXD_CLR();

		// \u6a21\u62dfCLK
		CLK_CLR();
		DRVDelayUs(2);
		CLK_SET();
		DRVDelayUs(2);
	}

	TXD_CLR();  //write

	// \u6a21\u62dfCLK
    CLK_CLR();
    DRVDelayUs(2);
    CLK_SET();
    DRVDelayUs(2);

	for(i = 0; i < 8; i++)  //data
	{
		if(Data &(1<<(7-i)))
			TXD_SET();
		else
			TXD_CLR();

		// \u6a21\u62dfCLK
        CLK_CLR();
		DRVDelayUs(2);
		CLK_SET();
		DRVDelayUs(2);
	}

	CS_SET();
	CLK_CLR();
	TXD_CLR();
	DRVDelayUs(2);

}


int rk_lcd_init(void)
{
    if(gLcd_info)
        gLcd_info->io_init();
	//R(0xess (A5~A0) Data(D7~D0)
#if 0
    spi_screenreg_set(0x03, 0x86);
    spi_screenreg_set(0x05, 0x33);
    spi_screenreg_set(0x09, 0xFF);
    spi_screenreg_set(0x3A, 0x95);
    spi_screenreg_set(0x3C, 0xE0);
    spi_screenreg_set(0x3D, 0xF4);
    spi_screenreg_set(0x3E, 0x21);
    spi_screenreg_set(0x3F, 0x87);
    spi_screenreg_set(0x15, 0x55);
    spi_screenreg_set(0x16, 0xAF);
    spi_screenreg_set(0x17, 0xFC);
    spi_screenreg_set(0x18, 0x00);
    spi_screenreg_set(0x19, 0x4B);
    spi_screenreg_set(0x1A, 0x80);
    spi_screenreg_set(0x1B, 0xFF);
    spi_screenreg_set(0x1C, 0x39);
    spi_screenreg_set(0x1D, 0x69);
    spi_screenreg_set(0x1E, 0x9F);
    spi_screenreg_set(0x1F, 0x09);
    spi_screenreg_set(0x20, 0x8F);
    spi_screenreg_set(0x21, 0xF0);
    spi_screenreg_set(0x22, 0x2B);
    spi_screenreg_set(0x23, 0x58);
    spi_screenreg_set(0x24, 0x7C);
    spi_screenreg_set(0x25, 0xA5);
    spi_screenreg_set(0x26, 0xFF);
#endif

    if(gLcd_info)
        gLcd_info->io_deinit();
    return 0;
}

int rk_lcd_standby(u8 enable)
{
    if(gLcd_info)
        gLcd_info->io_init();
	if(enable) {
		spi_screenreg_set(0x43, 0x20);
	} else {
		spi_screenreg_set(0x43, 0xE0);
	}
    if(gLcd_info)
        gLcd_info->io_deinit();
    return 0;
}
#endif

