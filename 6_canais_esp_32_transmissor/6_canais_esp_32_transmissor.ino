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
