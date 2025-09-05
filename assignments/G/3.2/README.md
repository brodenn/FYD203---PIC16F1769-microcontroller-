
---

## `assignments/G/3.2/README.md`

```markdown
# Uppgift 3.2 – Test av systemklocka och oscillatorlägen (PIC16F1769)

## Uppgiftsbeskrivning
Utgå från koden i 3.1 och ändra inställningarna så att du kan:
1. Skicka ut klocksignalen på RA4 och mäta den.
2. Ställa klockfrekvensen till 1 MHz.
3. Ställa klockfrekvensen till 32 MHz.
4. Försöka ställa högre än 32 MHz och se resultatet.
5. Använda en extern klockkälla på RA5 och undersöka hur långsamt PIC:en fortfarande kör.

## Förklaring
Systemklockan styr hastigheten på alla instruktioner. Instruktionstakten är alltid Fosc/4.  
Med konfigurationsbitar kan du välja intern oscillator, extern oscillator eller aktivera klockutgång på RA4.  
Målet är att praktiskt se skillnaden mellan olika klockinställningar och förstå begränsningen (max 32 MHz).

## Tekniska detaljer
- **Config-bitar:**
  - `CLKOUTEN=ON` för RA4 som klockutgång
  - `FOSC=INTOSC` eller `FOSC=EXTCLK`
  - `PLLEN=ON` för att nå 32 MHz (PLL x4)
- **OSCCON (IRCF-bitar):**
  - 16 MHz: `0x7A`
  - 1 MHz: `0x4E`
- **Mätvärden på RA4 (Fosc/4):**
  - 16 MHz → 4 MHz
  - 1 MHz → 250 kHz
  - 32 MHz → 8 MHz
  - >32 MHz → fungerar ej
- **Extern klocka:**
  - RA5 (CLKI) matas med funktionsgenerator
  - RA4 visar Fosc/4
  - Kan köras mycket långsamt (ner till Hz)

## Så kör du
1. Öppna projektet i MPLAB X (XC8). Aktivera **CLKOUTEN** i Configuration Bits.  
2. Ändra `OSCCON` enligt vald frekvens (1 MHz, 16 MHz, 32 MHz).  
3. Bygg och simulera: använd **Stopwatch** för att mäta superloop-tid.  
4. Koppla RA4 till oscilloskop och verifiera klockfrekvensen.  
5. Försök ställa högre än 32 MHz och observera resultatet.  
6. Koppla funktionsgenerator till RA5 och använd extern klocka.  

## Tips inför redovisning
- Förklara varför RA4 visar Fosc/4 och inte Fosc.  
- Visa att du kan räkna om från oscillatorfrekvens till instruktionstid.  
- Påpeka maxfrekvensen (32 MHz) enligt datablad.  
- Berätta hur du testade extern oscillator på RA5 och hur långsamt du lyckades köra.  
- Använd oscilloskopet på RA4 för att styrka mätresultat.  
