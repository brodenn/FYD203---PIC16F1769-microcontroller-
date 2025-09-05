// === KLIStra IN auto-genererade CONFIG-BITS här (via MPLAB X: Configuration Bits) ===
// (Se Appendix A: Generate Source Code to Output och klistra överst i denna fil.)  

#include <xc.h>

// Valfritt (behövs bara om du använder __delay_ms/us()):
#define _XTAL_FREQ 16000000UL

// ------------------------ KLOCKA & PORTAR ------------------------

static void clock_init(void) {
    // Intern oscillator 16 MHz:
    // OSCCON: SCS=10 (Internal oscillator), IRCF=1111 (16 MHz) => 0x7A  
    OSCCON = 0x7A;
    // Instruktionshastigheten är Fosc/4 (dvs 4 MHz vid Fosc=16 MHz). 
}

static void ports_init(void) {
    // Port B som digital: stäng av analoga funktioner för B[7:4], inklusive RB6 (LED)  
    ANSELBbits.ANSB4 = 0;
    ANSELBbits.ANSB5 = 0;
    ANSELBbits.ANSB6 = 0;
    ANSELBbits.ANSB7 = 0;

    // Riktning: RB4, RB5, RB7 = ingångar (1), RB6 = utgång (0)  
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB6 = 0;

    LATBbits.LATB6 = 0; // LED av initialt
}

// ------------------------ LOGIK 3.5 ------------------------
// Tabell 3.3 (A,B,C -> Out) enligt kursboken.  
//  A B C | Out
//  0 0 0 | 1
//  0 0 1 | 0
//  0 1 0 | 0
//  0 1 1 | 1
//  1 0 0 | 0
//  1 0 1 | 1
//  1 1 0 | 1
//  1 1 1 | 0
//
// Konstant-tids-lösning med look-up table (LUT) där index = (A<<2)|(B<<1)|C
// Ordning: index 0..7 motsvarar raderna ovan i binär ordning.
static const unsigned char LUT_ABC_to_Out[8] = {
    /*000*/ 1,
    /*001*/ 0,
    /*010*/ 0,
    /*011*/ 1,
    /*100*/ 0,
    /*101*/ 1,
    /*110*/ 1,
    /*111*/ 0
};

int main(void) {
    clock_init();
    ports_init();

    while (1) {
        // Läs in A, B, C från RB4, RB5, RB7
        unsigned char A = PORTBbits.RB4;   // bitvärden 0/1
        unsigned char B = PORTBbits.RB5;
        unsigned char C = PORTBbits.RB7;

        // Bilda index i [0..7] utan villkor (konstant exekveringstid)
        unsigned char idx = (A << 2) | (B << 1) | (C << 0);

        // Slå upp resultatet och skriv till LED på RB6
        LATBbits.LATB6 = LUT_ABC_to_Out[idx];

        // (Valfritt) – ingen delay här: superloopen går “så snabbt det går”.
        // Använd MPLAB X Stopwatch för att mäta loop-tid. 
    }
}
