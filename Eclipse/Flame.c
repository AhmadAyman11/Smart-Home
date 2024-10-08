#include "Flame.h"   // Include the header for flame sensor functionality
#include "gpio.h"    // Include the header for GPIO (General Purpose Input/Output) functionality

// Function to initialize the flame sensor
void FlameSensor_init(void)
{
	// Set the direction of the flame sensor pin to input
	GPIO_setupPinDirection(FLAME_PORT_ID, FLAME_PIN_ID, PIN_INPUT);
}

// Function to get the value from the flame sensor
uint8 FlameSensor_getValue(void)
{
	uint8 value = 0;  // Variable to store the read value from the sensor

	// Read the current value from the flame sensor pin
	value = GPIO_readPin(FLAME_PORT_ID, FLAME_PIN_ID);

	// Return the read value (0 or 1, depending on the sensor state)
	return value;
}
