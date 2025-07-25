#ifndef SENSOR_TYPES_H_
#define SENSOR_TYPES_H_

#ifdef CONFIG_ACC_GYRO_SENSOR_ENABLE
typedef struct acc_gyro_data_t {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} acc_gyro_data_t;
#endif

#ifdef CONFIG_TEMP_SENSOR_ENABLE
typedef struct acc_gyro_data_t {
    int16_t accel_x;
} acc_gyro_data_t;
#endif

typedef struct sensor_data_t {

    #ifdef CONFIG_ACC_GYRO_ENABLE
    acc_gyro_data_t acc_gyro;
    #endif



} sensor_data_t;

#endif
