#include "application_task.h"
#include "ruuvi_error.h"
#include "boards.h"
#include "gpio.h"

ruuvi_status_t application_task_init_distance_sensors(void)
{
  ruuvi_status_t err_code = RUUVI_SUCCESS;
  err_code |= platform_gpio_init();
  err_code |= platform_gpio_configure(DISTANCE_LEFT, RUUVI_GPIO_MODE_INPUT_PULLUP);
  err_code |= platform_gpio_configure(DISTANCE_RIGHT, RUUVI_GPIO_MODE_INPUT_PULLUP);

  return err_code;
}

bool application_task_read_distance(uint8_t pin)
{
  bool close = false;
  platform_gpio_read(pin, &close);
  return !close;
}

ruuvi_status_t application_task_init_motors(void)
{
  ruuvi_status_t err_code = RUUVI_SUCCESS;
  err_code |= platform_gpio_init();
  err_code |= platform_gpio_configure(MOTOR_LEFT_FORWARD, RUUVI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= platform_gpio_clear(MOTOR_LEFT_FORWARD);

  err_code |= platform_gpio_configure(MOTOR_LEFT_BACKWARD, RUUVI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= platform_gpio_clear(MOTOR_LEFT_BACKWARD);

  err_code |= platform_gpio_configure(MOTOR_RIGHT_FORWARD, RUUVI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= platform_gpio_clear(MOTOR_RIGHT_FORWARD);

  err_code |= platform_gpio_configure(MOTOR_RIGHT_BACKWARD, RUUVI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= platform_gpio_clear(MOTOR_RIGHT_BACKWARD);
  return err_code;
}

void application_task_set_motor(uint8_t side, int8_t direction)
{

  uint8_t forward  = (side == SIDE_RIGHT) ? MOTOR_RIGHT_FORWARD : MOTOR_LEFT_FORWARD;
  uint8_t backward = (side == SIDE_RIGHT) ? MOTOR_RIGHT_BACKWARD : MOTOR_LEFT_BACKWARD;
  platform_gpio_clear(forward);
  platform_gpio_clear(backward);
  if(1 == direction)  { platform_gpio_set(forward); }
  if(-1 == direction) { platform_gpio_set(backward); }
}