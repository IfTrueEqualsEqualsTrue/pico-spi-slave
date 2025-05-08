#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "spi_slave.pio.h"
#include <stdio.h>

#define CS_PIN   0
#define SCK_PIN  1
#define MISO_PIN 2

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("PIO SPI Slave starting...\n");

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &spi_slave_program);
    uint sm = pio_claim_unused_sm(pio, true);

    spi_slave_program_init(pio, sm, offset, CS_PIN, SCK_PIN, MISO_PIN);

    uint8_t counter = 0;
    while (true) {
        while (pio_sm_is_tx_fifo_full(pio, sm))
            tight_loop_contents();

        pio_sm_put_blocking(pio, sm, (uint32_t)(counter++) << 24);
        printf("Sent to master: 0x%02X\n", counter);
    }
}
