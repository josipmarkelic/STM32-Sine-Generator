#include "main.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "error_handler.h"
#include "peripheral_init.h"
#include "sinus.h"


/* Private variables ---------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/

uint16_t sine_wave[SINE_WAVE_SIZE];

/* USER CODE BEGIN PFP */

/*void generate_sine_wave(void);
void start_sine_wave(void);*/
void generate_sine_wave(void);
void start_sine_wave(void);
void set_output_frequency(float freq_hz);
/* USER CODE END PFP */

/* Main program */
int main(void)
{
	peripheral_init();

	generate_sine_wave();
	start_sine_wave();

  /* Logarithmic Sweep Parameters */
	float f_min = 10.0f;      // Min frekvencija [Hz]
	float f_max = 10000.0f;   // Max frekvencija [Hz]
	float duration = 10.0f;   // Sweep trajanje [s]
	uint32_t steps = 1000;    // Broj koraka
	float t_step = duration / steps;


	for (uint32_t i = 0; i <= steps; i++) {
		float ratio = (float)i / steps;
		float freq = f_min * powf((f_max / f_min), ratio);  // log-sweep frekvencija

		char buffer[64];  // <- greška, duplirana deklaracija (već postoji izvan petlje)

		uint32_t int_part = (uint32_t)freq;
		uint32_t decimal_part = (uint32_t)((freq - int_part) * 100); // Two decimal digits
		int len= sprintf(buffer, "FREQ:%lu.%lu\n",int_part,decimal_part);
		HAL_UART_Transmit(&huart4, (uint8_t*)buffer, len, HAL_MAX_DELAY);// <- ispis na standardni izlaz (ako postoji, npr. semihosting, debug konzola)
	}

	while (1) {}
}


/* USER CODE BEGIN 4 */
void generate_sine_wave(void) {
  for (int i = 0; i < SINE_WAVE_SIZE; i++) {
	  sine_wave[i] = (uint16_t)((sin(2 * M_PI * i / SINE_WAVE_SIZE) + 1) * 2047);
  }
}

void start_sine_wave(void) {
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)sine_wave, SINE_WAVE_SIZE, DAC_ALIGN_12B_R);
	HAL_TIM_Base_Start(&htim6);
}


void set_output_frequency(float freq_hz) {
	float timer_clock = 84000000.0f; // TIM6 clock = 84 MHz
	float update_rate = freq_hz * SINE_WAVE_SIZE;
	uint32_t period = (uint32_t)(timer_clock / update_rate);

	__HAL_TIM_DISABLE(&htim6);
	__HAL_TIM_SET_AUTORELOAD(&htim6, period - 1);
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	__HAL_TIM_ENABLE(&htim6);
}

/* USER CODE END 4 */

/* Clock, DAC, Timer, DMA, GPIO INIT... */




#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
