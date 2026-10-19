
#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>



PROCESS(parpadeo_1_process, "Hello world process");
PROCESS(parpadeo_2_process, "Periodic Process process");
PROCESS(timer_process, "Timer process");
AUTOSTART_PROCESSES(&parpadeo_1_process, &parpadeo_2_process, &timer_process);


PROCESS_THREAD(parpadeo_1_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  while(1) {
    leds_single_toggle(LEDS_LED1);
    etimer_set(&timer, CLOCK_SECOND * 2);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
  }

  PROCESS_END();
}


PROCESS_THREAD(parpadeo_2_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  while(1) {
    leds_single_toggle(LEDS_LED2);
    etimer_set(&timer, CLOCK_SECOND * 3);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
  }

  PROCESS_END();
}


PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 5);

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
  process_poll(&parpadeo_2_process);
  process_poll(&parpadeo_1_process);

  PROCESS_END();
}
