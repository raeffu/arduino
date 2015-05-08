volatile byte receiveByte = 0;
volatile int valence = 1;
volatile int bitsReceived = 0;
int bitRate = 14;
int fullCycle = (1 / bitRate) * 1000;
int halfCycle = fullCycle * .5;

int outputDataPin = 3;
int outputClockPin = 4;
int inputDataPin = 5;

void setup() {
 pinMode(outputDataPin, OUTPUT);
 pinMode(outputClockPin, OUTPUT);
 Serial.begin(9600);
 attachInterrupt(0, read, RISING); // interrupting on clock input
}

void loop() {
 byte value[1];
 while(Serial.available()){
   Serial.readBytes(value, 1);
   send(value[0]);
 }
}

void send(byte value){
 for(int i = 0; i < 8; i++){
   digitalWrite(outputDataPin, (value & (1 << i)) != 0);

   delay(halfCycle);
   digitalWrite(outputClockPin, HIGH);
   delay(halfCycle);
   digitalWrite(outputClockPin, LOW);
 }
}

void read(){
 receiveByte += valence * digitalRead(inputDataPin); // reading from data input
 valence *= 2;
 bitsReceived++;

 if(bitsReceived == 8){
   Serial.println((char)receiveByte);
   bitsReceived = 0;
   receiveByte = 0;
   valence = 1;
 }
}
