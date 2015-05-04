//Arduino Tutorial 1.1 - Taster

//by Scynd 2013

volatile int i=0;

int status = 0;
int zeit = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, blink, RISING) ;
}

void loop(){
if (zeit != 0 && zeit-millis() > 500){
 
//    delay(500);
   noInterrupts();
   Serial.println(i);
   i = 0;
   zeit = 0;
   }
   interrupts();

}

void blink(){
 if (zeit == 0){
     zeit = millis();
   }
   i = i+1;
   
}
