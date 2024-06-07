#include <MQ.h>

#define ANALOGRESOLUTION 5.0
#define ANALOG_BITS 10

MQ mq135(A2, 2.6, 3.6);

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  delay(1000);
  float r0 = mq135.calculateR0(100);  
  mq135.setR0(r0);
  
  float rs = mq135.readRS();
  float rsr0 = mq135.getRS_R0();
  float ppm = mq135.readPPM(9.02040638438155, 1872.09662777546, 0.347340267525612);

  Serial.print("R0 ");
  Serial.print(r0, 6);
  Serial.print(" RS ");
  Serial.print(rs, 6);
  Serial.print(" RS/R0 ");
  Serial.print(rsr0, 4);
  Serial.print(" PPM ");
  Serial.println(ppm);
}
