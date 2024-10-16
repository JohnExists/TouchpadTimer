/*
 * Timer.h
 *
 *  Created on: Aug 7, 2024
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <string.h>
#include <stm32f4xx_hal.h>
#include <Touchpad.h>

// The pre-set values for the seven segment timer
#define SEGMENT_A_PIN_TYPE GPIOB
#define SEGMENT_A_PIN_NUMBER GPIO_PIN_0

#define SEGMENT_B_PIN_TYPE GPIOB
#define SEGMENT_B_PIN_NUMBER GPIO_PIN_1

#define SEGMENT_C_PIN_TYPE GPIOB
#define SEGMENT_C_PIN_NUMBER GPIO_PIN_2

#define SEGMENT_D_PIN_TYPE GPIOB
#define SEGMENT_D_PIN_NUMBER GPIO_PIN_3

#define SEGMENT_E_PIN_TYPE GPIOB
#define SEGMENT_E_PIN_NUMBER GPIO_PIN_4

#define SEGMENT_F_PIN_TYPE GPIOB
#define SEGMENT_F_PIN_NUMBER GPIO_PIN_5

#define SEGMENT_G_PIN_TYPE GPIOB
#define SEGMENT_G_PIN_NUMBER GPIO_PIN_6

#define BUZZER_PIN_TYPE GPIOB
#define BUZZER_PIN_NUMBER GPIO_PIN_7

#define LED_PIN_TYPE GPIOB
#define LED_PIN_NUMBER GPIO_PIN_12


#define FALSE 0
#define TRUE 1

typedef uint8_t bool;

typedef struct Timer
{
	// The length of the timer in seconds
	uint8_t currentSelectedValue;
	// True if timer is running, fale if not
	bool isEnabled;
	// The epoch time when the timer will end
	uint32_t endTime;
} Timer;

/**
 * @brief Initializes the entire program, ADC channels and begins the main loop
 */
void launchTimer();
/**
 * @brief Updates the current state of the timer
 *
 * @param timer The timer that will be updated
 */
void updateTimer(Timer* timer);

/**
 * @brief Performs a function on the current timer
 *
 * @param action The function to perform (0 = START/STOP, 1 = INCREMENT, 2 = DECREMENT)
 *
 */
void useTimer(int action);

/**
 * @brief Activates segments on a seven-segment display to display a specified number.
 *
 * This function turns on segments on a seven-segment display to display a number
 * ranging from 0 to 9 based on predefined segment arrangements.
 *
 * @param number The number to display on the seven-segment display (0 to 9).
 *
 */
void Active_Seven_Segment(int number);

/**
 * @brief Sets the state of specified segments on a seven-segment display.
 *
 * This function sets the state (on/off) of segments on a seven-segment display
 * based on the provided letters that represent segment labels.
 *
 * @param letters A string containing the segment labels to set from a-f (e.g., "abc").
 * @param state The desired state of the segments (GPIO_PIN_SET or GPIO_PIN_RESET).
 *
 */
void Set_Seven_Segment_Pin(const char* letters, uint16_t state);



#endif /* INC_TIMER_H_ */
