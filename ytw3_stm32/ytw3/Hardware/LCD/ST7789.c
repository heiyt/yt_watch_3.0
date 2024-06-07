#include "ST7789.h"

static void ST7789_WriteCommand(uint8_t cmd)
{
	ST7789_DC_Clr();
    HAL_SPI_Transmit_DMA(&hspi1, &cmd, 1);
}

static void ST7789_WriteData(uint16_t data)
{
	ST7789_DC_Set();
    uint8_t temp[] = {data >> 8, data & 0xff};
    HAL_SPI_Transmit_DMA(&hspi1, temp, 2);
}

static void ST7789_WriteSmallData(uint8_t data)
{
    ST7789_DC_Set();
    HAL_SPI_Transmit(&hspi1, &data, 1,HAL_DMA_ERROR_TIMEOUT);
}

static void ST7789_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	x0 = x0 + X_SHIFT;
    x1 = x1 + X_SHIFT;
	/* Column Address set */
	ST7789_WriteCommand(ST7789_CASET);
    ST7789_WriteData(x0);
    ST7789_WriteData(x1);
	/* Row Address set */
	ST7789_WriteCommand(ST7789_RASET);
    ST7789_WriteData(y0);
    ST7789_WriteData(y1);
	/* Write to RAM */
	ST7789_WriteCommand(ST7789_RAMWR);
}

void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, lv_color_t *color)
{
    uint32_t i = 0,total;
    total = 2 * (xEnd - xSta + 1) * (yEnd - ySta + 1);
    uint8_t buff[total];
	ST7789_SetAddressWindow(xSta, ySta, xEnd, yEnd);
    while (i != total) {
        buff[i] = color->full >> 8;
        i++;
        buff[i] = color->full & 0xff;
        i++;
        color++;
    }
    ST7789_DC_Set();
    HAL_SPI_Transmit_DMA(&hspi1, buff, total);
    while (hspi1.hdmatx->State != HAL_DMA_STATE_READY);
}

void ST7789_SetRotation(uint8_t m)
{
    ST7789_WriteCommand(ST7789_MADCTL);	// MADCTL
    switch (m) {
        case 0:
            ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
            break;
        case 1:
            ST7789_WriteSmallData(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
            break;
        case 2:
            ST7789_WriteSmallData(ST7789_MADCTL_RGB);
            break;
        case 3:
            ST7789_WriteSmallData(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
            break;
        default:
            break;
    }
}

void ST7789_Init(void)
{
    HAL_Delay(25);
    ST7789_RST_Clr();
    HAL_Delay(25);
    ST7789_RST_Set();
    HAL_Delay(50);

    ST7789_WriteCommand(ST7789_COLMOD);		//	Set color mode
    ST7789_WriteSmallData(ST7789_COLOR_MODE_16bit);
    ST7789_WriteCommand(0xB2);				//	Porch control
    {
        uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
        ST7789_WriteSmallData(data[0]);
        ST7789_WriteSmallData(data[1]);
        ST7789_WriteSmallData(data[2]);
        ST7789_WriteSmallData(data[3]);
        ST7789_WriteSmallData(data[4]);
    }
    ST7789_SetRotation(ST7789_ROTATION);	//	MADCTL (Display Rotation)

    /* Internal LCD Voltage generator settings */
    ST7789_WriteCommand(0XB7);				//	Gate Control
    ST7789_WriteSmallData(0x35);			//	Default value
    ST7789_WriteCommand(0xBB);				//	VCOM setting
    ST7789_WriteSmallData(0x19);			//	0.725v (default 0.75v for 0x20)
    ST7789_WriteCommand(0xC0);				//	LCMCTRL
    ST7789_WriteSmallData (0x2C);			//	Default value
    ST7789_WriteCommand (0xC2);				//	VDV and VRH command Enable
    ST7789_WriteSmallData (0x01);			//	Default value
    ST7789_WriteCommand (0xC3);				//	VRH set
    ST7789_WriteSmallData (0x12);			//	+-4.45v (defalut +-4.1v for 0x0B)
    ST7789_WriteCommand (0xC4);				//	VDV set
    ST7789_WriteSmallData (0x20);			//	Default value
    ST7789_WriteCommand (0xC6);				//	Frame rate control in normal mode
    ST7789_WriteSmallData (0x0F);			//	Default value (60HZ)
    ST7789_WriteCommand (0xD0);				//	Power control
    ST7789_WriteSmallData (0xA4);			//	Default value
    ST7789_WriteSmallData (0xA1);			//	Default value
    /**************** Division line ****************/

    ST7789_WriteCommand(0xE0);
    {
        uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
        ST7789_WriteSmallData(data[0]);
        ST7789_WriteSmallData(data[1]);
        ST7789_WriteSmallData(data[2]);
        ST7789_WriteSmallData(data[3]);
        ST7789_WriteSmallData(data[4]);
        ST7789_WriteSmallData(data[5]);
        ST7789_WriteSmallData(data[6]);
        ST7789_WriteSmallData(data[7]);
        ST7789_WriteSmallData(data[8]);
        ST7789_WriteSmallData(data[9]);
        ST7789_WriteSmallData(data[10]);
        ST7789_WriteSmallData(data[11]);
        ST7789_WriteSmallData(data[12]);
        ST7789_WriteSmallData(data[13]);
    }

    ST7789_WriteCommand(0xE1);
    {
        uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
        ST7789_WriteSmallData(data[0]);
        ST7789_WriteSmallData(data[1]);
        ST7789_WriteSmallData(data[2]);
        ST7789_WriteSmallData(data[3]);
        ST7789_WriteSmallData(data[4]);
        ST7789_WriteSmallData(data[5]);
        ST7789_WriteSmallData(data[6]);
        ST7789_WriteSmallData(data[7]);
        ST7789_WriteSmallData(data[8]);
        ST7789_WriteSmallData(data[9]);
        ST7789_WriteSmallData(data[10]);
        ST7789_WriteSmallData(data[11]);
        ST7789_WriteSmallData(data[12]);
        ST7789_WriteSmallData(data[13]);
    }
    ST7789_WriteCommand (ST7789_INVON);		//	Inversion ON
    ST7789_WriteCommand (ST7789_SLPOUT);	//	Out of sleep mode
    ST7789_WriteCommand (ST7789_NORON);		//	Normal Display on
    ST7789_WriteCommand (ST7789_DISPON);	//	Main screen turned on

    HAL_Delay(50);
}