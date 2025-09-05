# Uppgift 3.1 – 2-ingångars AND-grind (PIC16F1769)

## Uppgiftsbeskrivning
Skriv ett program som gör att LED på RB6 tänds endast när både RB4 och RB5 är höga. Testa först i simulatorn och sedan på breadboard.

## Förklaring
Detta är den första laborationen där du lär dig grunderna i att programmera en mikrokontroller i C.  
Du måste konfigurera portar, ställa dem som in- eller utgångar och använda logiska operatorer för att styra LED:n.  
En AND-funktion betyder att LED bara lyser när båda ingångarna är 1.

## Tekniska detaljer
- **Config-bitar:**
  - Oscillator: INTOSC, 16 MHz
  - Watchdog Timer: OFF
  - MCLRE: ON
- **Register:**
  - `OSCCON` – väljer klockfrekvens (16 MHz, instruktionstakt = Fosc/4 = 4 MHz)
  - `ANSELB` – stänger av analog funktion på B-portar
  - `TRISB` – riktning: RB4/RB5 = ingångar, RB6 = utgång
  - `PORTB` – läs ingångar
  - `LATB` – skriv utgång
- **Logik i loopen:**
```c
LATBbits.LATB6 = (PORTBbits.RB4 && PORTBbits.RB5);
