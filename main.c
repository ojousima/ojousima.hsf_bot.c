#include "boards.h"
#include "app_error.h"
#include <string.h>

#include "application_config.h"

#include "ruuvi_sensor.h"
#include "ruuvi_error.h"
#include "communication.h"
#include "gpio.h"
#include "application_task.h"
#include "task_adc.h"
#include "task_bluetooth.h"
#include "task_led.h"
#include "task_spi.h"

//TODO: Move to tasks
#include "yield.h"
#include "ble4_stack.h"
#include "ble4_gatt.h"
#include "interface_scheduler.h"

#define PLATFORM_LOG_MODULE_NAME main
#if MAIN_LOG_ENABLED
#define PLATFORM_LOG_LEVEL       MAIN_LOG_LEVEL
#define PLATFORM_LOG_INFO_COLOR  MAIN_INFO_COLOR
#else
#define PLATFORM_LOG_LEVEL       0
#endif
#include "platform_log.h"
PLATFORM_LOG_MODULE_REGISTER();

static uint8_t name[] = {'R', 'u', 'u', 'v', 'i'};
// static uint8_t errors = 0;
// static uint8_t error_code[20] = {'E', 'r', 'r', ':', ' '};
// static uint8_t err_index = 5;

// Read default configuration from application_config.h and initialize accelerometer with it.
// If there is error, add error information to global error counters.
// Call peripheral init before calling this to have SPI bus and timers operational.
// static ruuvi_status_t app_accelerometer_init(void)
// {
//   err_code = task_accelerometer_init();
//   ruuvi_sensor_configuration_t accelerometer_configuration;
//   accelerometer_configuration->resolution = 10;
//   err_code |= task_accelerometer_setup();
//   if (RUUVI_SUCCESS != err_code)
//   {
//     error_code[err_index++] = 'A'; // Accelerometer
//     errors++;
//   }
//   PLATFORM_LOG_INFO("Accelerometer init status: 0x%X", err_code);
// }

// Initialize bluetooth with default configuration from application_bluetooth_configuration.h
//
static ruuvi_status_t app_bluetooth_init(void)
{
  ruuvi_status_t err_code = RUUVI_SUCCESS;
  err_code |= task_bluetooth_init();
  err_code |= task_bluetooth_advertise(name, sizeof(name) - 1);
  PLATFORM_LOG_INFO("Bluetooth init status: 0x%X", err_code);
  return err_code;
}


// Init environmental sensor. Reads default configuration from application_config.h
// static ruuvi_status_t app_environmental_init()
// {
//   err_code = task_environmental_init();
//   err_code |= task_environmental_setup();
//   if (RUUVI_SUCCESS != err_code)
//   {
//     error_code[err_index++] = 'E'; // Environmental
//     errors++;
//   }
//   PLATFORM_LOG_INFO("Environmental init status: 0x%X", err_code);
// }

// Init peripherals, such as leds, timers, SPI, WDT and NFC. Default configuration is in application_config.h if applicable.
// Some board-specific configuration, such as SPI speed and pinout is in board configuration.
// If there is error, add error information to global error counters.
static ruuvi_status_t app_peripheral_init()
{
  ruuvi_status_t err_code = RUUVI_SUCCESS;
  // err_code |= task_led_init();
  // err_code |= task_spi_init();
  // task_timers_init();
  // task_rtc_init();
  // task_crypto_init();
  // task_nfc_init();
  // err_code |= task_adc_init();
  err_code |= application_task_init_distance_sensors();
  err_code |= application_task_init_motors();
  PLATFORM_LOG_INFO("Peripheral init status: 0x%X", err_code);
  return err_code;
}

// Init events
// static ruuvi_status_t app_events_init()
// {

// }

// Init periodic task
// static ruuvi_status_t app_periodic_task_init()
// {

// }

int main(void)
{
  // Init log first
  APP_ERROR_CHECK(PLATFORM_LOG_INIT(NULL));
  PLATFORM_LOG_DEFAULT_BACKENDS_INIT();
  PLATFORM_LOG_INFO("Logging started");

  // Init yield then, as other init tasks might require delays
  platform_yield_init();

  // Init peripherals, sensors will require them
  app_peripheral_init();

  // Init bluetooth
  app_bluetooth_init();

  // Init sensors
  // app_accelerometer_init();
  // app_environmental_init();

  // Run self-test
  // app_selftest();

  // init event handling
  // app_events_init();

  // app_periodic_task_init();

  // Execute schedule and go back to sleep
  platform_yield();
  platform_yield();
  while (1)
  {
    // PLATFORM_LOG_DEBUG("Processing");
    // platfrom_scheduler_execute();
    // PLATFORM_LOG_DEBUG("Yielding");
    bool left_close =  application_task_read_distance(DISTANCE_LEFT);
    PLATFORM_LOG_INFO("Left close: %d", left_close);
    // application_task_set_motor(SIDE_LEFT, left_close);
    bool right_close = application_task_read_distance(DISTANCE_RIGHT);
    PLATFORM_LOG_INFO("Right close: %d", right_close);
    // application_task_set_motor(SIDE_RIGHT, right_close);

    //if both close back up
    if(left_close && right_close)
    {
      application_task_set_motor(SIDE_RIGHT, -1);
      application_task_set_motor(SIDE_LEFT, -1);
    }

    // If neither close go forward
    if(!left_close && !right_close)
    {
      application_task_set_motor(SIDE_RIGHT, 1);
      application_task_set_motor(SIDE_LEFT, 1);
    }

    if(!left_close && right_close)
    {
      application_task_set_motor(SIDE_RIGHT, 1);
      application_task_set_motor(SIDE_LEFT, 0);
    }

    if(left_close && !right_close)
    {
      application_task_set_motor(SIDE_RIGHT, 0);
      application_task_set_motor(SIDE_LEFT, 1);
    }

    platform_delay_ms(10);
    // platform_yield();
    // PLATFORM_LOG_DEBUG("Resuming");
  }
}