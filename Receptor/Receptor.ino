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
