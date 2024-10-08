#ifndef FLAME_H_  // Include guard to prevent multiple inclusions
#define FLAME_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

// Define the port and pin for the flame sensor
#define FLAME_PORT_ID                PORTD_ID  // Port where the flame sensor is connected
#define FLAME_PIN_ID                 PIN2_ID   // Pin ID for the flame sensor

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

// Function to initialize the flame sensor
void FlameSensor_init(void);

// Function to get the current value from the flame sensor
uint8 FlameSensor_getValue(void);  // Returns the flame sensor value (0 or 1)

#endif /* FLAME_H_ */  // End of include guard
