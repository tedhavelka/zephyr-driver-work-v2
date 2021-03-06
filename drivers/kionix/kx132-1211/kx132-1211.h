#ifndef KX132_1211_H
#define KX132_1211_H


// KX132-1211 sensor possible I2C addresses:
// ( See KX132-1211-Specifications-Rev-1.0.pdf for details )
#define KX132_I2C_ADDRESS__ADDR_PIN_AT_GND    (0x1E)
#define KX132_I2C_ADDRESS__ADDR_PIN_AT_IO_VDD (0x1F)
#define KX132_I2C_ADDRESS_FLIPPED__ADDR_PIN_AT_GND    (0x1C)
#define KX132_I2C_ADDRESS_FLIPPED__ADDR_PIN_AT_IO_VDD (0x1D)


#define BYTE_COUNT_OF_KX132_ACCELERATION_READING_SINGLE_AXIS (2)
#define BYTE_COUNT_OF_KX132_ACCELERATION_READING_THREE_AXES ((BYTE_COUNT_OF_KX132_ACCELERATION_READING_SINGLE_AXIS) * 3) 



// For following defines see Kionix document
// KX132-1211-Technical-Reference-Manual-Rev-3.0.pdf

// Note following are KX132-1211 config' register addresses:
#define MAN_ID (0x00)
#define PART_ID (0x01)

#define KX132_1211_ACCELEROMETER_XOUT_L    (0x08)
#define KX132_1211_ACCELEROMETER_XOUT_H    (0x09)
#define KX132_1211_ACCELEROMETER_YOUT_L    (0x0A)
#define KX132_1211_ACCELEROMETER_YOUT_H    (0x0B)
#define KX132_1211_ACCELEROMETER_ZOUT_L    (0x0C)
#define KX132_1211_ACCELEROMETER_ZOUT_H    (0x0D)

#define KX132_1211_CONFIG_REGISTER__CNTL   (0x1B)
#define KX132_1211_CONFIG_REGISTER__ODCNTL (0x21)
//#define KX132_1211_CONFIG_REGISTER__

// Given Zephyr's lower level I2C API, our sensor query type commands
//  are effectively one byte in size and contain the address of the
//  sensor configuration register from which to read:
#define CMD_KX132_REQUEST_MANUFACTURER_ID { MAN_ID }
#define CMD_KX132_REQUEST_PART_ID { PART_ID }



// Note:  Zephyr Project 2.6.0 provides sensor.h header file in
//  ncs/zephyr/include/drivers/sensor.h.  An important enum given here
//  is named sensor_channel.  Near it's end last two elements are:
//
//    189         SENSOR_CHAN_PRIV_START = SENSOR_CHAN_COMMON_COUNT,
//
//    194         SENSOR_CHAN_MAX = INT16_MAX,
//
//  Until we find better we're going to use "sensor channel private start"
//  enum element to provide some custom channels to Kionix KX132-1211.
//----------------------------------------------------------------------

enum sensor_channels_kionix_specific {
    SENSOR_CHAN_KIONIX_START = (SENSOR_CHAN_PRIV_START + 1),
    SENSOR_CHAN_KIONIX_MANUFACTURER_ID,
    SENSOR_CHAN_KIONIX_PART_ID,
    SENSOR_CHAN_KIONIX_END,
};


// REF https://docs.zephyrproject.org/latest/reference/peripherals/sensor.html#c.sensor_attribute
// REF from Kionix AN092-Getting-Stated.pdf

// QUESTION:  how do we keep our and any custom enumerated sensor
//  attributes from colliding with other third party, out-of-tree
//  driver enumerations?
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum kx132_1211_config_setting_e
{
    KX132_CONFIGURATION_SETTING_FIRST,

// From AN092-Getting-Stated.pdf:
    KX132_ENABLE_ASYNC_READINGS,
    KX132_ENABLE_SYNC_READINGS_WITH_HW_INTERRUPT,
    KX132_ENABLE_SYNC_READINGS_WITHOUT_HW_INTERRUPT,
    KX132_ENABLE_ACCELEROMETER_READINGS_BUFFER,
    KX132_ENABLE_WATERMARK_INTERRUPT,
    KX132_SET_TRIGGER_MODE,
    KX132_ENABLE_WAKE_UP,
    KX132_ENABLE_WAKE_UP_AND_BACK_TO_SLEEP,
    KX132_ENABLE_TILT_POSITION_WITH_FACE_DETECT,
    KX132_ENABLE_TAP_DOUBLE_TAP,
    KX132_ENABLE_FREE_FALL_ENGINE,

// From AN109-...-3p0.pdf
    KX132_SET_OUTPUT_DATA_RATE,

    KX132_CONFIGURATION_SETTING_LAST
};


// REF Kionix document KX132-1211-Technical-Reference-Manual-Rev-3.0.pdf
// ODCNTL (0x21) control register, pages 25..26 of 75. 
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

enum kx132_1211_output_data_rates_e
{
    KX132_ODR__0P781_HZ,
    KX132_ODR__1P563_HZ,
    KX132_ODR__3P125_HZ,
    KX132_ODR__6P25_HZ,

    KX132_ODR_12P5_HZ,
    KX132_ODR_25_HZ,
    KX132_ODR_50_HZ,
    KX132_ODR_100_HZ,

    KX132_ODR_200_HZ,
    KX132_ODR_400_HZ,
    KX132_ODR_800_HZ,
    KX132_ODR_1600_HZ,

    KX132_ODR_3200_HZ,
    KX132_ODR_6400_HZ,
    KX132_ODR_12800_HZ,
    KX132_ODR_25600_HZ,
};



#endif // KX132_1211_H
