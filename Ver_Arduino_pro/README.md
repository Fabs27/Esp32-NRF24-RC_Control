Claro! Vou te passar um README completo com todas as conexões e itens necessários para montar o transmissor e receptor de 6 canais usando ESP32 e NRF24L01.

---

# 6-Channel Transmitter and Receiver using ESP32 and NRF24L01

## Sumário
- [Descrição](#descrição)
- [Itens Necessários](#itens-necessários)
- [Conexões](#conexões)
- [Código](#código)
- [Como Usar](#como-usar)

## Descrição
Este projeto consiste em um transmissor e receptor de 6 canais utilizando a placa ESP32 e o módulo de comunicação sem fio NRF24L01. É ideal para controlar dispositivos como drones, carros RC, e outros veículos remotos.

## Itens Necessários

### Transmissor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 1 x Joystick ou potenciômetro (para cada canal: throttle, yaw, pitch, roll, aux1 e aux2)
- Protoboard e fios de conexão

### Receptor:
- 1 x ESP32 (38 pinos)
- 1 x Módulo NRF24L01
- 6 x Servomotores
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

- **Joysticks/Potenciômetros:**
  - Throttle (Analog Pin) -> GPIO34 (A0)
  - Yaw (Analog Pin) -> GPIO35 (A1)
  - Pitch (Analog Pin) -> GPIO33 (A2)
  - Roll (Analog Pin) -> GPIO32 (A3)
  - Aux1 (Digital Pin) -> GPIO25 (D2)
  - Aux2 (Analog Pin) -> GPIO26 (A7)

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
  - Servo 1 (Throttle) -> GPIO9
  - Servo 2 (Yaw) -> GPIO2
  - Servo 3 (Pitch) -> GPIO3
  - Servo 4 (Roll) -> GPIO4
  - Servo 5 (Aux1) -> GPIO5
  - Servo 6 (Aux2) -> GPIO6

## Código

### Transmissor:
```cpp
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Definições de pinos para o ESP32
const int CE_PIN = 17;  // Pin GPIO17 para CE
const int CSN_PIN = 5;  // Pin GPIO5 para CSN

const uint64_t pipeOut = 0xE9E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN);

struct Signal {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte aux1;
    byte aux2;
};
Signal data;

void ResetData() {
    data.throttle = 12;
    data.yaw = 127;
    data.pitch = 127;
    data.roll = 127;
    data.aux1 = 0;
    data.aux2 = 127;
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
    // Serial.begin(250000);
    delay(1000);
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

void loop() {
    data.throttle = mapJoystickValues(analogRead(34), 12, 524, 1020, true);
    data.yaw = mapJoystickValues(analogRead(35), 12, 524, 1020, false);
    data.roll = mapJoystickValues(analogRead(32), 12, 524, 1020, true);
    data.pitch = mapJoystickValues(analogRead(33), 12, 524, 1020, false);
    data.aux1 = digitalRead(25);
    data.aux2 = mapJoystickValues(analogRead(26), 12, 524, 1020, true);
    radio.write(&data, sizeof(Signal));
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

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;

struct Signal {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
    byte aux1;
    byte aux2;
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

    ch1.writeMicroseconds(ch_width_1);
    ch2.writeMicroseconds(ch_width_2);
    ch3.writeMicroseconds(ch_width_3);
    ch4.writeMicroseconds(ch_width_4);
    ch5.writeMicroseconds(ch_width_5);
    ch6.writeMicroseconds(ch_width_6);

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
    // Serial.println(" ");
}
```

## Como Usar

1. **Configuração do Hardware:**
   - Conecte todos os componentes de acordo com as seções de conexões descritas acima para o transmissor e receptor.

2. **Carregar o Código:**
   - Carregue o código do transmissor no ESP32 conectado aos joysticks/potenciômetros.
   - Carregue o código do receptor no ESP32 conectado aos servomotores.

3. **Operação:**
   - Ligue o transmissor e o receptor.
   - Movimente os joysticks/potenciômetros no transmissor para controlar os servomotores no receptor.

4. **Testes:**
   - Teste cada canal para garantir que os sinais estão sendo transmitidos corretamente e que os servomotores estão respondendo conforme esperado.

### Dicas Adicionais:
- Certifique-se de que os módulos NRF24L01 estejam corretamente alimentados e com boa conexão à antena para melhor alcance.
- Verifique as ligações e conexões dos pinos para evitar falhas de comunicação.
- Se necessário, ajuste os valores mapeados dos joysticks/potenciômetros para calibrar os controles de acordo com suas necessidades.

---

Se precisar de mais ajuda ou tiver alguma dúvida, estou aqui para ajudar! 😊
