#include<Wire.h>

long acclX,acclY,acclZ;
float gForceX,gForceY,gForceZ;

long gyroX,gyroY,gyroZ;
float rotX,rotY,rotZ;

void setup() {
Serial.begin(9600);
Wire.begin();
setupMPU();

}

void loop() {
//recordAcclRead();
//printAcclData();

recordGyroRead();
printGyroData();

delay(200);
}

void setupMPU()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); //Power management
  Wire.write(0b00000000);
  Wire.endTransmission();
  
  Wire.beginTransmission(0x68);
  Wire.write(0x1C); //Accelerometer configuration
  Wire.write(0b00000000);
  Wire.endTransmission();

  Wire.beginTransmission(0x68);
  Wire.write(0x1B); //Gyroscopr config
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

void recordGyroRead(){

 Wire.beginTransmission(0x68);
 Wire.write(0x43);
 Wire.endTransmission();
 Wire.requestFrom(0x68,6);
 while(Wire.available()<6);
  gyroX=Wire.read()<<8|Wire.read();
  gyroY=Wire.read()<<8|Wire.read();
  gyroZ=Wire.read()<<8|Wire.read();
  rotX=gyroX/131.0;
  rotY=gyroY/131.0;
  rotZ=gyroZ/131.0;

}

void printGyroData(){

  Serial.println("  ");
  Serial.print("Angular velocity d/sec     ");
  Serial.print("   X= ");
  Serial.print(rotX);
  Serial.print("     Y= ");
  Serial.print(rotY);
  Serial.print("    Z= ");
  Serial.print(rotZ);
}
