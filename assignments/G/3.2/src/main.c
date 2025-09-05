#include <xc.h>

// === Klistra in de auto-genererade #pragma config-raderna här ===

// 16 MHz intern klocka (OSCCON enligt bokens tabell)
static void clock_init(void) {
    // SCS=10 (Internal oscillator), IRCF=1111 (16 MHz), SPLLEN=0 här
    OSCCON = 0x7A;  // 0b01111010
    // Fosc = 16 MHz, instruktionshastighet = Fosc/4 = 4 MHz (1 cykel = 250 ns). 
}

static void ports_init(void) {
    // Ställ PORTB pins till digitala: ANSELB bitar 4,5,6 = 0 (digital) 
    ANSELBbits.ANSB4 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELBbits.ANSB6 = 0;

    // TRISB: RB4, RB5 = input (1), RB6 = output (0) 
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 0;

    // Startvärde på LED-pinnen (RB6) = av
    LATBbits.LATB6 = 0;
}

int main(void) {
    clock_init();
    ports_init();

    // Superloop (måste finnas enligt kursboken) 
    while (1) {
        // AND-grind: LED på RB6 tänds endast om RB4=1 OCH RB5=1
        // (PORTBbits.RB4/RB5 är bitar → && eller & spelar ingen roll här, men && är semantiskt logiskt AND) 
        LATBbits.LATB6 = (PORTBbits.RB4 && PORTBbits.RB5);
    }
}
