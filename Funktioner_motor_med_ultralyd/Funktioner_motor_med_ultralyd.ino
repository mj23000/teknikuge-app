  
#include <SoftwareSerial.h>
int bluetoothTx = 9;
int bluetoothRx = 10;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char besked;

int retningVenstreEt = 8;
int retningVenstreTo = 7;
int retningHoejreEt = 3;
int retningHoejreTo = 4;
int hastighedVenstre = 6;
int hastighedHoejre= 5;

int forlygte = A0;
int baglygte = A1;
int dytDyt = A3;

int afstandLED = 13;
const long trigger = A5;
const long echo = A4;
long centimeter = 0;

void hastighedStop(){
  analogWrite(hastighedVenstre, 0); 
  analogWrite(hastighedHoejre, 0);
}

void frem(){
  analogWrite(hastighedVenstre, 255); 
  analogWrite(hastighedHoejre, 255);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW);
  digitalWrite(baglygte, LOW);
  digitalWrite(forlygte, HIGH);
  
}

void tilbage(){
  analogWrite(hastighedVenstre, 255); 
  analogWrite(hastighedHoejre, 255);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH);
  digitalWrite(baglygte, HIGH);
  digitalWrite(forlygte, LOW);
}

void venstreFrem(){
  analogWrite(hastighedVenstre, 170); 
  analogWrite(hastighedHoejre, 130);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW); 
  digitalWrite(baglygte, LOW);
  digitalWrite(forlygte, HIGH);
}

void hoejreFrem(){
  analogWrite(hastighedVenstre, 130); 
  analogWrite(hastighedHoejre, 170);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(baglygte, LOW);
  digitalWrite(forlygte, HIGH);
}

void hoejreTilbage(){
  analogWrite(hastighedVenstre, 170); 
  analogWrite(hastighedHoejre, 130);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  digitalWrite(baglygte, HIGH);
  digitalWrite(forlygte, LOW);
  }

void venstreTilbage(){
  analogWrite(hastighedVenstre, 130); 
  analogWrite(hastighedHoejre, 170);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH); 
  digitalWrite(baglygte, HIGH);
  digitalWrite(forlygte, LOW);
}

void hoejreSkarp(){
  analogWrite(hastighedVenstre, 0); 
  analogWrite(hastighedHoejre, 255);
   digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(baglygte, LOW);
  digitalWrite(forlygte, HIGH);
}

void venstreSkarp(){
  analogWrite(hastighedHoejre, 0);
  analogWrite(hastighedVenstre, 255);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, LOW); 
  digitalWrite(baglygte, LOW);
  digitalWrite(forlygte, HIGH);
}

void inputBluetooth(){
  char besked;
  if(bluetooth.available()){ 
    besked=(char)bluetooth.read(); 
    if(besked=='f'){
      frem();
    }
    else if(besked=='v'){
      venstreFrem();
    }
    else if(besked=='t'){
      tilbage();
    }
    else if(besked=='h'){
      hoejreFrem();
    }
     else if(besked=='k'){
      venstreTilbage();
    }
     else if(besked=='d'){
      hoejreTilbage();
    }
    else if (besked=='y'){
      venstreSkarp();
    }
    else if (besked=='x'){
      hoejreSkarp();
    }
    else if(besked=='a'){
      tilbage();
      delay(200);
      hastighedStop();
    }
    else if (besked=='l'){
      digitalWrite(forlygte, HIGH);
      digitalWrite(baglygte, HIGH);
    }
    else if (besked=='n'){
      digitalWrite(forlygte, LOW);
      digitalWrite(baglygte, LOW);
    }
    else if (besked=='b'){
      analogWrite(dytDyt, 128);
      delay(80);
      analogWrite(dytDyt, 0);
      delay(80);
      analogWrite(dytDyt, 128);
      delay(80);
      analogWrite(dytDyt, 0);
    } 
    else if(besked=='s'){
      hastighedStop();
  }     
    bluetooth.print(besked);
  }
}

void setup() {
  pinMode(retningVenstreEt, OUTPUT);
  pinMode(retningVenstreTo, OUTPUT);
  pinMode(retningHoejreEt, OUTPUT);
  pinMode(retningHoejreTo, OUTPUT);
  pinMode(hastighedVenstre, OUTPUT);
  pinMode(hastighedHoejre, OUTPUT);
  
  pinMode(forlygte, OUTPUT);
  pinMode(baglygte, OUTPUT);  
  pinMode(dytDyt, OUTPUT);
  
  pinMode(afstandLED, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
 
  bluetooth.begin(115200);
  Serial.begin(9600);

}

void loop() {

  bluetooth.listen();
  inputBluetooth();
  bluetooth.println(centimeter);
  delay(60);

  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds( 10);
  digitalWrite(trigger, LOW);

centimeter = pulseIn(echo, HIGH);

centimeter = centimeter/58;

  Serial.println(" centimeter");
  Serial.print(centimeter);

  if (centimeter<=30){
   hastighedStop();
   delay(10);
    }
    
  if (centimeter>=400){
    centimeter = Serial.print("\n Fejl \n");
}

}


