#ifndef _MQ
#define _MQ

#include <arduino.h>

#define uint unsigned int 

#ifndef ANALOGRESOLUTION
#define ANALOGRESOLUTION 5.0
#endif

#ifndef ANALOG_BITS
#define ANALOG_BITS 10
#endif

class MQ
{
private:
    uint m_LoadResistor; 
    uint m_R0;

    uint m_ratioInCleanAir;

    uint m_AnalogPort;
    
    float readVoltage()
    {
        return ANALOGRESOLUTION * analogRead(this->m_AnalogPort) / (pow(2, ANALOG_BITS)-1);
    };

    float temperature = 0;
    float humidity = 0;

public:
    /// @brief Inicia uma instancia de um MQ qualer
    /// @param analogPort Porta analogica conectada ao sensor.
    /// @param loadResistor Resitor de carga do sensor (em KOhm)
    /// @param ratioInCleanAir RS/R0 no ar. Pode ser extraido do datasheet ou calculada usando setR0(calculateR0()) e getRS_R0() em um ambiente com ar limpo.
    MQ(uint8_t analogPort, uint loadResistor, uint ratioInCleanAir) :
        m_AnalogPort(analogPort),
        m_LoadResistor(loadResistor), 
        m_ratioInCleanAir(ratioInCleanAir){
            this->m_R0 = ratioInCleanAir;
    }

    /// @brief Atualiza o valor de R0
    /// @param R0 em KOhm
    void setR0(float R0)
    {
        this->m_R0 = R0;
    }

    /// @brief A FAZER!
    /// @param temperature 
    /// @param humidity 
    void updateTemperatureHumidity(float temperature, float humidity)
    {
        float temperature = temperature;
        float humidity = humidity;
    }

    /// @brief Calcula o R0, ao invés de usar o do datasheet.
    /// @param samples 
    float calculateR0(int samples = 1)
    {
        float avg = 0;
        
        for(int i = 0; i < samples; i++)
            avg += readRS();

        avg = avg / samples;

        return avg/this->m_ratioInCleanAir;
    }

    ///@brief Le a resistencia do sensor, 
    ///@brief RS = [(VC x RL) / VRL] - RL
    ///@param RL Resistor de carga
    ///@param VC Tensão de alimentação sensor
    ///@param RS Resistencia do sensor   
    float readRS()
    {
        float RL = this->m_LoadResistor;
        float VC = ANALOGRESOLUTION;

        float rs = ((VC*RL)/readVoltage())-RL;
        return rs;
    }

    /// @brief Le a resistencia do sensor e divide pelo R0 salvo por 'ratioInCleanAir' ou setR0(). 
    /// @return Retorna a divisão RS/R0
    float getRS_R0()
    {
        return readRS()/this->m_R0;
    }

    /// @brief Converte getRS_R0() em PPM por uma regressão expdecay.
    /// @brief ppm = y0 + a*exp(-rs/t)
    float readPPM(float y0, float a, float t)
    {
        return (y0 + a * exp(-getRS_R0()/t));
    }

    /// @brief Converte getRS_R0() em PPM por uma regressão de potência.
    /// @brief ppm = a * rs^b
    float readPPM(float a, float b)
    {
        return a * pow(getRS_R0(), b);
    }
};

#endif