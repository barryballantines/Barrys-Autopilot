//**************************************************************//
// Hardware test for Shift-Register and 7-Segment Display
// Based on "shiftOutCode, Hello World"
// By  Carlyn Maw,Tom Igoe, David A. Mellis 
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
int oePin = 9;
int srClearPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(srClearPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // clear register and activate output...
  digitalWrite(srClearPin, LOW);
  digitalWrite(srClearPin, HIGH);
  digitalWrite(oePin, LOW);
  
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  byte numbers[] = { 
    B11111100, // 0
    B01100000, // 1
    B11011010, // 2
    B11110010, // 3
    B01100110, // 4
    B10110110, // 5
    B10111110, // 6
    B11100000, // 7
    B11111110, // 8
    B11110110, // 9 
  };
  for (int i = 9; i >= 0; i--) {
    
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[i]);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(1000);
  }
}
