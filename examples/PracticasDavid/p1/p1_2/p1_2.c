#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(parpadeo_1_process, "Parpadeo 1 process");
PROCESS(parpadeo_2_process, "Parpadeo 2 process");
PROCESS(timer_process, "Timer process");

AUTOSTART_PROCESSES(&parpadeo_1_process, &parpadeo_2_process, &timer_process);

/*---------------------------------------------------------------------------*/
/* Espera 5 segundos y despierta los dos procesos de parpadeo */
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 5);
  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

  process_poll(&parpadeo_1_process);
  process_poll(&parpadeo_2_process);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/* Conmuta LED1 cada 2 segundos tras recibir el poll */
PROCESS_THREAD(parpadeo_1_process, ev, data)
{
  static struct etimer timer_led1;

  PROCESS_BEGIN();

  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  etimer_set(&timer_led1, CLOCK_SECOND * 2);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_led1));
    leds_single_toggle(LEDS_LED1);
    etimer_reset(&timer_led1);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/* Conmuta LED3 cada 3 segundos tras recibir el poll */
PROCESS_THREAD(parpadeo_2_process, ev, data)
{
  static struct etimer timer_led2;

  PROCESS_BEGIN();

  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  etimer_set(&timer_led2, CLOCK_SECOND * 3);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_led2));
    leds_single_toggle(LEDS_LED3);
    etimer_reset(&timer_led2);
  }

  PROCESS_END();
}
