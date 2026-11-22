#include "contiki.h"
#include "lib/sensors.h"
#include <stdio.h>
#include <stdint.h>

/* Referencia externa al sensor de temperatura de la plataforma */
extern const struct sensors_sensor temperature_sensor;

PROCESS(timer_process, "Proceso Temporizador");
PROCESS(temperature_process, "Proceso Lector de Temperatura");

AUTOSTART_PROCESSES(&timer_process, &temperature_process);

/*---------------------------------------------------------------------------*/
/* Dispara la lectura del sensor cada 3 segundos */
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 3);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    process_poll(&temperature_process);
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
/* Lee el sensor en cuartos de grado y lo convierte a formato decimal */
PROCESS_THREAD(temperature_process, ev, data)
{
  int32_t temp_raw;
  int32_t temp_entero;
  int32_t temp_decimal;

  PROCESS_BEGIN();

  SENSORS_ACTIVATE(temperature_sensor);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);

    temp_raw = temperature_sensor.value(0);
    temp_entero = temp_raw / 4;
    temp_decimal = (temp_raw % 4) * 25;

    if(temp_decimal < 0) {
      temp_decimal = -temp_decimal;
    }

    printf("Temperatura interna: %d.%02d C\n", (int)temp_entero, (int)temp_decimal);
  }

  SENSORS_DEACTIVATE(temperature_sensor);

  PROCESS_END();
}
