# MQSensor
Uma biblioteca para facilitar o uso de qualquer sensor MQ.  
Foram testados os sensores MQ8 e MQ135.  

# Metodologia 
O site [WebPlotDigitizer](https://automeris.io/wpd/) foi utilizado para extrair dados das curvas de calibração dos sensores (Disponíveis nos datasheets dos fabricantes).   
Os dados extraídos foram plotados e regressões exponênciais foram feitas utilizando o software [SciDavis](https://scidavis.sourceforge.net/).

### MQ8 
![mq8](./dados/mq8.png)

### MQ135
![mq135](./dados/mq135.png)
