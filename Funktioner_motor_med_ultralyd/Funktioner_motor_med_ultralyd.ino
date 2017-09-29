  
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

int skyd = 2;

void skydFunktion(){
      digitalWrite(skyd, HIGH);
      delay(150);
      digitalWrite(skyd, LOW);
      }

void frem(){
  analogWrite(hastighedVenstre, 255); 
  analogWrite(hastighedHoejre, 255);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW);
  
}

void tilbage(){
  analogWrite(hastighedVenstre, 255); 
  analogWrite(hastighedHoejre, 255);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH);
}

void venstreFrem(){
  analogWrite(hastighedVenstre, 130); 
  analogWrite(hastighedHoejre, 170);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW); 
}

void hoejreFrem(){
  analogWrite(hastighedVenstre, 170); 
  analogWrite(hastighedHoejre, 130);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
}

void hoejreTilbage(){
  analogWrite(hastighedVenstre, 130); 
  analogWrite(hastighedHoejre, 170);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  }

void venstreTilbage(){
  analogWrite(hastighedVenstre, 170); 
  analogWrite(hastighedHoejre, 130);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, HIGH);
  digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, HIGH); 
}

void hoejreSkarp(){
  analogWrite(hastighedVenstre, 255); 
  analogWrite(hastighedHoejre, 0);
   digitalWrite(retningHoejreEt, LOW);
  digitalWrite(retningHoejreTo, LOW);
  digitalWrite(retningVenstreEt, HIGH);
  digitalWrite(retningVenstreTo, LOW);
}

void venstreSkarp(){
  analogWrite(hastighedHoejre, 255);
  analogWrite(hastighedVenstre, 0);
  digitalWrite(retningVenstreEt, LOW);
  digitalWrite(retningVenstreTo, LOW);
  digitalWrite(retningHoejreEt, HIGH);
  digitalWrite(retningHoejreTo, LOW); 
}

void hastighedStop(){
  analogWrite(hastighedVenstre, 0); 
  analogWrite(hastighedHoejre, 0);
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

      else if(besked=='o'){
      skydFunktion();
  }
    else if(besked=='s'){
      hastighedStop();
  }     
    bluetooth.print(besked);
  }
}

void setup() {
    pinMode(skyd, OUTPUT);
    
  pinMode(retningVenstreEt, OUTPUT);
  pinMode(retningVenstreTo, OUTPUT);
  pinMode(retningHoejreEt, OUTPUT);
  pinMode(retningHoejreTo, OUTPUT);
  pinMode(hastighedVenstre, OUTPUT);
  pinMode(hastighedHoejre, OUTPUT);

  bluetooth.begin(115200);
  Serial.begin(9600);

}

void loop() {

  bluetooth.listen();
  inputBluetooth();
  delay(60);
}


