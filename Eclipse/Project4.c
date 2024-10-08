#include "adc.h"               // Include ADC driver for analog reading
#include "lcd.h"               // Include LCD driver for display
#include "lm35_sensor.h"       // Include LM35 temperature sensor driver
#include <avr/io.h>            // AVR IO library for Microcontroller
#include "Flame.h"             // Include flame sensor driver
#include "LDR.h"               // Include LDR (Light Dependent Resistor) driver
#include <util/delay.h>        // Include delay functions
#include "PWM.h"               // Include PWM driver for motor control
#include "DCmotor.h"           // Include DC motor driver
#include "LED.h"               // Include LED driver
#include "BUZZER.h"            // Include buzzer driver

int main(void)
{
	uint8 temp;               // Variable to hold temperature reading
	uint16 intensity;         // Variable to hold light intensity reading
	uint8 Flame;              // Variable to hold flame sensor value
	uint8 Rotation;           // Variable to hold motor rotation state

	Rotation = STOP;          // Initialize motor rotation state to STOP

	LCD_init();               // Initialize the LCD
	ADC_init();               // Initialize the ADC
	FlameSensor_init();       // Initialize the flame sensor
	DcMotor_Init();           // Initialize the DC motor
	LEDS_init();              // Initialize the LEDs
	Buzzer_init();            // Initialize the buzzer


	// Display initial messages on the LCD
	LCD_displayStringRowColumn(0,4,"Fan is ");
	LCD_displayStringRowColumn(1,0,"Temp=   ");
	LCD_displayStringRowColumn(1,8,"LDR=   %");

	while(1)
	{
		// Read temperature, light intensity, and flame sensor values
		temp = LM35_getTemperature();
		intensity = LDR_getLightIntensity();
		Flame = FlameSensor_getValue();

		// Check if flame is detected
		if(Flame == 1)
		{
			// Display alert on LCD
			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("Critical Alert!");
			Buzzer_on();	// Activate buzzer
			DcMotor_Rotate(STOP, 0);	// Stop the motor

			// Wait for flame to clear
			while (Flame == 1)
			{
				_delay_ms(100);	// Delay for stability
				Flame = FlameSensor_getValue();	// Read flame sensor again
				// Turn off LEDs
				LED_off(0);
				LED_off(1);
				LED_off(2);
			}

			LCD_clearScreen();	// Clear the screen after flame is no longer detected

			LCD_displayStringRowColumn(0, 4, "Fan is ");
			LCD_displayStringRowColumn(1, 0, "Temp=   ");
			LCD_displayStringRowColumn(1, 8, "LDR=   %");

		}
		else
		{
			Buzzer_off();	// Deactivate buzzer if no flame
			/* Display the temperature value every time */
			if(temp >= 100)
			{
				LCD_moveCursor(1,5);
				LCD_intgerToString(temp);	// Convert and display temperature
			}
			else
			{
				LCD_moveCursor(1,5);
				LCD_intgerToString(temp);	// Convert and display temperature
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}

			if(temp >= 25)
			{
				LCD_moveCursor(0,11);
				LCD_displayString("ON");	// Display "ON" if temperature is above threshold
				LCD_displayCharacter(' ');
			}
			else
			{
				LCD_moveCursor(0,11);
				LCD_displayString("OFF");	// Display "OFF" if temperature is below threshold
			}

			if(intensity == 100)
			{
				LCD_moveCursor(1,12);
				LCD_intgerToString(intensity);	// Convert and display intensity
			}
			else
			{
				LCD_moveCursor(1,12);
				LCD_intgerToString(intensity);	// Convert and display intensity
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}

			// Control motor speed based on temperature
			if (temp >= 40)
			{
				DcMotor_Rotate(CLOCKWISE, 100); // 100% speed
			}
			else if (temp >= 35)
			{
				DcMotor_Rotate(CLOCKWISE, 75);  // 75% speed
			}
			else if (temp >= 30)
			{
				DcMotor_Rotate(CLOCKWISE, 50);  // 50% speed
			}
			else if (temp >= 25)
			{
				DcMotor_Rotate(CLOCKWISE, 25);  // 25% speed
			}
			else if(temp < 25)
			{
				DcMotor_Rotate(STOP, 0);        // Motor OFF
			}

			// Control LEDs based on light intensity
			if(intensity >= 70)
			{
				// Turn off all LEDs if intensity is high
				LED_off(0);
				LED_off(1);
				LED_off(2);
			}
			else if((intensity >= 51) && (intensity < 70))
			{
				// Turn on Red LED for medium intensity
				LED_on(0);
				LED_off(1);
				LED_off(2);
			}
			else if((intensity >= 16) && (intensity < 50))
			{
				// Turn on Red and Green LEDs for lower intensity
				LED_on(0);
				LED_on(1);
				LED_off(2);
			}
			else if((intensity < 16) )
			{
				// Turn on all LEDs for very low intensity
				LED_on(0);
				LED_on(1);
				LED_on(2);
			}

		}

		_delay_ms(100);	// Delay to prevent rapid loop execution
	}

}
