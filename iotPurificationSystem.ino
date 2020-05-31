#include <dht.h>
#include <MiCS.h>
#include <MQ7.h>
#include <MQ3.h>

int in1 = 9;
int in2 = 6;

int chk;
dht DHT;

float MICS;
MiCS gasSensor = MiCS5524(A3);

int pin = A0;
MQ3 mq3(pin);

float ppm;
MQ7 mq7(A1, 5.0);

void setup() {
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  Serial.begin(9600);
  mq3.begin();
}

void TurnMotor(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
}

void TurnOFF(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
}

void loop() {

  //MQ-7
  MQ7 = analogRead(A1);
  ppm = mq7.getPPM();
  Serial.print(" MQ7 = ");
  Serial.println(ppm,1);
    
  //MICS
  MICS = gasSensor.getPPM();
  Serial.print(" MICS = ");
  Serial.println(MICS,1);
  
  //MQ-3
  float lpg = mq3.readLPG();
  float smoke = mq3.readSmoke();
  Serial.print(" lpg = ");
  Serial.print(lpg,1);
  Serial.print(" Smoke = ");
  Serial.println(smoke,1);
  
  //DHT11
  chk = DHT.read11(DHT11_PIN);
  if(DHT.temperature > -500)
  {
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
  }
  
  if(DHT.humidity > -500)
  {
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
  }
  delay(1000);
  if( DHT.temperature > 40 || DHT.humidity > 0.4 || MQ-7 > 0 || lpg > 0 || smoke > 0 || MICS > 1 ){
    TurnMotor();
  }
  else {
    TurnOFF();
  }
}
