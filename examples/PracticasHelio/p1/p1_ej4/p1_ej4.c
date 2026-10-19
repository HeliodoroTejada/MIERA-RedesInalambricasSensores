#include "contiki.h"
#include <stdio.h>
#include "lib/sensors.h"

PROCESS(timer_process, "Timer process");
PROCESS(read_temp, "Temperature process");
AUTOSTART_PROCESSES(&read_temp, &timer_process);



PROCESS_THREAD(read_temp, ev, data)
{
  PROCESS_BEGIN();

  static const struct sensors_sensor *sensor;
  sensor = sensors_find("Temperature");
  int raw_value=0;
  int temp_converted=0;

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);

    raw_value = sensor->value(0);
    temp_converted = raw_value/4;
    printf("Temperatura leida: %d ºC\n", temp_converted);
  }

  PROCESS_END();
}


PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();
  while(1) 
  {
    etimer_set(&timer, CLOCK_SECOND * 3);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    process_poll(&read_temp);
  }

  PROCESS_END();
}
