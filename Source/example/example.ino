#define ANALOGRESOLUTION 5.0
#define ANALOG_BITS 10

#include "MQ.h"

MQ mq8(A0, 10, 70);
MQ mq135(A1, 20, 3.6);


void setup()
{
  Serial.begin(9600);

  Serial.println("[MQ8] Calculating R0 in clean air...");
  float r0_8 = mq8.calculateR0(100); mq8.setR0(r0_8);
  Serial.print("[MQ8] R0: ");  Serial.println(r0_8);

  Serial.println("[MQ135] Calculating R0 in clean air...");
  float r0_135 = mq135.calculateR0(100); mq135.setR0(r0_135);
  Serial.print("[MQ8] R0: ");  Serial.println(r0_135);
}

void loop()
{
  delay(1000);

  float mq8_pow_ppm = mq8.readPPM(1083.211425083,-0.633928542243332);
  float mq135_pow_ppm = mq8.readPPM(109.695705908249, -2.69058770302719);
  
  float mq8_exp_ppm = mq8.readPPM(665.240745929716, 10458.9630009314, 0.124002119003327);
  float mq135_exp_ppm = mq8.readPPM(9.02040638438155, 1872.09662777546, 0.347340267525612);
 
  Serial.println("[MQ8] POW PPM / EXP PPM:");
  Serial.print("  ");
  Serial.print(mq8_pow_ppm, 4);
  Serial.print(" / ");
  Serial.println(mq8_exp_ppm, 4);

  Serial.println("[MQ135] POW PPM / EXP PPM:");
  Serial.print("  ");
  Serial.print(mq135_pow_ppm, 4);
  Serial.print(" / ");
  Serial.println(mq135_exp_ppm, 4);
}