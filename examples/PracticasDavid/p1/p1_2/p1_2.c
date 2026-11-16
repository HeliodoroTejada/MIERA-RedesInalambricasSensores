#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

/* Declaración de los procesos */
PROCESS(parpadeo_1_process, "Parpadeo 1 process");
PROCESS(parpadeo_2_process, "Parpadeo 2 process");
PROCESS(timer_process, "Timer process");

/* Iniciar los 3 procesos automáticamente */
AUTOSTART_PROCESSES(&parpadeo_1_process, &parpadeo_2_process, &timer_process);

/* Proceso que genera el evento tras 5 segundos */
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  /* Configurar el temporizador periódico a 5 segundos */
  etimer_set(&timer, CLOCK_SECOND * 5);

  /* Esperar a que el temporizador expire */
  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
  
  /* Enviar el evento process_poll a los procesos asociados a los leds */
  process_poll(&parpadeo_1_process);
  process_poll(&parpadeo_2_process);

  PROCESS_END();
}

/* Proceso encargado de la conmutación del LED1 */
PROCESS_THREAD(parpadeo_1_process, ev, data)
{
  static struct etimer timer_led1;

  PROCESS_BEGIN();

  /* Esperar exclusivamente hasta recibir el evento nativo de poll */
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);

  /* Configurar el temporizador periódico a 2 segundos */
  etimer_set(&timer_led1, CLOCK_SECOND * 2);

  while(1) {
    /* Esperar a que el temporizador expire */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_led1));
    
    /* Conmutación LED1 */
    leds_single_toggle(LEDS_LED1);
    
    /* Reiniciar el temporizador */
    etimer_reset(&timer_led1);
  }

  PROCESS_END();
}

/* Proceso encargado de la conmutación del LED2 */
PROCESS_THREAD(parpadeo_2_process, ev, data)
{
  static struct etimer timer_led2;

  PROCESS_BEGIN();

  /* Esperar exclusivamente hasta recibir el evento nativo de poll */
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);

  /* Configurar el temporizador periódico a 3 segundos */
  etimer_set(&timer_led2, CLOCK_SECOND * 3);

  while(1) {
    /* Esperar a que el temporizador expire */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_led2));
    
    /* Conmutación LED2 (RGB) */
    leds_single_toggle(LEDS_LED3);
    
    /* Reiniciar el temporizador */
    etimer_reset(&timer_led2);
  }

  PROCESS_END();
}