/******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
******************************************************************************/
//			Made by: Kubas Michal
/*============================================================================*\
* Headers files, namespace
\*============================================================================*/
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_sdram.h"
#include "stm32f7xx_hal_ltdc.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32f7xx_ll_fmc.h"
#include "stdio.h"
#include "stdlib.h"
#include "back.h"
#include "open.h"
#include "closed.h"
#include "lock_open.h"
#include "lock_closed.h"

/*============================================================================*\
* Private variables
\*============================================================================*/
CRC_HandleTypeDef hcrc;
DMA2D_HandleTypeDef hdma2d;
LTDC_HandleTypeDef hltdc;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart1;
SDRAM_HandleTypeDef hsdram1;

uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t sum;
uint8_t check=0;
uint8_t back1, back2;

bool lock = 0;
int led = 0;
uint8_t count1=0, count2=0, count3=0;
uint16_t x[4],y[4],last_y[4];

/*============================================================================*\
* Functions prototypes
\*============================================================================*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_TIM3_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

TS_StateTypeDef TS_State;
GPIO_InitTypeDef GPIO_InitStruct;

void led1(float duty){
    TIM1->CCR1=(int)(duty*65535.0);
}
void led2(float duty){
    TIM2->CCR1=(int)(duty*65535.0);
}

void set_sensor_input(void)
{
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

void set_sensor_output(void)
{
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

extern TIM_HandleTypeDef htim3;

void delay_us (uint32_t delay)
{
	__HAL_TIM_SET_COUNTER (&htim3, 0);
	while (__HAL_TIM_GET_COUNTER(&htim3) < delay);
}


void sensor_start (void)
{
set_sensor_output (); // set the pin as output
HAL_GPIO_WritePin (GPIOI, GPIO_PIN_2, 0); // pull the pin low
delay_us (18000); // wait for 18ms
set_sensor_input (); // set as input
}

void check_response (void)
{
 delay_us (40);
 if (!(HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2))) // if the pin is low
 {
  delay_us (80); // wait for 80us
  if ((HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2)))
    check = 1; // now if the pin is high response = ok i.e. check =1
 }
 while ((HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2))); // wait for the pin to go low
}

uint8_t read_data (void)
{
 uint8_t i,j;
 for (j=0;j<8;j++)
 {
  while (!(HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2))); // wait for the pin to go high
  delay_us(40); // wait for 40 us
  if ((HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2)) == 0) // if the pin is low
  {
    i&= ~(1<<(7-j)); // write 0
   }
  else i|= (1<<(7-j)); // if the pin is high, write 1
  while ((HAL_GPIO_ReadPin (GPIOI, GPIO_PIN_2))); // wait for the pin to go low
 }
 return i;
}

/*============================================================================*\
* Main function
\*============================================================================*/
int main(void)
{

  /* Enable I-Cache-------------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache-------------------------------------------------------------*/
  SCB_EnableDCache();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  MX_GPIO_Init();
  MX_CRC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_TIM3_Init();


  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  BSP_LCD_Init();


  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
  BSP_LCD_DisplayOn();

  BSP_LCD_SelectLayer(0);
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SelectLayer(1);
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

  if( BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize())!=TS_OK)
  {
    Error_Handler();
  }

  x[0]=150;
  x[1]=233;
  x[2]=100;
  x[3]=300;
  y[0]=212;
  y[1]=30;
  y[2]=118;
  y[3]=118;

  void DisplayButton1(uint16_t X, uint16_t Y, uint16_t R, uint32_t colour)
  {
	BSP_LCD_SetTextColor(colour);
	BSP_LCD_FillCircle(X,Y,R);
  }

  void welcome()
  {
	  BSP_LCD_SelectLayer(0);
	  BSP_LCD_Clear(LCD_COLOR_DARKGRAY );
	  BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
	  BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
	  BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *)"Witamy w naszym systemie", CENTER_MODE);
	  BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t *)"sterujesz: SYPIALNIA", CENTER_MODE);

  }

  void DrawHome()
  {
	BSP_LCD_SelectLayer(0);
	BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_DrawRect(55,60,180,70);
    BSP_LCD_DrawRect(55,180,180,70);
    BSP_LCD_DisplayStringAt(65,70,(uint8_t *)"Sterowanie", LEFT_MODE);
    BSP_LCD_DisplayStringAt(65,90,(uint8_t *)"swiatlami", LEFT_MODE);
    BSP_LCD_DisplayStringAt(65,190,(uint8_t *)"Sterowanie", LEFT_MODE);
    BSP_LCD_DisplayStringAt(65,210,(uint8_t *)"zaluzjami", LEFT_MODE);
  }

  void DrawBlinds()
  {
	BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
    BSP_LCD_DrawRect(15,15,50,30);
    BSP_LCD_DisplayStringAt(40,228,(uint8_t *)"Zamykanie", LEFT_MODE);
    BSP_LCD_DisplayStringAt(40,248,(uint8_t *)"  okna", LEFT_MODE);


	if (lock==1)
	{
		BSP_LCD_DrawBitmap(80,150, (uint8_t *)&lock_open);
		BSP_LCD_DrawBitmap(233,40, (uint8_t *)&open);
	}
	else if(lock==0)
	{
		BSP_LCD_DrawBitmap(80,150, (uint8_t *)&lock_closed);
		BSP_LCD_DrawBitmap(233,40, (uint8_t *)&closed);
	}

    BSP_LCD_DrawBitmap(15,15, (uint8_t *)&back);
    BSP_LCD_FillRect(x[1],30,217,y[1]-30);

   }

  void DrawLed()
  {
	BSP_LCD_SelectLayer(0);
  	BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
  	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
  	BSP_LCD_FillRect(x[0],y[0],10,20);
  	BSP_LCD_DrawRect(150,212,190,20);
    BSP_LCD_DrawCircle(100,126,45);
    BSP_LCD_DrawCircle(300,126,45);
    BSP_LCD_DrawRect(15,15,50,30);
    BSP_LCD_DrawBitmap(15,15, (uint8_t *)&back);

	if(led==1)
	{
		DisplayButton1(100,126,45,0xFFFF0000);
	}
	else if (led==2)
	{
		DisplayButton1(300,126,45,0xFF00FF00);
	}

    BSP_LCD_DisplayStringAt(72,118,(uint8_t *)"LED1", LEFT_MODE);
    BSP_LCD_DisplayStringAt(272,118,(uint8_t *)"LED2", LEFT_MODE);
  }


  void sensor()
  {
	  sensor_start();
	  check_response();
	  Rh_byte1= read_data();
	  Rh_byte2= read_data();
	  Temp_byte1= read_data();
	  Temp_byte2= read_data();
	  sum = read_data();

	  if(sum==(Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2))
	  {
		  BSP_LCD_SelectLayer(1);
		  BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGRAY);
		  BSP_LCD_SetBackColor(LCD_COLOR_DARKGRAY);
		  BSP_LCD_SetFont(&Font12);
		  BSP_LCD_DisplayStringAt(315, 75, (uint8_t *)"Temperatura:", LEFT_MODE);
		  BSP_LCD_DisplayChar(330, 90, (Temp_byte1/10)+48);
		  BSP_LCD_DisplayChar(340, 90, (Temp_byte1%10)+48);
		  BSP_LCD_DisplayStringAt(350, 90, (uint8_t *)"*C", LEFT_MODE);
		  BSP_LCD_DisplayStringAt(315, 150, (uint8_t *)"Wilgotnosc:", LEFT_MODE);
		  BSP_LCD_DisplayChar(330, 165, (Rh_byte1/10)+48);
		  BSP_LCD_DisplayChar(340, 165, (Rh_byte1%10)+48);
		  BSP_LCD_DisplayStringAt(350, 165, (uint8_t *)"%", LEFT_MODE);
		  HAL_Delay(500);
	  }
   }

   welcome();

/*============================================================================*\
* while loop
\*============================================================================*/
while (1)
{

	BSP_TS_GetState(&TS_State);

	if (TS_State.touchDetected)
	{

		DrawHome();
		sensor();
		back1=1;
		back2=1;

      		if(TS_State.touchX[0]>55&&TS_State.touchX[0]<235&&TS_State.touchY[0]>60&&TS_State.touchY[0]<130)
      		{
      			DrawLed();

      			while(back1==1)
      			{
      				BSP_TS_GetState(&TS_State);
      				count2++;
      					if(count2>30)
      					{
      						if (TS_State.touchDetected)
      						{
      							if(led==1)led1(((float)(x[0]-150)/190.0));

      							else if(led==2)led2(((float)(x[0]-150)/190.0));

      							if( TS_State.touchX[0]>x[0]-20&&TS_State.touchX[0]<x[0]+20&&TS_State.touchY[0]>y[0]-20&&TS_State.touchY[0]<y[0]+20)
      							{
      								x[0]=TS_State.touchX[0];

      								if(x[0]<=150) x[0]=150;

      								else if(x[0]>=340) x[0]=340;
      							}

      							else if(TS_State.touchX[0]>40-25&&TS_State.touchX[0]<40+25&&TS_State.touchY[0]>40-15&&TS_State.touchY[0]<30+15)
      							{
      								back1=0;
      							}

      							else if(TS_State.touchX[0]>x[2]-40&&TS_State.touchX[0]<x[2]+40&&TS_State.touchY[0]>y[2]-40&&TS_State.touchY[0]<y[2]+40)
      							{
      								if(led==1) led= 0;

      								else
      								{
      									led = 1;
      									led1(((float)(x[0]-150)/190.0));
      								}
      							}

      							else if(TS_State.touchX[0]>x[3]-40&&TS_State.touchX[0]<x[3]+40&&TS_State.touchY[0]>y[3]-40&&TS_State.touchY[0]<y[3]+40)
      							{
      								if(led==2) led=0;

      								else
      								{
      									led=2;
      									led2(((float)(x[0]-150)/190.0));
      								}
      							}

      							DrawLed();
      						}
      						count2=0;
      					}

      				}
      			}

        	if(TS_State.touchX[0]>55&&TS_State.touchX[0]<235&&TS_State.touchY[0]>180&&TS_State.touchY[0]<250)
        	{
        		DrawBlinds();

        		while(back2==1)
        		{
        			BSP_TS_GetState(&TS_State);
      				count3++;
      				if(count3>30)
      				{
						if (TS_State.touchDetected)
						{
							int pre_y = y[1];

							if( TS_State.touchX[0]>233&&TS_State.touchX[0]<450&&TS_State.touchY[0]>40-20&&TS_State.touchY[0]<230+20)
							{
								if(TS_State.touchY[0]-y[1]>1)
								{
									y[1]=TS_State.touchY[0];
									last_y[1]=y[1];
									DrawBlinds();
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_SET);
									HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_RESET);
									HAL_Delay(abs(pre_y-y[1])*50);
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_RESET);
								}

								else if(TS_State.touchY[0]-y[1]<-1)
								{
									y[1]=TS_State.touchY[0];
									last_y[1]=y[1];
									DrawBlinds();
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_RESET);
									HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_SET);
									HAL_Delay(abs(pre_y-y[1])*50);
									HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_RESET);
								}

								else if (TS_State.touchY[0]-y[1]>=-1||TS_State.touchY[0]-y[1]<=1)
								{
									y[1]=last_y[1];
								}

								if(y[1]<=40)
								{
									y[1]=40;
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_RESET);
									HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_RESET);
								}

								else if(y[1]>220)
								{
									y[1]=220;
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3,GPIO_PIN_RESET);
									HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6,GPIO_PIN_RESET);
								}
							}

							else if(TS_State.touchX[0]>40-25&&TS_State.touchX[0]<40+25&&TS_State.touchY[0]>40-15&&TS_State.touchY[0]<30+15)
							{
								back2=0;
							}

							else if(TS_State.touchX[0]>110-30&&TS_State.touchX[0]<110+30&&TS_State.touchY[0]>180-30&&TS_State.touchY[0]<180+30)
							{
								if (lock==1)
								{
									lock=0;
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0,GPIO_PIN_RESET);

								}
								else if(lock==0)
								{
									lock=1;
									HAL_GPIO_WritePin(GPIOI, GPIO_PIN_0,GPIO_PIN_SET);
								}

							}
							DrawBlinds();
						}
        			count3 = 0;
      				}

        		}
        	}
        	DrawHome();
        	sensor();
	}
}

}


/*============================================================================*\
System clock config funtion
  * @brief System Clock Configuration
  * @retval None
\*============================================================================*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /* Configure the main internal regulator output voltage */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Initializes the CPU, AHB and APB */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 100;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* CRC init function */
static void MX_CRC_Init(void)
{

  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* DMA2D init function */
static void MX_DMA2D_Init(void)
{

  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* LTDC init function */
static void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg;

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 40;
  hltdc.Init.VerticalSync = 9;
  hltdc.Init.AccumulatedHBP = 53;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveW = 533;
  hltdc.Init.AccumulatedActiveH = 283;
  hltdc.Init.TotalWidth = 565;
  hltdc.Init.TotalHeigh = 285;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* Timer1 initialization */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}

/* Timier 2 initialization */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim2);

}

/* Timer 3 initialization */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 108-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xffff-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART 1 Initialization */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* FMC initialization  */
static void MX_FMC_Init(void)
{
  FMC_SDRAM_TimingTypeDef SdramTiming;

  /* Perform the SDRAM1 memory initialization sequence */
  hsdram1.Instance = FMC_SDRAM_DEVICE;

  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;

  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 3;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* Configure pins as Analog and Input/Output */
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3|GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);

  /* Configure GPIO: PI3 LCD_DISP_Pin PI0 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|LCD_DISP_Pin|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /* Configure GPIO: PI2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /* Configure GPIO: LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /* Configure GPIO: LCD_INT_Pin */
  GPIO_InitStruct.Pin = LCD_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_INT_GPIO_Port, &GPIO_InitStruct);

  /* Configure GPIO: PH6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
}

void _Error_Handler(char *file, int line)
{
  while(1)
  {}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{}

#endif /* USE_FULL_ASSERT */

/*======================END PROGRAM===================================*/
