

#include <IRremote.h>

unsigned long button = 0;
const int relayPin = 3;
const int relayPin2 = 4;

//le o infravermelho e deolvove o valor HEX
unsigned long readInfrared() {
  unsigned long code = 0;
  // Check if we've received a new code
  if (IrReceiver.decode()) {
    // Get the infrared code
    code = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();
  }
  return code;
}



//Controla o movimento da curtina. Mantendo o relay aberto ate receber novamente o mesmo input que ativou o sinal, impede que ambos relays estajam ativos
void verticalControl(unsigned long state) {
  if (state == 0xE619FF00) {
    if (digitalRead(relayPin) == HIGH) {
      digitalWrite(relayPin2, HIGH);
      delay(25);
      digitalWrite(relayPin, LOW);
    } else
      digitalWrite(relayPin, HIGH);
  } else if (state == 0xF20DFF00) {
    if (digitalRead(relayPin2) == HIGH) {
      digitalWrite(relayPin, HIGH);
      delay(25);
      digitalWrite(relayPin2, LOW);
    } else
      digitalWrite(relayPin2, HIGH);
  }
}



//O relay esta fechado em HIGH e aberto em LOW
void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  digitalWrite(relayPin, HIGH);
  digitalWrite(relayPin2, HIGH);
  IrReceiver.begin(2);
}

void loop() {
  button = readInfrared();
  //Serial.println(button, HEX);
  verticalControl(button);

  delay(25);  // Delay a little bit to improve simulation performance
}