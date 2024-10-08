#ifndef LDR_H_  // Include guard to prevent multiple inclusions
#define LDR_H_

#include "std_types.h"  // Include standard types header for type definitions

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LDR_SENSOR_CHANNEL_ID             0   // ADC channel for the LDR sensor
#define LDR_SENSOR_MAX_VOLT_VALUE         2.56 // Maximum voltage output from the LDR
#define LDR_SENSOR_MAX_LIGHT_INTENSITY    100  // Maximum light intensity value

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

// Function to get the current light intensity from the LDR
uint16 LDR_getLightIntensity(void);  // Returns the light intensity as an unsigned 16-bit integer

#endif /* LDR_H_ */  // End of include guard
