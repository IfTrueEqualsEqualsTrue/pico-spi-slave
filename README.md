# PIO SPI Slave (for Raspberry Pi Pico)

This project implements an half-duplex SPI slave interface, using the Raspberry Pi Pico's PIO. The slave responds to SPI signals from a master by sending an 8-bit counter value, increasing with each request.

## Features

- SPI slave implemented in PIO assembly (half
- MSB-first data shifting for compatibility with Raspberry Pi's `spidev`
- 8-bit counter value sent on each transfer
- Minimal external dependencies (only uses `pico-sdk`)

## Wiring

| Pico Pin | Function    |
|----------|-------------|
| GP0      | SPI CS (Chip Select)  |
| GP1      | SPI SCK (Clock)       |
| GP2      | SPI MISO (Data Out)   |

> Connect these to the corresponding SPI pins on a Raspberry Pi (or other master).

## Building

A setup of the [Pico SDK](https://github.com/raspberrypi/pico-sdk) is required.

```bash
mkdir build && cd build
cmake ..
make
```

## Running

Flash the `.uf2` to the Pico. The SPI slave will start listening both CS and SCK signals, and ticking :

```
PIO SPI Slave starting...
Sent to master: 0x00
Sent to master: 0x01
...
```

Connect any SPI master (a Raspberry Pi, ..) to pilot the pico and read the responses.

## PIO Program

The SPI behavior is defined in `spi_slave.pio`, including a helper function `spi_slave_program_init()` that configures the PIO and state machine.

