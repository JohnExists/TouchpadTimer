/*
 * Touchpad.h
 *
 *  Created on: Aug 7, 2024
 */

#ifndef INC_TOUCHPAD_H_
#define INC_TOUCHPAD_H_

#include "stm32f4xx_hal.h"

#define FALSE 0
#define TRUE 1

typedef uint8_t bool;

// All the touchpad values
typedef struct Touchpad
{
	  // The handler for the analog to digital conversions (ADC)
	  ADC_HandleTypeDef* hadc1;
	  // Pointer to the list of channels where the ADC happens
	  uint32_t* channels;
	  // Number of channels that are active
	  uint8_t numChannels;
	  // Array of booleans for each touchpad, True if currently touched by user, false if not
	  bool* results;
	  // Array of booleans for each touchpad, True if previously touched by user, false if not
	  bool* prevResults;
} Touchpad;

/**
 * Initializes a Touchpad structure with the provided ADC handle, number of channels,
 * and channel configuration. Allocates memory for the channel array, current results,
 * and previous results.
 *
 * @param hadc1       Pointer to the ADC handle used for reading the touchpad channels.
 * @param numChannels The number of channels in the touchpad to be initialized.
 * @param channels    Array containing the ADC channel numbers to be used for the touchpad.
 * @return            A `Touchpad` structure initialized with the provided parameters.
 */
Touchpad initTouchpad(ADC_HandleTypeDef* hadc1, uint8_t numChannels,  uint32_t channels[]);

/**
 * Updates the touchpad state by checking the current status of all channels and triggering
 * a button release event if a previously pressed button is released. The previous results
 * are then updated to reflect the current state.
 *
 * @param pad Pointer to the `Touchpad` structure that contains the channel configuration
 *            and results to be updated.
 */
void updateTouchpad(Touchpad* pad);


/**
 * Checks any user interaction with the touchpad, uses default values
 *
 * @param pad       Pointer to the `Touchpad` structure containing the channels and results.
 */
void checkTouchpad(Touchpad* pad);

/**
 * Checks the touchpad channels by running multiple ADC conversion cycles and counts the number of
 * times each channel's ADC value exceeds a defined threshold. If the count exceeds the specified
 * tolerance, the corresponding channel is marked as touched.
 *
 * @param tolerance The percentage threshold to determine if a touch event has occurred.
 * @param maxCycles The maximum number of ADC conversion cycles to run for each channel.
 * @param pad       Pointer to the `Touchpad` structure containing the channels and results.
 */
void checkTouchpadA(float tolerance, int maxCycles, Touchpad* pad);

/**
 * Copies the data from one array to another different array
 *
 * @param len 	The length of one of the arrays
 * @param old 	The array where the data is being copied from
 * @param new 	The array where the data is being copied to
 *
 */
void cpyArray(size_t len, uint8_t old[], uint8_t new[]);

/**
 * Retrieves the ADC value for a specified channel in the touchpad by starting the ADC conversion,
 * polling for the result, and returning the converted value.
 *
 * @param pad     Pointer to the `Touchpad` structure containing the ADC handle.
 * @param channel The specific ADC channel to read the value from.
 * @return        The 32-bit ADC value obtained from the specified channel.
 */
uint32_t getADCVal(Touchpad* pad, uint32_t channel);

/**
 * Changes the channel from which the analog value
 * is being read from
 *
 * @param pad
 */
void OpenChannel(Touchpad* pad, uint32_t channel);


void ButtonReleasedEvent(uint8_t button);


#endif /* INC_TOUCHPAD_H_ */
