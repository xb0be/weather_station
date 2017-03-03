/*
Little weather station prank.

Objectives of this amusing project were:
- capture remote weather station sensor signal on 433 MHz
- decode it
- reproduce it and send it to weather station via Arduino
- make father wondering how come there's always 9.2 degrees
- Celsius and 84% humidity outside ;)

Used tools:
- RTL-SDR USB dongle
- gqrx
- rtl_433 (great tool!)
- Audacity
- Arduino with 433 MHz transmiter

*/

// timings measured from captured signal in Audacity
#define SYNC_TIME 9000
#define DATA_HIGH 500
#define DATA_LOW_0 2000
#define DATA_LOW_1 4000
#define WAIT 8800
const int buttonPin = 2;  // button to begin sending signal
int buttonState = 0;

void setup() {
  pinMode(3, OUTPUT);     // pin 3 will be our RF transmit pin
  pinMode(buttonPin, INPUT);
}
  
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    /*
     Let's send our string:
     11100101 00000011 10100000 00100001 1000
     which means:
       House Code:      167
       Channel:         1
       Battery:         OK
       Temperature:     9.20 C
       Humidity:        84 %
    */ 
    noInterrupts();
    
    PORTD = PORTD | B00001000; // D3 high - send SYNC signal
    delayMicroseconds(DATA_HIGH);
    PORTD = PORTD & B11110111; // D3 low
    delayMicroseconds(SYNC_TIME);
  
    for (int k = 0; k<8; k++) {  // send DATA and delay betwee them 8 times
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
    
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
    
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
    
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
  
      PORTD = PORTD | B00001000; // D3 high - "1"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_1);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      delayMicroseconds(DATA_LOW_0);
      PORTD = PORTD | B00001000; // D3 high - "0"
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111; // D3 low
      
      delayMicroseconds(WAIT);   // send delay between two bursts
    }     // end for
  }       // end if
}         // end loop

