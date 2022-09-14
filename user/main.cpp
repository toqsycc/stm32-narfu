#include <stm32f4xx_hal.h>

void ledInit()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef boardLED;
	boardLED.Mode = GPIO_MODE_OUTPUT_PP;
	boardLED.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	HAL_GPIO_Init(GPIOD, &boardLED);
}

void btnInit()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef btn;
	btn.Mode = GPIO_MODE_INPUT;
	btn.Pull = GPIO_PULLDOWN;
	btn.Pin = GPIO_PIN_0;

	HAL_GPIO_Init(GPIOA, &btn);
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
	uint32_t count = 0;
	uint8_t isReadyToRead = 0xFF;
	//uint8_t status[4] = { 0 };
	btnInit();
	ledInit();

	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

	for(;;) 
	{ 
		/*
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && !(count % 2))
		{
			count++;
			for (uint8_t i = 0; i < 4; i++)
			{
				if (!status[i])
				{
					status[i] = !status[i];
					HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 + i);
				}
				else continue;
			}
			delayMs(40);
		}

		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && count % 2)
		{
			count++;
			for (uint8_t i = 0; i < 4; i++)
			{
				if (status[i])
				{
					status[i] = !status[i];
					HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 + i);
				}
				else continue;
			}
			delayMs(40);
		}*/

		if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) isReadyToRead = 0xFF;

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && !(count % 4) && isReadyToRead)
		{
			isReadyToRead = 0x00;
			count++;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			delayMs(40);
		}

		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && !((count % 4) - 1) && isReadyToRead)
		{
			isReadyToRead = 0x00;
			count++;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
			delayMs(40);
		}

		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && !((count % 4) - 2) && isReadyToRead)
		{
			isReadyToRead = 0x00;
			count++;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
			delayMs(40);
		}

		else if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) && !((count % 4) - 3) && isReadyToRead)
		{
			isReadyToRead = 0x00;
			count++;
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			delayMs(40);
		}
	}

	return 0;
}
