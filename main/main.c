#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "task/vospi_task.h"
#include "task/display_task.h"
#include "task/shared_frame.h"

static c_frame_t c_frame;

void app_main()
{
  // Create the semaphore for the current frame
  c_frame.sem = xSemaphoreCreateBinary();

  // The semaphore isn't held to start with
  xSemaphoreGive(c_frame.sem);

  // Start tasks
  xTaskCreate(&vospi_task, "vospi_task", 30000, &c_frame, 5, NULL);
  xTaskCreate(&display_task, "display_task", 16000, &c_frame, 5, NULL);
}
