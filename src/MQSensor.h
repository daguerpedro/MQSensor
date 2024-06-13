#ifndef _MQSensor
#define _MQSensor

#include <Arduino.h>
class MQSensor
{
private:
    unsigned int m_LoadResistor; 
    unsigned int m_R0;

    uint8_t m_AnalogPort;
    
    float m_Resulution;
    float m_Bits;

public:
    MQSensor(uint8_t analogPort, unsigned int loadResistor, float resolution = 5, float bits = 10) :  m_AnalogPort(analogPort),  m_LoadResistor(loadResistor), m_Resulution(resolution), m_Bits(bits) {    };

    float readVoltage()
    {
        return this->m_Resulution * analogRead(this->m_AnalogPort) / (pow(2, this->m_Bits)-1);
    };

    float setup(int samples = 1)
    {
        float avg = 0;
        
        for(int i = 0; i < samples; i++)
            avg += readRS();

        avg = avg / samples;

        this->m_R0 = avg;
        return this->m_R0;
    }

    float readRS()
    {
        float RL = this->m_LoadResistor;
        float VC = 5;

        float rs = ((VC*RL)/readVoltage())-RL;
        return rs;
    }

    float readRSR0()
    {
        return (readRS()/this->m_R0);
    }

    float readPPM(float a, float b)
    {
        return a * pow(readRSR0(), b);
    }
};
#endif
