# Casa-Automatica:

Nosso projeto tem como sua **principal** meta integrar a casa com um sistema de **iluminação** e de **motores** para portões via **WiFi** com a ajuda do aplicativo de celular [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=pt_BR&gl=US), Integrar todos os controladores da casa em um só lugar, facilitando a vida do utilizador e estabelecendo um controle total da casa na palma da mão. 

**Configurações do MQTT:**

- MQTT Server (broker.hivemq.com)
 - Porta (1883)
 - Conexão WiFi padrão
 - Tópicos: 
	 - IFSP/fruitinc
	 - IFSP/ledsala
	 - IFSP/ledquarto1
	 - IFSP/ledquarto2
	 - IFSP/ledcozinha
	 - IFSP/ledgaragem
	 - IFSP/motorgaragem
	 - IFSP/sensor

 - Simulação: [Casa Automática](https://wokwi.com/projects/349074362081477202)

Controle: ![imagem](https://i.imgur.com/BYxx7sZ.jpg)
## Programa em funcionamento:

Para o funcionamento do programa é necessário:


 - **Conexão WiFi**
 - **MqttServer: (broker.hivemq.com)**
 -  **porta: (1883)**

## Materiais:
Foram utilizadas 7 lâmpadas de **LED** nas cores verde, amarelo, vermelho,  laranja e azul, 7 **resistores** equiparentes, **ESP32 WiFi**, **Display Oled**, uma **protoboard** de 400 pinos, cabos **jumpers**, um **Servo Motor** e um **Sensor de Presença**.

## Como Utilizar:

Primeiramente, instale o software de desenvolvimento **Arduino IDE**. Depois acrescente a seguinte URL na aba Arquivo -> Preferências: `(https://dl.espressif.com/dl/package_esp32_index.json)`, adicione a placa "esp32" em Ferramentas -> Placa -> Gerenciador de Placas e configure a placa para **ESP32 DevModule**. Após isso, instale as bibliotecas mencionadas em `Bibliotecas`.

Ademais, instale o aplicativo MQTT Dash para seu dispositivo móvel. Após instalado, crie um novo _broker_ clicando no símbolo de **+**, localizado no canto superior direito, colocando o endereço de IP e a porta, mencionados em `Configurações do MQTT:`.

Depois de criado o _broker_, realize o mesmo procediemento de adição citado acima, incluindo os tópicos presentes na seção `Configurações do MQTT:` e, para aqueles que possuírem formato _Switch_, defina o texto de ativação para _On_ e _Off_, respectivamente, "on" e "off" (OBS: somente o tópico IFSP/motor garagem deverá ter como chaves de ativação os números "1" e "0" para ligar e desligar, respectivamente.

Por fim, verifique se o sistema está funcionando de forma correta. Caso contrário, busque ajuda em sites externos.

## Bibliotecas

- **EspMQTTClient**;
- **Adafruit GFX Library**;
- **WiFi**;
- **Adafruit SSD 1306**;
- **ESP32Servo**;
- **Adafruit BusIO**;
- **ESPPubSubClientWrapper**;
- **MQTTPubSubClient**;
- **PubSubClient**.




