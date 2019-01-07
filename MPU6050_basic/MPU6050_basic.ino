#include<Wire.h>

long acclX,acclY,acclZ;
float gForceX,gForceY,gForceZ;


void setup() {
Serial.begin(9600);
Wire.begin();
setupMPU();

}

void loop() {
recordAcclRead();
printAcclData();



delay(200);
}

void setupMPU()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();
  }

void recordAcclRead(){

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  while(Wire.available()<6);
  acclX=Wire.read()<<8|Wire.read();
  acclY=Wire.read()<<8|Wire.read();
  acclZ=Wire.read()<<8|Wire.read();
  gForceX=acclX/16384.0;
  gForceY=acclY/16384.0;
  gForceZ=acclZ/16384.0;
}

void printAcclData(){
  
  Serial.println(" ");
  Serial.print("Accl(g): ");
  Serial.print("     X= ");
  Serial.print(gForceX);
  Serial.print("     Y= ");
  Serial.print(gForceY);
  Serial.print("     Z= ");
  Serial.println(gForceZ);
  
  }
