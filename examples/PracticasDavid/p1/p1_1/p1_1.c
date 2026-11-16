#include "contiki.h"
#include <stdio.h>

/* Declaración de los procesos */
PROCESS(hello_world_process, "Hello world process");
PROCESS(periodic_process, "Periodic process");

/* Iniciar ambos procesos automáticamente */
AUTOSTART_PROCESSES(&hello_world_process, &periodic_process);

/* Variable global para definir nuestro evento personalizado */
process_event_t custom_hello_event;

/*---------------------------------------------------------------------------*/
/* Proceso que genera el evento cada 5 segundos */
PROCESS_THREAD(periodic_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  /* Asignar un ID único al evento del sistema */
  custom_hello_event = process_alloc_event();

  /* Configurar el temporizador periódico a 5 segundos */
  etimer_set(&timer, CLOCK_SECOND * 5);

  while(1) {
    /* Esperar a que el temporizador expire */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    
    /* Enviar el evento al proceso hello_world_process */
    process_post(&hello_world_process, custom_hello_event, NULL);
    
    /* Reiniciar el temporizador */
    etimer_reset(&timer);
  }

  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
/* Proceso original modificado que recibe eventos e imprime */
PROCESS_THREAD(hello_world_process, ev, data)
{
  static int counter = 0;

  PROCESS_BEGIN();

  while(1) {
    /* Esperar exclusivamente hasta recibir nuestro evento personalizado */
    PROCESS_WAIT_EVENT_UNTIL(ev == custom_hello_event);

    printf("Hello World! (number %d)\n", counter);
    
    /* Incrementar contador y reiniciar al pasar de 20 */
    counter++;
    if(counter > 20) {
      counter = 0;
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/