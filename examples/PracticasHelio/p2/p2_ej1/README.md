# Instrucciones de Uso

### Compilar y ejecutar en modo nativo
```bash
make TARGET=native
./build/native/$(basename "$PWD").native
```

### Compilar y ejecutar para nRF52840 DONGLE
```bash
make TARGET=nrf52840 BOARD=dongle
make TARGET=nrf52840 BOARD=dongle $(basename "$PWD").dfu-upload
```
