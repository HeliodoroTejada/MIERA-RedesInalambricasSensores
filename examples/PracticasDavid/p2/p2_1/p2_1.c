
#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

/* Declaración de las 3 tareas */
PROCESS(tarea_1_process, "Tarea 1 - LED Verde");
PROCESS(tarea_2_process, "Tarea 2 - LED Amarillo");
PROCESS(tarea_3_process, "Tarea 3 - Temporizador");

/* Arranque automático de los 3 procesos */
AUTOSTART_PROCESSES(&tarea_1_process, &tarea_2_process, &tarea_3_process);

/* -------------------------------------------------------------------------- */
/* TAREA 3: Temporizador de 3 segundos que lanza eventos a Tarea 1 y Tarea 2  */
/* -------------------------------------------------------------------------- */
PROCESS_THREAD(tarea_3_process, ev, data)
{
  static struct etimer timer_inicio;

  PROCESS_BEGIN();

  printf("Tarea 3: Iniciando temporizador de 3 segundos...\n");
  etimer_set(&timer_inicio, CLOCK_SECOND * 3);

  PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_inicio));

  printf("Tarea 3: Timer expirado. Lanzando eventos a Tarea 1 y Tarea 2.\n");
  process_poll(&tarea_1_process);
  process_poll(&tarea_2_process);

  PROCESS_END();
}

/* -------------------------------------------------------------------------- */
/* TAREA 1: Parpadeo de LEDS_GREEN cada 2 segundos tras recibir evento        */
/* -------------------------------------------------------------------------- */
PROCESS_THREAD(tarea_1_process, ev, data)
{
  static struct etimer timer_green;

  PROCESS_BEGIN();

  /* Esperar evento de la Tarea 3 */
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  printf("Tarea 1: Evento recibido. Iniciando parpadeo LEDS_GREEN (2s).\n");

  etimer_set(&timer_green, CLOCK_SECOND * 2);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_green));
    leds_toggle(LEDS_GREEN);
    printf("Tarea 1: Toggle LEDS_GREEN\n");
    etimer_reset(&timer_green);
  }

  PROCESS_END();
}

/* -------------------------------------------------------------------------- */
/* TAREA 2: Parpadeo de LEDS_YELLOW cada 4 segundos tras recibir evento       */
/* -------------------------------------------------------------------------- */
PROCESS_THREAD(tarea_2_process, ev, data)
{
  static struct etimer timer_yellow;

  PROCESS_BEGIN();

  /* Esperar evento de la Tarea 3 */
  PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
  printf("Tarea 2: Evento recibido. Iniciando parpadeo LEDS_YELLOW (4s).\n");

  etimer_set(&timer_yellow, CLOCK_SECOND * 4);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer_yellow));
    leds_toggle(LEDS_YELLOW);
    printf("Tarea 2: Toggle LEDS_YELLOW\n");
    etimer_reset(&timer_yellow);
  }

  PROCESS_END();
}