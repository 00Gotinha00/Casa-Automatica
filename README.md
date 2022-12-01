# Casa-Automatica:

Nosso projeto tem como sua **principal** meta integrar a casa com um sistema de **iluminação** e de **motores** para portões via **WiFi** com a ajuda do aplicativo de celular [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=pt_BR&gl=US), Integrar todos os controladores da casa em um só lugar, facilitando a vida do utilizador e estabelecendo um controle total da casa na palma da mão. 

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
 -  
## Materiais:
Foram utilizadas 6 lâmpadas de **LED** nas cores verde, amarelo, vermelho,  laranja e azul, 6 **resistores** equiparentes, **ESP32 WiFi**, **Display Oled**, uma **protoboard** de 400 pinos, cabos **jumpers** ,um **Servo Motor** e um **Sensor de Presença**.
