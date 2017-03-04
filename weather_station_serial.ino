/*
Sample data, captured on 5.2.2017:
$ rtl_433 -D -A -R 16
00010101 00000100 00100000 00001001 0111 => ALL OK!
Should be:
        Temperature:     6.60 C
        Humidity:        90 %
        Chekcsum:        0111
Let's reproduce this with Arduino.
*/

const int buttonPin = 2;
int buttonState = 0;

// Let's define data like we captured it
const uint8_t data [] = {             // coresponds to bb[i][j] in alecto.c
    B00010101, B00000100, B00100000, B00001001
};

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

// Helper funcions - copied from rtl_433 source (big thanks for new knowledge ;)
uint8_t bcd_decode8(uint8_t x) {
  return ((x & 0xF0) >> 4) * 10 + (x & 0x0F);
}

uint8_t reverse8(uint8_t x) {
  x = (x & 0xF0) >> 4 | (x & 0x0F) << 4;
  x = (x & 0xCC) >> 2 | (x & 0x33) << 2;
  x = (x & 0xAA) >> 1 | (x & 0x55) << 1;
  return x;
}

// Let's calculate humidity and temperature
uint8_t calc_humidity_temp() {
  uint8_t humidity = bcd_decode8(reverse8(data[3]));
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  int16_t temp = (int16_t) ((uint16_t) (reverse8(data[1]) >> 4) | (reverse8(data[2]) << 4));
  if ((temp & 0x800) != 0) {
    temp |= 0xf000;
  }
  Serial.print("Temperature: ");
  Serial.print(temp/10.0, 1);
  Serial.println(" C");
}

void loop() {
/*  - calculate humidity and temperature
    - calculate checksum
    - put together all bits and checksum
    - send via 433 transmiter and (fingerscrossed)
*/

buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {
  calc_humidity_temp();                // call function to calculate humidity and temperature

  uint8_t csum = 0;                    // calculate checksum
  int i;
  for (i = 0; i < 4; i++) {
    uint8_t tmp = reverse8(data[i]);
    csum += (tmp & 0xf) + ((tmp & 0xf0) >> 4);
  };
  if ((data[1] & 0x7f) == 0x6c) {
    csum = csum + 0x7;
  }
  else {
    csum = 0xf - csum;
  }
  csum = reverse8((csum & 0xf) << 4);

  // Put together the whole string and print it to Serial monitor, take care of leading "0"
  String tmp_str [5];                 // temp array of strings for each byte
  String str_to_send = "\"";          // init the final string
  for (int j = 0; j < 4; j++) {       // run through all bytes
    for (int i = 7; i >= 0; i--) {    // run through all bits of each byte
      if (bitRead(data[j], i) == 0) { // use bitRead to check every bit of it
        tmp_str[j] += "0";            // and append appropriate bit value to the final string
      }
      else {
        tmp_str[j] += "1";
      }
    }
    str_to_send += tmp_str[j];
  }

  String add_csum = "";               // init checksum

  for (int i = 3; i >= 0; i--) {      // this is only 4 bits long
    if (bitRead(csum, i) == 0) {    // again, use bitRead to verify all bits
      add_csum += "0";              // and add appropriate bit to the final string
    }
    else {
      add_csum += "1";
    }
  }
  Serial.print("Calculated checksum: ");  // print the calculated checksum to Serial monitor
  Serial.println(add_csum);
  str_to_send += add_csum;
  str_to_send += "\"";                    // add the ending "
  Serial.print("String to send: ");       // print the finished string which to Serial monitor
  Serial.println(str_to_send);
  Serial.println();
}   // end if
}   // end loop

// Just comments down here, useful data from during the testing
/*
Original string from rtl_433 (last 4 bits are checksum):
00010101 00000110 10100000 00010001 0100 => checksum OK!
00010101 01000110 10100000 01101110 1100 => checksum OK!

mySwitch.send(87659867532);
mySwitch.send("000000000001010100010001");
"000101010000011010100000000100010100" should be:
2017-02-04 16:01:02 :   AlectoV1 Temperature Sensor
    House Code:      168
    Channel:         1
    Battery:         OK
    Temperature:     8.90 C
    Humidity:        89 %
*/
