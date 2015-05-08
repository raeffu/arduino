volatile int empf_byte = 0;
volatile int wertigkeit = 1;
volatile int bitsEmpf = 0;

long input;
int counter = 0;

int ausgangPin = 3;
int eingangPin = 5;
int clockAus = 4;
unsigned int tbit = 20;

void setup() {
  Serial.begin(9600);
  pinMode(ausgangPin, OUTPUT);
  pinMode(eingangPin, INPUT);
  pinMode(clockAus, OUTPUT);
  attachInterrupt(0, read, RISING);
}

void loop(){
  
  if(tbit > 500){
    return;
  }
  
  for(int i=0;i<1000;i++){
    input = random(256);
    send(input);
  }
  
  Serial.print("Bitzeit: ");
  Serial.println(tbit);
  Serial.print("counter: ");
  Serial.println(counter);
  
  counter = 0;
  tbit += 20;
  
}

void send(byte wert){
  
  int n = 8;
  
  for(int i=0; i<n; i++){
    digitalWrite(ausgangPin,(wert & (1 << i)) != 0);
    delayMicroseconds(tbit/2);
    digitalWrite(clockAus,HIGH);
    delayMicroseconds(tbit/2);
    digitalWrite(ausgangPin, LOW);
    digitalWrite(clockAus, LOW);
  }
}

void read(){
  empf_byte = empf_byte + wertigkeit * digitalRead(5);
  wertigkeit = 2*wertigkeit;
  
  bitsEmpf++;

  if(bitsEmpf == 8){
    //Serial.print("Empfangen: ");
    //Serial.println((char)empf_byte);
    
    if(input != empf_byte){
      counter++;
    }
    
    bitsEmpf = 0;
    empf_byte = 0;
    wertigkeit = 1;
  }
}

