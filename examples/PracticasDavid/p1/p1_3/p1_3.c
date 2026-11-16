#include "contiki.h"
#include "lib/sensors.h"
#include <stdio.h>
#include <stdint.h>

/* Declarar la existencia del sensor de temperatura para evitar errores de compilación */
extern const struct sensors_sensor temperature_sensor;

/* Declaración de los procesos independientes */
PROCESS(timer_process, "Proceso Temporizador");
PROCESS(temperature_process, "Proceso Lector de Temperatura");

/* Iniciar ambos procesos automáticamente */
AUTOSTART_PROCESSES(&timer_process, &temperature_process);

/* -------------------------------------------------------------------------- */
/* PROCESO 1: Encargado exclusivamente de generar el aviso cada 3 segundos */
/* -------------------------------------------------------------------------- */
PROCESS_THREAD(timer_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  /* Configurar el temporizador periódico a 3 segundos */
  etimer_set(&timer, CLOCK_SECOND * 3);

  while(1) {
    /* Esperar a que el temporizador expire */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    
    /* Enviar el evento process_poll al proceso encargado de leer el sensor */
    process_poll(&temperature_process);
    
    /* Reiniciar el temporizador para los próximos 3 segundos */
    etimer_reset(&timer);
  }

  PROCESS_END();
}

/* -------------------------------------------------------------------------- */
/* PROCESO 2: Encargado de leer el sensor e imprimir el valor */
/* -------------------------------------------------------------------------- */
PROCESS_THREAD(temperature_process, ev, data)
{
  int32_t temp_raw;
  int32_t temp_entero;
  int32_t temp_decimal;

  PROCESS_BEGIN();

  /* Función de activación: Enciende el sensor de temperatura */
  SENSORS_ACTIVATE(temperature_sensor);

  while(1) {
    /* Quedarse bloqueado esperando el aviso (poll) del timer_process */
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);

    /* Función de lectura: Obtener el valor del sensor (en cuartos de grado) */
    temp_raw = temperature_sensor.value(0);

    /* Convertir el formato raw a grados centígrados (Celsius) */
    temp_entero = temp_raw / 4;
    temp_decimal = (temp_raw % 4) * 25;
    
    /* Manejar temperaturas bajo cero para que el decimal no sea negativo */
    if(temp_decimal < 0) {
        temp_decimal = -temp_decimal;
    }

    /* Imprimir por pantalla el valor leído */
    printf("Temperatura interna: %d.%02d C\n", (int)temp_entero, (int)temp_decimal);
  }

  /* Función de desactivación: Apaga el sensor (en este código nunca se alcanza) */
  SENSORS_DEACTIVATE(temperature_sensor);

  PROCESS_END();
}