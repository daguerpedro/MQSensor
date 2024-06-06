#include <Arduino.h>
#line 1 "D:\\code\\MQSensor\\Arduino\\test\\test.ino"
#include "..\MQ.h"

#define ANALOG_PORT A2

#define RATIO_CLEAN_AIR 3.6 //EXTRACTED FROM DATASHEET
#define RL 20 //KOhm, TRIMPOT VALUE

#define DEBUG false
#define CASES 5

double getSensorVolt()
{
  return (double)(5.0*analogRead(ANALOG_PORT))/1023.0;
}

double getCorrecterResistence(float temp)
{
  return getResistence()/ (1.26432097540018-0.022915494713572*temp+0.000301801953068772*pow(temp, 2));
}
double getResistence()
{
  //  RS = [(VC x RL) / VRL] - RL
  return ((5.0*RL)/getSensorVolt())-RL;
}

double getCorrectedR0(float temp)
{
  double rs = getCorrecterResistence(temp);  
  return (double)(rs/RATIO_CLEAN_AIR);
}

double getCorrectedRatio(float temp)
{
  return (double)getCorrecterResistence(temp)/getCorrectedR0(temp);
}

double getR0()
{
  double rs = getResistence();  
  return (double)(rs/RATIO_CLEAN_AIR);
}

double getRatio()
{
  return (double)getResistence()/getR0();
}

double toPPM(double ratio)
{
  //log(r) = m*log(p)+b;
  //(log(r)-b)/m = log(p)
  //p = pow(10, (log(r)-b)/m); 

  double m = -0.149176376376766151;
  double b = 0.70474918321322;

  double logp = (log10(ratio)-b)/m;
  return pow(10, (logp));
}

double getLP(double ratio)
{
  //log(r) = m*log(p)+b;
  //(log(r)-b)/m = log(p)
  //p = pow(10, (log(r)-b)/m); 

  double m = -0.149176376376766151;
  double b = 0.70474918321322;

  return  (log10(ratio)-b)/m;
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  double r0 = getR0();
  double cr0 = getCorrectedR0(20);
   
  double rs =  getResistence();
  double crs = getCorrecterResistence(20);
  
  double rsr0 = getRatio();
  double crsr0 = getCorrectedRatio(20);
  
  double ppm = toPPM(rsr0);
  double cppm = toPPM(crsr0);

  double lp = getLP(rsr0);
  double clp = getLP(crsr0);

 // Serial.print("(RS/R0 | CRS/R0) ");
  //Serial.print(rsr0, CASES);
  
 // Serial.print("|");
  //Serial.println(crsr0, CASES);

  //Serial.print(" RS ");
  //Serial.print(rs, CASES);

  //Serial.print(" C_RS ");
  //Serial.print(crs, CASES);
  
  //Serial.print(" R0 ");
  //Serial.print(r0, CASES);

  //Serial.print(" C_R0 ");
  //Serial.println(cr0, CASES);

  Serial.print("RS ");
  Serial.print(rs);
  Serial.print("|");
  Serial.print(crs);
  Serial.print(" PPM ");
  Serial.print(ppm);
  Serial.print("|");
  Serial.println(cppm);
  
  delay(300);
}

