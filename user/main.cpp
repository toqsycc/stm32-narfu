#include <stm32f4xx_hal.h>

void ledInit()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef boardLED;
	boardLED.Mode = GPIO_MODE_OUTPUT_PP;
	boardLED.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	HAL_GPIO_Init(GPIOD, &boardLED);
}

void delayMs(volatile int ms)
{
	int j;
	for (j = 0; j < ms * 4000; j++)
	{
		__asm("nop");
	}
}

int main()
{
	ledInit();

	for(;;) 
	{ 
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		delayMs(10);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		delayMs(10);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		delayMs(10);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		delayMs(10);
	}

	return 0;
}
