#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int data[2];
RF24 radio(9, 10); // CE, CSN
const byte address[10] = "selo";
bool sinyal[1];
int durum = 0;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(0, address);
  radio.startListening();
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT); // ON FAR

}

void loop() {

  if (radio.available()) {
    int x = data[0];
    int y = data[1];
    radio.read(data, sizeof(data));
    //data[0] gaz fren
    //data[1] sağ sol
    Serial.println(data[0]);
    Serial.println(data[1]);
    if (data[0] >= 470 && data[0] <= 520) {
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      analogWrite(A1, 0);
      analogWrite(A0, 0);
      digitalWrite(3, LOW);
    }
    if (data[1] >= 500 && data[1] <= 600) {
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      analogWrite(A1, 0);
      analogWrite(A0, 0);
      digitalWrite(3, LOW);
    }
    if (data[0] < 470) {
      int pwm = map(data[0], 480, 427, 150, 255);
      analogWrite(5, pwm);
      analogWrite(6, pwm);
      digitalWrite(3, HIGH);
      analogWrite(A1, 255);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
    }
    if (data[0] > 520) {
      int pwm = map(data[0], 500, 590, 150, 255);
      analogWrite(5, pwm);
      analogWrite(6, pwm);
      analogWrite(A0, 255);
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
    }
    if (data[1] < 500) {
      int pwm = map(data[1], 500, 0, 150, 255);
      analogWrite(5, pwm);
      analogWrite(6, pwm);
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
    }
    if (data[1] > 600) {
      int pwm = map(data[1], 600, 1023, 150, 255);
      analogWrite(5, pwm);
      analogWrite(6, pwm);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
    }
  }
}
