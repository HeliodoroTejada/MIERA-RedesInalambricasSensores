# Práctica 1 - Ejercicio 1: Búsqueda de ficheros de la plataforma nRF52840

Rutas de los ficheros fuente (`.c`) y de cabecera (`.h`) correspondientes a los drivers de cada uno de los chips que componen la placa utilizada en las prácticas en Contiki-NG (`release/v5.1`):

## 1. Microcontrolador (Nordic nRF52840 SoC)
* **Arquitectura y configuración específica del MCU:**
  * `~/contiki-ng/arch/cpu/nrf52840/nrf52840-def.h`
  * `~/contiki-ng/arch/cpu/nrf52840/nrf52840-conf.h`
  * `~/contiki-ng/arch/cpu/nrf52840/rtimer-arch.c`
  * `~/contiki-ng/arch/cpu/nrf52840/rtimer-arch.h`
  * `~/contiki-ng/arch/cpu/nrf52840/watchdog-arch.c`
* **Drivers base de periféricos internos (GPIO, relojes):**
  * `~/contiki-ng/arch/cpu/nrf/nrf-gpio.c`
  * `~/contiki-ng/arch/cpu/nrf/nrf-gpio.h`
  * `~/contiki-ng/arch/cpu/nrf/nrf-clock.c`
  * `~/contiki-ng/arch/cpu/nrf/nrf-clock.h`
* **Definición de la placa (`dongle`):**
  * `~/contiki-ng/arch/platform/nrf52840/dongle/dongle-def.h`
  * `~/contiki-ng/arch/platform/nrf52840/dongle/board.h`
  * `~/contiki-ng/arch/platform/nrf52840/dongle/leds-arch.c`

## 2. Transceiver radio (Radio integrada IEEE 802.15.4 de 2.4 GHz)
El SoC nRF52840 integra el transceptor radio dentro del propio chip. Sus drivers para IEEE 802.15.4 son:
* `~/contiki-ng/arch/cpu/nrf/net/nrf-ieee-driver.c`
* `~/contiki-ng/arch/cpu/nrf/net/nrf-ieee-driver.h`

## 3. Almacenamiento externo (Memoria Flash SPI / QSPI)
> **Nota hardware:** La variante utilizada en las prácticas (`BOARD=dongle`) **no incorpora chip de memoria Flash externa** en la PCB.

Los drivers de soporte en el repositorio para esta plataforma son:
* **Driver genérico de memoria Flash externa SPI:**
  * `~/contiki-ng/arch/dev/ext-flash/ext-flash.c`
  * `~/contiki-ng/arch/dev/ext-flash/ext-flash.h`
* **Controladores de bus serie SPI / QSPI del MCU:**
  * `~/contiki-ng/arch/cpu/nrf/nrf-spim.c`
  * `~/contiki-ng/arch/cpu/nrf/nrf-spim.h`
  * `~/contiki-ng/arch/cpu/nrf/nrf-qspi.c`
  * `~/contiki-ng/arch/cpu/nrf/nrf-qspi.h`
* **Definición del chip externo (en variante DK):**
  * `~/contiki-ng/arch/platform/nrf52840/dk/mx25r6435f-def.h`

## 4. Almacenamiento interno (Memoria Flash interna de 1 MB del nRF52840)
* **Adaptación de almacenamiento en Flash para la plataforma nrf52840 (Coffee FS):**
  * `~/contiki-ng/arch/platform/nrf52840/common/cfs-coffee-arch.c`
  * `~/contiki-ng/arch/platform/nrf52840/common/cfs-coffee-arch.h`
* **Driver del controlador de memoria no volátil interna (NVMC):**
  * `~/contiki-ng/arch/cpu/nrf/lib/nrfx/drivers/src/nrfx_nvmc.c`
  * `~/contiki-ng/arch/cpu/nrf/lib/nrfx/drivers/include/nrfx_nvmc.h`
* **Sistema de archivos genérico en Flash de Contiki-NG:**
  * `~/contiki-ng/os/storage/cfs/cfs-coffee.c`
  * `~/contiki-ng/os/storage/cfs/cfs-coffee.h`