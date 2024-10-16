#include "Timer.h"

inline bool isBuzzerEnabled = FALSE;
inline Timer timer;

void launchTimer(ADC_HandleTypeDef* hadc1)
{
	  // The channels where the ADC values are going to be read
	  uint32_t channels[3] = {ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_4 };
	  uint8_t numChannels = sizeof(channels) / sizeof(uint32_t);
	  // Creates a new touchpad object
	  Touchpad pad = initTouchpad(hadc1, numChannels, channels);

	  // Initializes the timer
	  timer.currentSelectedValue = 1;
	  timer.isEnabled = FALSE;
	  timer.endTime = -1;

	  // Begins the main loop
	  while (1)
	  {
		  updateTouchpad(&pad);
		  updateTimer(&timer);

		  if(isBuzzerEnabled)
		  {
			  HAL_GPIO_WritePin(BUZZER_PIN_TYPE, BUZZER_PIN_NUMBER, GPIO_PIN_SET);
			  HAL_Delay(50);
			  HAL_GPIO_WritePin(BUZZER_PIN_TYPE, BUZZER_PIN_NUMBER, GPIO_PIN_RESET);
			  isBuzzerEnabled = FALSE;
		  }
	  }
}

void updateTimer(Timer* timer)
{
	  if(!timer->isEnabled)
	  {
		  Active_Seven_Segment(timer->currentSelectedValue);
		  HAL_GPIO_WritePin(LED_PIN_TYPE, LED_PIN_NUMBER, GPIO_PIN_RESET);
	  }
	  if(timer->isEnabled)
	  {
		  // Turns on LED when timer is active
		  HAL_GPIO_WritePin(LED_PIN_TYPE, LED_PIN_NUMBER, GPIO_PIN_SET);
		  int timeLeft = timer->endTime - HAL_GetTick();
		  // Displays time left on seven segment display
		  Active_Seven_Segment((int)(timeLeft / 1000.0));

		  // When the timer ends, turns on the buzzer and disables timer
		  if(timeLeft <= 0)
		  {
			  for(int i = 0; i < 3; ++i)
			  {
				  HAL_GPIO_WritePin(BUZZER_PIN_TYPE, BUZZER_PIN_NUMBER, GPIO_PIN_SET);
				  HAL_GPIO_TogglePin(LED_PIN_TYPE, LED_PIN_NUMBER);
				  HAL_Delay(250);
				  HAL_GPIO_WritePin(BUZZER_PIN_TYPE, BUZZER_PIN_NUMBER, GPIO_PIN_RESET);
				  HAL_GPIO_TogglePin(LED_PIN_TYPE, LED_PIN_NUMBER);
				  HAL_Delay(250);
			  }
			  timer->isEnabled = FALSE;
		  }
	  }
}



void ButtonReleasedEvent(uint8_t buttonReleased)
{
	  isBuzzerEnabled = TRUE;
	  useTimer(buttonReleased);
}


void useTimer(int action)
{
	switch (action) {
		// START/STOP
		case 0:
			  if(timer.isEnabled)
			  {
				  timer.isEnabled = FALSE;
			  } else if (!timer.isEnabled) {
				  timer.isEnabled = TRUE;
				  timer.endTime = HAL_GetTick() + (timer.currentSelectedValue * 1000);
			  }
			break;
		// INCREMENT TIMER
		case 1:
			  if(timer.currentSelectedValue < 9) timer.currentSelectedValue++;
			break;
		// DECREMENT TIMER
		case 2:
			  if(timer.currentSelectedValue > 1) timer.currentSelectedValue--;
			break;
	}
}


void Set_Seven_Segment_Pin(const char* letters, uint16_t state)
{
	for(int i = 0; i < (int)strlen(letters); ++i)
	{
		char it = letters[i];

		switch (it) {
			case 'a':
				HAL_GPIO_WritePin(SEGMENT_A_PIN_TYPE, SEGMENT_A_PIN_NUMBER, state);
				break;
			case 'b':
				HAL_GPIO_WritePin(SEGMENT_B_PIN_TYPE, SEGMENT_B_PIN_NUMBER, state);
				break;
			case 'c':
				HAL_GPIO_WritePin(SEGMENT_C_PIN_TYPE, SEGMENT_C_PIN_NUMBER, state);
				break;
			case 'd':
				HAL_GPIO_WritePin(SEGMENT_D_PIN_TYPE, SEGMENT_D_PIN_NUMBER, state);
				break;
			case 'e':
				HAL_GPIO_WritePin(SEGMENT_E_PIN_TYPE, SEGMENT_E_PIN_NUMBER, state);
				break;
			case 'f':
				HAL_GPIO_WritePin(SEGMENT_F_PIN_TYPE, SEGMENT_F_PIN_NUMBER, state);
				break;
			case 'g':
				HAL_GPIO_WritePin(SEGMENT_G_PIN_TYPE, SEGMENT_G_PIN_NUMBER, state);
				break;
		}
	}
}

void Active_Seven_Segment(int number)
{
	if(number > 9 || number < 0) return;

	const char* numericArangements[10] = {"abcdef", "bc", "abged", "abgcd", "fgbc",
			"afgcd", "afgcde", "abc", "abcdefg", "abcdgf"};


	// Switches all the segment lights off
	Set_Seven_Segment_Pin("abcdefg", GPIO_PIN_RESET);

	// Turns on the pins for the correct number
	Set_Seven_Segment_Pin(numericArangements[number], GPIO_PIN_SET);

}
