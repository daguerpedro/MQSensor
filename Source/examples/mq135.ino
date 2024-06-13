#include <MQ.h>

MQ mq135(A2, 4.7);

void setup()
{
  Serial.begin(9600);
  Serial.println("-----------------------------------------");
  Serial.println("Calculating R0... leave the sensor in clean air!");
 
  float r0 = mq135.setup(100); //Calculate 100 times.

  Serial.print("R0: ");  
  Serial.println(r0);
  Serial.println("-----------------------------------------");
}

void loop()
{
  delay(1000);
  Serial.println("\n-----------------------------------------");
  Serial.print(" V: ");  Serial.println(mq135.readVoltage());
  Serial.print(" RS: ");  Serial.println(mq135.readRS());
  Serial.print(" RS/R0: ");  Serial.println(mq135.readRSR0());  
  Serial.print(" PPM: ");  Serial.println(mq135.readPPM(1.75597943848423, -0.476716991535901));  
  Serial.println("-----------------------------------------");
}
