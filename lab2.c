#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"

#define UART_ID uart1   // Use uart1
#define BAUD_RATE 115200
#define TX_PIN 8    // Transmit on pin 8
#define RX_PIN 9    // Receive on pin 9

const uint BTN_PIN = 22;

int main() {
    // Initialise the standard stuff
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_set_pulls(BTN_PIN, true, false);
    gpio_set_function(TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    
    int a = 64; // Literally define the letter 'A' in ASCII
    char charData; // Define a variable to store incoming data

    // Infinite loop
    while (true) {
        if(gpio_get(BTN_PIN))
        {
            // If never press button then we send a string of 1s
            uart_putc(UART_ID, '1');
            sleep_ms(1000);
        } else{

            // If press button then we send a string of uppercase alphabets
            a+=1;
            if (a > 90) {
                a = 65;
            }
            char sendingAlphabet = a;
            uart_putc(UART_ID, sendingAlphabet);
            sleep_ms(1000);
        }

        if(uart_is_readable(UART_ID)){
            // Fetch the data from the bus
            charData = uart_getc(UART_ID);
            // If they send 1 then we print 2
            if (charData == '1') {
                printf("%c", '2');
            }
            // If they send alphabet then we print in lowercase
            else {
                printf("%c", tolower(charData));
            }
        }
    }
}
