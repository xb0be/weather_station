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

Let's send our string:
11100101 00000011 10100000 00100001 1000
which means:
  House Code:      167
  Channel:         1
  Battery:         OK
  Temperature:     9.20 C
  Humidity:        84 %
*/

unsigned long RFcode = 0B11100101000000111010000000100001;
unsigned long csum = 0B1000;

// timings measured from captured signal in Audacity
#define SYNC_TIME 9000
#define DATA_HIGH 500
#define DATA_LOW_0 2000 
#define DATA_LOW_1 4000 
#define WAIT 8800
const int buttonPin = 2;                // button to begin sending signal
int buttonState = 0;

void setup() {
  pinMode(3, OUTPUT);                   // pin 3 will be our RF transmit pin
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void send_sync() {
  PORTD = PORTD | B00001000;            // D3 high - send SYNC signal
  delayMicroseconds(DATA_HIGH);
  PORTD = PORTD & B11110111;            // D3 low
  delayMicroseconds(SYNC_TIME);
}

void send_data(unsigned long code) {
    for (int i=0; i<32; i++) {          //send all 32 bits
      PORTD = PORTD | B00001000;        // D3 high
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111;        // D3 low
      if (code & 0x80000000) {          // get the current bit by masking all but the MSB
        delayMicroseconds(DATA_LOW_1);  // if it is "1", we should wait DATA_LOW_1
      }
      else {
        delayMicroseconds(DATA_LOW_0);  // if it is "0", we should wait DATA_LOW_0
      }
      code = code << 1;                 //shift to the next bit
    }                                   // end for
}                                       // end proc

void send_csum(unsigned long c){
  for (int j=0; j<4; j++) {             //send all 4 bits + "0" at the end
    PORTD = PORTD | B00001000;          // D3 high - "1"
    delayMicroseconds(DATA_HIGH);
    PORTD = PORTD & B11110111;          // D3 low
    if (c & 0x8) {                      //get the current bit by masking all but the MSB
      delayMicroseconds(DATA_LOW_1);
    }
    else {
      delayMicroseconds(DATA_LOW_0);
    }
    c = c << 1;                        //shift to the next bit
  }                                    // end for
}                                      // end proc

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    //noInterrupts();
    delay(300);
    send_sync();                       // send SYNC
    for (int k = 0; k<8; k++) {        // send DATA and delay between them 8 times
      send_data(RFcode);
      send_csum(csum);                 // send checksum
      PORTD = PORTD | B00001000;       // Additional "0" at the end
      delayMicroseconds(DATA_HIGH);
      PORTD = PORTD & B11110111;
      delayMicroseconds(WAIT);         // send delay between two bursts
    }
  }                                    // end if
}                                      // end loop

