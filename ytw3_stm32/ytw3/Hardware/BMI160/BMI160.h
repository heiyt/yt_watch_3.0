//
// Created by heiyt_R9000P on 2024/2/28.
//

#ifndef YTW3_0_BMI160_H
#define YTW3_0_BMI160_H

#include "main.h"
#include <stdlib.h>
#include "memory.h"
void init_bmi160();
void i2c_read_data(int *gyr_x, int *gyr_y, int *gyr_z);

#endif //YTW3_0_BMI160_H
