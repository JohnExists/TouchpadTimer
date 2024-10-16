#include "Touchpad.h"


Touchpad initTouchpad(ADC_HandleTypeDef* hadc1, uint8_t numChannels,  uint32_t channels[])
{
	Touchpad pad;
	pad.hadc1 = hadc1;
	pad.numChannels = numChannels;
	pad.channels = malloc(sizeof(uint32_t) * numChannels);
	pad.results = malloc(sizeof(bool) * numChannels);
	pad.prevResults = malloc(sizeof(bool) * numChannels);

	for(int i = 0; i < numChannels; ++i)
	{
		pad.results[i] = FALSE;
		pad.prevResults[i] = FALSE;
		pad.channels[i] = channels[i];
	}

	return pad;
}

void updateTouchpad(Touchpad* pad)
{
	  checkTouchpad(pad);

	  // Checks if touchpad was released
	  for(int i = 0; i < pad->numChannels; ++i)
	  {
		  if(pad->prevResults[i] == TRUE && pad->results[i] == FALSE) ButtonReleasedEvent(i);
	  }

	  // Copies the current to the previous results
	  cpyArray(pad->numChannels, pad->results, pad->prevResults);
}

void checkTouchpad(Touchpad* pad)
{
	  const float TOLERANCE = 0.25;
	  const float MAX_CYCLES = 80.0;
	  checkTouchpadA(TOLERANCE, MAX_CYCLES, pad);
}


void checkTouchpadA(float tolerance, int maxCycles, Touchpad* pad)
{
	size_t numChannels = pad->numChannels;
	uint32_t* channels = pad->channels;
	uint8_t* results = pad->results;

	const int HIGH = 3500;
	// Counts the number of times a touch pad returns an
	// analog value greater than HIGH
	uint32_t High_ADC_Count[numChannels];
	for(int i = 0; i < numChannels; ++i) High_ADC_Count[i] = 0;

	// Runs through X number of cycles to count the number of HIGHs
	for(int i = 0; i < maxCycles; ++i)
	{
		  for(int i = 0 ; i < numChannels; ++i)
		  {
			  if(getADCVal(pad, channels[i]) <= HIGH) continue;
			  High_ADC_Count[i] = High_ADC_Count[i] + 1;
		  }
	}

	// Updates the results array with new data
	for(int i = 0; i < numChannels; ++i)
	{
		if(High_ADC_Count[i] > (uint8_t)(maxCycles * tolerance)) results[i] = TRUE;
		else results[i] = 0;
	}
}

uint32_t getADCVal(Touchpad* pad, uint32_t channel)
{
	  uint32_t result = 0;
	  OpenChannel(pad, channel);
	  HAL_ADC_Start(pad->hadc1);
	  HAL_ADC_PollForConversion(pad->hadc1, 80);
	  result = HAL_ADC_GetValue(pad->hadc1);
	  HAL_ADC_Stop(pad->hadc1);
	  return result;
}



void cpyArray(size_t len, uint8_t old[], uint8_t new[])
{
	for(int i = 0; i < len; ++i) new[i] = old[i];
}


void OpenChannel(Touchpad* pad, uint32_t channel)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = channel;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(pad->hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}
