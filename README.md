Aqui está a primeira parte do README detalhado para o projeto do transmissor e receptor de 6 canais utilizando ESP32 e NRF24L01, sem o código, com marcações para onde adicionar o código:

---

# 20-Channel Transmitter and Receiver using ESP32 and NRF24L01

## Sumário
- [Descrição](#descrição)
- [Itens Necessários](#itens-necessários)
- [Conexões](#conexões)
- [Código](#código)
- [Como Usar](#como-usar)
- [Conexões e Circuito Adicional](#conexões-e-circuito-adicional)
- [Display OLED](#display-oled)
- [Buzzer de Alerta](#buzzer-de-alerta)
- [Configurando os Botões para Funções](#configurando-os-botões-para-funções)

## Descrição
Este projeto consiste em um transmissor e receptor de 6 canais utilizando a placa ESP32 e o módulo de comunicação sem fio NRF24L01. Além dos canais de joystick e leitura de tensão, ele inclui 14 canais adicionais de botões, uma tela OLED para exibir informações e um buzzer para alertas de baixa tensão. É ideal para controlar dispositivos como drones, carros RC, e outros veículos remotos.

## Itens Necessários

### Transmissor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 1 x Tela OLED SPI 0.91" (ou 0.96")
- 1 x Buzzer
- 1 x Transistor BC547
- 1 x Capacitor 1000uF 6.3V/3.3V
- 4 x Resistores 10K (para divisor de tensão)
- 2 x Joysticks (para canais de throttle, yaw, pitch e roll)
- 1 x Potenciômetro de 10k (para canal aux2)
- Botões para canais adicionais (14 botões)
- Protoboard e fios de conexão

### Receptor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 20 x Servomotores (para todos os canais) funçoes programaveis (para todos os canais)
- Protoboard e fios de conexão

## Conexões

### Transmissor:
- **NRF24L01 para ESP32:**
  - GND -> GND
  - VCC -> 3.3V
  - CE  -> GPIO17
  - CSN -> GPIO5
  - SCK -> GPIO18
  - MOSI -> GPIO23
  - MISO -> GPIO19

- **Tela OLED SPI:**
  - GND -> GND
  - VCC -> 3.3V
  - SCK -> GPIO18
  - SDA -> GPIO23

- **Leitura de Tensão:**
  - Divisor de tensão com resistores de 10K (em série) e capacitor de 1000uF entre VCC e GND. Ponto médio dos resistores para ADC (ex: GPIO36).

- **Buzzer:**
  - Transistor BC547: Emissor para GND, Coletor para um lado do buzzer, outro lado do buzzer para VCC.
  - Capacitor 10K entre base do transistor e GPIO22.

- **Joysticks/Potenciômetros:**
  - Joystick 1 (Throttle e Yaw) -> GPIO34 (A0) e GPIO35 (A1)
  - Joystick 2 (Pitch e Roll) -> GPIO32 (A3) e GPIO33 (A2)
  - Potenciômetro de 10k (Aux2) -> GPIO26 (A7)

- **Botões:**
  - Botão 1 -> GPIO 10 (com resistor pull-down)
  - Botão 2 -> GPIO 11 (com resistor pull-down)
  - Botão 3 -> GPIO 12 (com resistor pull-down)
  - Botão 4 -> GPIO 13 (com resistor pull-down)
  - Botão 5 -> GPIO 14 (com resistor pull-down)
  - Botão 6 -> GPIO 15 (com resistor pull-down)
  - Botão 7 -> GPIO 16 (com resistor pull-down)
  - Botão 8 -> GPIO 17 (com resistor pull-down)
  - Botão 9 -> GPIO 18 (com resistor pull-down)
  - Botão 10 -> GPIO 19 (com resistor pull-down)
  - Botão 11 -> GPIO 20 (com resistor pull-down)
  - Botão 12 -> GPIO 21 (com resistor pull-down)
  - Botão 13 -> GPIO 22 (com resistor pull-down)
  - Botão 14 -> GPIO 23 (com resistor pull-down)

### Receptor:
- **NRF24L01 para ESP32:**
  - GND -> GND
  - VCC -> 3.3V
  - CE  -> GPIO17
  - CSN -> GPIO5
  - SCK -> GPIO18
  - MOSI -> GPIO23
  - MISO -> GPIO19

- **Servomotores:**
  - Servo 1 -> GPIO9
  - Servo 2 -> GPIO2
  - Servo 3 -> GPIO3
  - Servo 4 -> GPIO4
  - Servo 5 -> GPIO5
  - Servo 6 -> GPIO6
  - Servo 7 -> GPIO10
  - Servo 8 -> GPIO11
  - Servo 9 -> GPIO12
  - Servo 10 -> GPIO13
  - Servo 11 -> GPIO14
  - Servo 12 -> GPIO15
  - Servo 13 -> GPIO16
  - Servo 14 -> GPIO17
  - Servo 15 -> GPIO18
  - Servo 16 -> GPIO19
  - Servo 17 -> GPIO20
  - Servo 18 -> GPIO21
  - Servo 19 -> GPIO22
  - Servo 20 -> GPIO23

## Código

---

# 20-Channel Transmitter and Receiver using ESP32 and NRF24L01

## Sumário
- [Descrição](#descrição)
- [Itens Necessários](#itens-necessários)
- [Conexões](#conexões)
- [Código](#código)
- [Como Usar](#como-usar)
- [Conexões e Circuito Adicional](#conexões-e-circuito-adicional)
- [Display OLED](#display-oled)
- [Buzzer de Alerta](#buzzer-de-alerta)

## Descrição
Este projeto consiste em um transmissor e receptor de 6 canais utilizando a placa ESP32 e o módulo de comunicação sem fio NRF24L01. Além dos canais de joystick e leitura de tensão, ele inclui 14 canais adicionais de botões, uma tela OLED para exibir informações e um buzzer para alertas de baixa tensão. É ideal para controlar dispositivos como drones, carros RC, e outros veículos remotos.

## Itens Necessários

### Transmissor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 1 x Tela OLED SPI 0.91" (ou 0.96")
- 1 x Buzzer
- 1 x Transistor BC547
- 1 x Capacitor 1000uF 6.3V/3.3V
- 4 x Resistores 10K (para divisor de tensão)
- Joysticks/Potenciômetros (para canais de throttle, yaw, pitch, roll, aux1 e aux2)
- Botões para canais adicionais (14 botões)
- Protoboard e fios de conexão

### Receptor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 20 x Servomotores (para todos os canais)
- Protoboard e fios de conexão

## Conexões

### Transmissor:
- **NRF24L01 para ESP32:**
  - GND -> GND
  - VCC -> 3.3V
  - CE  -> GPIO17
  - CSN -> GPIO5
  - SCK -> GPIO18
  - MOSI -> GPIO23
  - MISO -> GPIO19

- **Tela OLED SPI:**
  - GND -> GND
  - VCC -> 3.3V
  - SCK -> GPIO18
  - SDA -> GPIO23

- **Leitura de Tensão:**
  - Divisor de tensão com resistores de 10K (em série) e capacitor de 1000uF entre VCC e GND. Ponto médio dos resistores para ADC (ex: GPIO36).

- **Buzzer:**
  - Transistor BC547: Emissor para GND, Coletor para um lado do buzzer, outro lado do buzzer para VCC.

## Código

### Transmissor:

```cpp
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definições de pinos para o ESP32
const int CE_PIN = 17;  // Pin GPIO17 para CE
const int CSN_PIN = 5;  // Pin GPIO5 para CSN
const int BUZZER_PIN = 22;
const int VOLTAGE_PIN = 36; // ADC para leitura de tensão
const uint64_t pipeOut = 0xE9E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct Signal {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte aux1;
    byte aux2;
    byte button[14];  // Adicionando 14 canais de botões
};
Signal data;

void ResetData() {
    data.throttle = 12;
    data.yaw = 127;
    data.pitch = 127;
    data.roll = 127;
    data.aux1 = 0;
    data.aux2 = 127;
    for (int i = 0; i < 14; i++) {
        data.button[i] = 0;
    }
}

void setup() {
    radio.begin();
    radio.stopListening();
    radio.openWritingPipe(pipeOut);
    radio.setAutoAck(false);
    radio.setCRCLength(RF24_CRC_8);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(108);
    ResetData();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
    delay(1000);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    for (int i = 10; i <= 23; i++) { // Definindo pinos 10 a 23 para botões
        pinMode(i, INPUT_PULLDOWN);
    }
}

int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse) {
    val = constrain(val, lower, upper);
    if (val < middle) {
        val = map(val, lower, middle, 0, 128);
    } else {
        val = map(val, middle, upper, 128, 255);
    }
    return (reverse ? 255 - val : val);
}

void displayVoltage(float voltage) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Voltage: ");
    display.print(voltage);
    display.println("V");
    display.display();
}

void loop() {
    data.throttle = mapJoystickValues(analogRead(34), 12, 524, 1020, true);
    data.yaw = mapJoystickValues(analogRead(35), 12, 524, 1020, false);
    data.roll = mapJoystickValues(analogRead(32), 12, 524, 1020, true);
    data.pitch = mapJoystickValues(analogRead(33), 12, 524, 1020, false);
    data.aux1 = digitalRead(25);
    data.aux2 = mapJoystickValues(analogRead(26), 12, 524, 1020, true);
    
    for (int i = 0; i < 14; i++) {
        data.button[i] = digitalRead(10 + i);
    }

    float voltage = analogRead(VOLTAGE_PIN) * (3.3 / 4095.0) * 2; // Multiplicar por 2 devido ao divisor de tensão
    displayVoltage(voltage);

    radio.write(&data, sizeof(Signal));

    if (voltage < 3.3) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}
```

### Receptor:

```cpp

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32Servo.h>  // Inclua a biblioteca ESP32Servo

// Definições de pinos para o ESP32
const int CE_PIN = 17;  // Pin GPIO17 para CE
const int CSN_PIN = 5;  // Pin GPIO5 para CSN

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;
int ch_width_7 = 0;
int ch_width_8 = 0;
int ch_width_9 = 0;
int ch_width_10 = 0;
int ch_width_11 = 0;
int ch_width_12 = 0;
int ch_width_13 = 0;
int ch_width_14 = 0;
int ch_width_15 = 0;
int ch_width_16 = 0;
int ch_width_17 = 0;
int ch_width_18 = 0;
int ch_width_19 = 0;
int ch_width_20 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;
Servo ch7;
Servo ch8;
Servo ch9;
Servo ch10;
Servo ch11;
Servo ch12;
Servo ch13;
Servo ch14;
Servo ch15;
Servo ch16;
Servo ch17;
Servo ch18;
Servo ch19;
Servo ch20;

struct Signal {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte aux1;
    byte aux2;
    byte button[14];  // Adicionando 14 canais de botões
};

Signal data;
const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

void ResetData() {
    data.roll = 127;
    data.pitch = 127;
    data.throttle = 12;
    data.yaw = 127;
    data.aux1 = 0;
    data.aux2 = 127;
    for (int i = 0; i < 14; i++) {
        data.button[i] = 0;
    }
}

void setup() {
    radio.begin();
    radio.startListening();
    radio.openReadingPipe(1, pipeIn);
    radio.setAutoAck(false);
    radio.setCRCLength(RF24_CRC_8);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(108);
    ResetData();
    // Serial.begin(250000);

    ch1.attach(9);
    ch2.attach(2);
    ch3.attach(3);
    ch4.attach(4);
    ch5.attach(5);
    ch6.attach(6);
    ch7.attach(10);
    ch8.attach(11);
    ch9.attach(12);
    ch10.attach(13);
    ch11.attach(14);
    ch12.attach(15);
    ch13.attach(16);
    ch14.attach(17);
    ch15.attach(18);
    ch16.attach(19);
    ch17.attach(20);
    ch18.attach(21);
    ch19.attach(22);
    ch20.attach(23);
    delay(1000);
}

unsigned long lastRecvTime = 0;

void recvData() {
    while (radio.available()) {
        radio.read(&data, sizeof(Signal));
        lastRecvTime = millis();
    }
}

void loop() {
    recvData();
    unsigned long now = millis();
    if (now - lastRecvTime > 1000) {
        ResetData();
    }

    ch_width_1 = map(data.roll, 0, 255, 1000, 2000);
    ch_width_2 = map(data.pitch, 0, 255, 1000, 2000);
    ch_width_3 = map(data.throttle, 0, 255, 1000, 2000);
    ch_width_4 = map(data.yaw, 0, 255, 1000, 2000);
    ch_width_5 = map(data.aux1, 0, 1, 1000, 2000);
    ch_width_6 = map(data.aux2, 0, 255, 1000, 2000);
    ch_width_7 = map(data.button[0], 0, 1, 1000, 2000);
    ch_width_8 = map(data.button[1], 0, 1, 1000, 2000);
    ch_width_9 = map(data.button[2], 0, 1, 1000, 2000);
    ch_width_10 = map(data.button[3], 0, 1, 1000, 2000);
    ch_width_11 = map(data.button[4], 0, 1, 1000, 2000);
    ch_width_12 = map(data.button[5], 0, 1, 1000, 2000);
    ch_width_13 = map(data.button[6], 0, 1, 1000, 2000);
    ch_width_14 = map(data.button[7], 0, 1, 1000, 2000);
    ch_width_15 = map(data.button[8], 0, 1, 1000, 2000);
    ch_width_16 = map(data.button[9], 0, 1, 1000, 2000);
    ch_width_17 = map(data.button[10], 0, 1, 1000, 2000);
    ch_width_18 = map(data.button[11], 0, 1, 1000, 2000);
    ch_width_19 = map(data.button[12], 0, 1, 1000, 2000);
    ch_width_20 = map(data.button[13], 0, 1, 1000, 2000);

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);
    ch7.writeMicroseconds(ch_width_7);
    ch8.writeMicroseconds(ch_width_8);
    ch9.writeMicroseconds(ch_width_9);
    ch10.writeMicroseconds(ch_width_10);
    ch11.writeMicroseconds(ch_width_11);
    ch12.writeMicroseconds(ch_width_12);
    ch13.writeMicroseconds(ch_width_13);
    ch14.writeMicroseconds(ch_width_14);
    ch15.writeMicroseconds(ch_width_15);
    ch16.writeMicroseconds(ch_width_16);
    ch17.writeMicroseconds(ch_width_17);
    ch18.writeMicroseconds(ch_width_18);
    ch19.writeMicroseconds(ch_width_19);
    ch20.writeMicroseconds(ch_width_20);

    // Serial.print(data.pitch);
    // Serial.print(" ");
    // Serial.print(data.throttle);
    // Serial.print(" ");
    // Serial.print(data.yaw);
    // Serial.print(" ");
    // Serial.print(data.roll);
    // Serial.print(" ");
    // Serial.print(data.aux1);
    // Serial.print(" ");
    // Serial.print(data.aux2);
    // Serial.print(" ");
    // Serial.print(ch_width_1);
    // Serial.print(" ");
    // Serial.print(ch_width_2);
    // Serial.print(" ");
    // Serial.print(ch_width_3);
    // Serial.print(" ");
    // Serial.print(ch_width_4);
    // Serial.print(" ");
    // Serial.print(ch_width_5);
    // Serial.print(" ");
    // Serial.print(ch_width_6);
    // Serial.print(" ");
    // Serial.print(ch_width_7);
    // Serial.print(" ");
    // Serial.print(ch_width_8);
    // Serial.print(" ");
    // Serial.print(ch_width_9);
    // Serial.print(" ");
    // Serial.print(ch_width_10);
    // Serial.print(" ");
    // Serial.print(ch_width_11);
    // Serial.print(" ");
    // Serial.print(ch_width_12);
    // Serial.print(" ");
    // Serial.print(ch_width_13);
    // Serial.print(" ");
    // Serial.print(ch_width_14);
    // Serial.print(" ");
    // Serial.print(ch_width_15);
    // Serial.print(" ");
    // Serial.print(ch_width_16);
    // Serial.print(" ");
    // Serial.print(ch_width_17);
    // Serial.print(" ");
    // Serial.print(ch_width_18);
    // Serial.print(" ");
    // Serial.print(ch_width_19);
    // Serial.print(" ");
    // Serial.print(ch_width_20);
    // Serial.println(" ");
}

```



## Como Usar

1. **Configuração do Hardware:**
   - Conecte todos os componentes de acordo com as seções de conexões descritas acima para o transmissor e receptor.

2. **Carregar o Código:**
   - Carregue o código do transmissor no ESP32 conectado aos joysticks/potenciômetros e botões.
   - Carregue o código do receptor no ESP32 conectado aos servomotores.

3. **Operação:**
   - Ligue o transmissor e o receptor.
   - Movimente os joysticks/potenciômetros no transmissor para controlar os servomotores no receptor.
   - Pressione os botões para ativar os canais adicionais e controlar os servomotores correspondentes.

4. **Testes:**
   - Teste cada canal para garantir que os sinais estão sendo transmitidos corretamente e que os servomotores estão respondendo conforme esperado.

## Conexões e Circuito Adicional

### Leitura de Tensão:
Para implementar a leitura de tensão, utilize um divisor de tensão com dois resistores de 10K em série. Conecte um capacitor de 1000uF entre VCC e GND para estabilizar a leitura. O ponto médio dos resistores deve ser conectado ao pino ADC do ESP32 (GPIO36).

### Display OLED:
Conecte a tela OLED SPI ao ESP32 conforme descrito na seção de conexões. Certifique-se de inicializar a tela OLED no código do transmissor para exibir a tensão lida.

### Buzzer de Alerta:
Conecte o buzzer ao ESP32 através de um transistor BC547. Use um resistor de 10K entre a base do transistor e o pino GPIO22 do ESP32. O buzzer será ativado quando a tensão medida estiver abaixo de um valor específico (por exemplo, 3.3V).

---

## Display OLED

A tela OLED é usada para exibir a leitura de tensão do sistema. Utilize a biblioteca Adafruit_SSD1306 para inicializar e controlar a tela OLED. No código, a função `displayVoltage(float voltage)` é responsável por atualizar as informações exibidas na tela.

## Buzzer de Alerta

O buzzer é utilizado para emitir alertas de baixa tensão. Utilize um transistor BC547 para controlar o buzzer a partir do ESP32. Quando a tensão medida pelo divisor de tensão estiver abaixo de 3.3V, o buzzer será ativado.

## Configurando os Botões para Funções

Os botões adicionais podem ser configurados para diversas funções no código do transmissor. Cada botão está conectado a um pino GPIO específico e pode ser lido utilizando a função `digitalRead()`. No código do transmissor, cada botão é mapeado para um índice no array `data.button`.

### Exemplo de Configuração de Função para um Botão:
No código, você pode adicionar lógica condicional para executar ações específicas quando um botão for pressionado. Por exemplo, para configurar o botão 1 para acionar uma função específica:

```cpp
if (data.button[0] == HIGH) {
    // Código para acionar a função específica
}
```

### Funções Possíveis:
- **Ativar/Desativar LEDs:** Conecte um LED a um pino GPIO e controle-o com um botão.
- **Trocar Modo de Operação:** Use botões para alternar entre diferentes modos de operação do transmissor/receptor.
- **Emitir Som com Buzzer:** Use um botão para ativar o buzzer quando necessário.
- **Ativar Motores ou Outros Dispositivos:** Utilize os botões para controlar diretamente outros dispositivos conectados aos pinos GPIO do receptor.

### Configurando Múltiplos Botões:
Para configurar múltiplos botões, adicione lógica semelhante para cada botão, modificando o índice do array `data.button` conforme necessário. Por exemplo, para configurar o botão 2:

```cpp
if (data.button[1] == HIGH) {
    // Código para acionar a função específica do botão 2
}
```

## Conclusão
Este README fornece as instruções necessárias para configurar e operar o sistema de transmissor e receptor de 20 canais utilizando ESP32 e NRF24L01. Certifique-se de seguir as conexões e carregar os códigos apropriados no transmissor e receptor. Utilize as seções de configuração de botões e componentes adicionais para personalizar o sistema de acordo com suas necessidades específicas.

---
