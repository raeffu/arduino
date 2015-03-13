// Primitives Menu für den Arduino uno. Jeder Befehl startet mit einem $ zeichen. 
// Es kann (muss aber nicht) ein Argument übergeben werden
// Aufrufsbeispiel:    $1 50 
// Führe den Befehl 1 aus und übergebe das Argument 50
// Die Baudrate im Serial Monitor (oder was immer der Kommunikationspartner ist) muss übereinstimmen
// mit dem Wert der Initialisierung, hier 9600.
// Dezember 2014, BHG1
int Command;              //Befehlsnummer
unsigned int Argument;    //Argument (zur Zeit nur bei Befehl 2)
void setup() { //Initialisierungen
  Serial.begin(9600);    //Baudrate für serielle Kommunikation.
}

void loop() {  //Main
  if (Serial.available() > 0) {
    Command = get_command(); //Pollen auf Befehl von Schnittstelle
    if (Command == 1) //Befehl 1
    {
      Serial.print("Befehl 1: Funktionsaufruf  mit Argument = ");
      Serial.println(Argument);
      Serial.print("tu_was(Argument) = ");
      Serial.println(tu_was(Argument));
    }
    if (Command == 2) // Befehl 2
    {
      Serial.println("Befehl 2: Ohne Funktion, ohne Argument ");
      Serial.println("Auch ich tue was");
    }
  }
}

int tu_was(int nix) { //Funktion
  return nix + 1;
}


int get_command() {
  //wartet bis auf Schnittstelle ein Befehl erkannt wurde. Ein Befehl beginnt mit $ dann einer Zahl und allenfalls einem Argument
  //Beispiel $1 (ohne Argument)
  //Beispiel $2 56     (mit Argument)
  char serialdata[20];
  int AnzahlChar;
  int j;
  unsigned int Wertigkeit = 1;
  int Command_ = 0;
  AnzahlChar = Serial.readBytesUntil('\n',  serialdata, 20 );
  if (serialdata[0] == '$' && AnzahlChar > 1)
  {
    Command_ = (serialdata[1]) - 48;
  }
  //Wandelt Characters des Arguments in eine Zahl um (das könnte man sicher "schöner programmieren")
  Argument = 0;
  Wertigkeit = 1;   //Wertigkeit der Ziffer, d.h. 1 -> 10 -> 100 ..
  for (j = AnzahlChar - 1; j >= 3; j--) {
    Argument = Argument + Wertigkeit * (serialdata[j] - 48);
    Wertigkeit = 10 * Wertigkeit;
  }
  return Command_;
}



