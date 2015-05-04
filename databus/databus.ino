//Arduino Tutorial 1.1 - Taster

//by Scynd 2013

volatile int empf_byte = 0;
volatile int wertigkeit = 1;
volatile int bitsReceived = 0;

int ausgangPin = 3;
int eingangPin = 5;
int clockAus = 4;
unsigned long tbit = 100;

void setup() {
  Serial.begin(9600);
  pinMode(ausgangPin, OUTPUT);
  pinMode(eingangPin, INPUT);
  pinMode(clockAus, OUTPUT);
  attachInterrupt(0, read, RISING);
}

void loop(){
  char value[1];
  while(Serial.available()){
    Serial.readBytes(value, 1);
    send(value[0]);
  }
}

void send(byte wert){
  
  int n = 8;
  
  Serial.print("Senden: ");
  Serial.println((char)wert);
  
  for(int i=0; i<n; i++){
    //Serial.print("Senden: ");
    //Serial.println((wert & (1 << i)) != 0);
    digitalWrite(ausgangPin,(wert & (1 << i)) != 0);
    delay(tbit/2);
    digitalWrite(clockAus,HIGH);
    delay(tbit/2);
    digitalWrite(ausgangPin, LOW);
    digitalWrite(clockAus, LOW);
  }
}

void read(){
  empf_byte = empf_byte + wertigkeit * digitalRead(5);
  wertigkeit = 2*wertigkeit;
  
  bitsReceived++;

  if(bitsReceived == 8){
    Serial.print("Empfangen: ");
    Serial.println((char)empf_byte);
    bitsReceived = 0;
    empf_byte = 0;
    wertigkeit = 1;
  }
}
