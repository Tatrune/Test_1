
// USARTs Example

#include <stdint.h>
#include <avr/io.h>

// Define baud rate
#define USART0_BAUD         115200ul
#define USART0_UBBR_VALUE   ((F_CPU/(USART0_BAUD<<4))-1)

void USART0_vInit(void)
{
    // Set baud rate
    UBRR0H = (uint8_t)(USART0_UBBR_VALUE>>8);
    UBRR0L = (uint8_t)USART0_UBBR_VALUE;

    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C = (0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);

    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN)|(1<<TXEN);   
}

void USART0_vSendByte(uint8_t u8Data)
{
    // Wait if a byte is being transmitted
    while((UCSR0A&(1<<UDRE0)) == 0) // 
    {
        ;
    }

    // Transmit data
    UDR0 = u8Data; 
}

uint8_t USART0_vReceiveByte()
{
    // Wait until a byte has been received
    while((UCSR0A&(1<<RXC0)) == 0)
    {
        ;
    }

    // Return received data
    return UDR0;
}

int main(void)
{
    uint8_t u8Data;

    // Initialise USART
    USART0_vInit();

    // Send string
    USART0_vSendByte('A');
    USART0_vSendByte('V');
    USART0_vSendByte('R');
    USART0_vSendByte('\r');
    USART0_vSendByte('\n');

    // Repeat indefinitely
    for(;;)
    {
        // Echo received characters
        u8Data = USART0_vReceiveByte();
        USART0_vSendByte(u8Data);
    }
}
