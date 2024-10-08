#include "LDR.h"    // Include the header for LDR functionality
#include "adc.h"    // Include the header for ADC (Analog to Digital Converter) functionality

// Function to get the light intensity from the LDR
uint16 LDR_getLightIntensity(void)
{
    float voltage = 0;                // Variable to store the calculated voltage
    float light_intensity = 0;        // Variable to store the calculated light intensity
    uint16 adc_value = 0;             // Variable to store the raw ADC value

    // Read the ADC value from the specified LDR sensor channel
    adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

    // Convert the raw ADC value to voltage
    // voltage = (adc_value / ADC_MAXIMUM_VALUE) * LDR_SENSOR_MAX_VOLT_VALUE
    voltage = (adc_value * LDR_SENSOR_MAX_VOLT_VALUE) / ADC_MAXIMUM_VALUE;

    // Convert voltage to light intensity
    // light_intensity is calculated as a proportion of the maximum light intensity
    light_intensity = ((voltage / LDR_SENSOR_MAX_VOLT_VALUE)) * LDR_SENSOR_MAX_LIGHT_INTENSITY;

    // Return the calculated light intensity as an unsigned 16-bit integer
    return (uint16)light_intensity;
}
