#include "contiki.h"
#include <stdio.h>

PROCESS(hello_world_process, "Hello world process");
PROCESS(periodic_process, "Periodic process");

AUTOSTART_PROCESSES(&hello_world_process, &periodic_process);

/* Evento personalizado para sincronizar ambos procesos */
process_event_t custom_hello_event;

/*---------------------------------------------------------------------------*/
/* Genera un evento cada 5 segundos */
PROCESS_THREAD(periodic_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  custom_hello_event = process_alloc_event();
  etimer_set(&timer, CLOCK_SECOND * 5);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    process_post(&hello_world_process, custom_hello_event, NULL);
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/* Espera el evento periodico e imprime el contador (0 a 20) */
PROCESS_THREAD(hello_world_process, ev, data)
{
  static int counter = 0;

  PROCESS_BEGIN();

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == custom_hello_event);

    printf("Hello World! (number %d)\n", counter);

    counter++;
    if(counter > 20) {
      counter = 0;
    }
  }

  PROCESS_END();
}
