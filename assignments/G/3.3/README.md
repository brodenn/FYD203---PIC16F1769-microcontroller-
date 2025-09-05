# Uppgift 3.3 – 2-ingångars OR-grind (PIC16F1769)

## Uppgiftsbeskrivning
Ändra koden från uppgift 3.1 så att LED på RB6 lyser när minst en av ingångarna RB4 eller RB5 är hög.  
Verifiera i simulatorn och testa sedan på breadboard.

## Förklaring
En OR-grind betyder att LED tänds om någon av ingångarna är 1.  
I C används operatorn `||` för logiskt OR. Bitvis OR `|` fungerar också, men här används logiska operatorer.

Programflöde:
1. Initiera klockan (16 MHz).
2. Konfigurera RB4/RB5 som ingångar, RB6 som utgång.
3. I loopen: läs RB4/RB5, beräkna OR och skriv till RB6.

## Tekniska detaljer
- **Config-bitar:**
  - Oscillator: INTOSC, 16 MHz
  - Watchdog Timer: OFF
  - MCLRE: ON
- **Register:**
  - `ANSELB` – digitala portar
  - `TRISB` – riktning
  - `PORTB` – läsa ingångar
  - `LATB` – skriva utgång
- **Logik i loopen:**
```c
LATBbits.LATB6 = (PORTBbits.RB4 || PORTBbits.RB5);
