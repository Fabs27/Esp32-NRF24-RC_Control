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
