#include <avr/interrupt.h>
#include <avr/io.h>
volatile int event = 0;
volatile unsigned long time;
volatile unsigned long startTime;

void setup() { //Initialisierungen
  Serial.begin(9600);    //Baudrate für serielle Kommunikation.
  //ACSR = 3;  //Analog Comperator fallende Flanke, externe Referenzspannung auf Pin D6
  // ACSR = 2; //Analog Comperator steigendee Flanke, externe Referenzspannung auf Pin D6
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(3000);
  digitalWrite(13, HIGH);
  startTime = micros();
  bitSet(ACSR, 2);    //Interrupt für Comparator freigeben
}
void loop() {
  Serial.println(time);
  //bitClear(ACSR, 3);  //Comparator Interrupt sperren
}


ISR(ANALOG_COMP_vect ) {   //Analog Comperator Interrupt
  event = 1;
  time = micros() - startTime;
}


