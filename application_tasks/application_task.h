#ifndef APPLICATION_TASK_H
#define APPLICATION_TASK_H
#include "ruuvi_error.h"
#include "boards.h"
#ifndef BOARD_HSF18BOT
  #error "This application is for HSF18 ot only"
#endif

#define SIDE_RIGHT 1
#define SIDE_LEFT  2

ruuvi_status_t application_task_init_distance_sensors(void);
ruuvi_status_t application_task_init_motors(void);

bool application_task_read_distance(uint8_t pin);
void application_task_set_motor(uint8_t side, int8_t direction);

#endif