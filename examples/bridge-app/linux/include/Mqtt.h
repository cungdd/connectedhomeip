
#pragma once
#include <string.h>
#include <mosquitto.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <stdio.h>
#include <iostream>

using namespace std;

#define PATH_MQTT "/var/tmp/mqtt-config.json"

using namespace std;

enum ModeLed{
    ONOFF,
    DIM,
    CCT,
    HUE,
    SATURATION
};

enum Control{
    OFF,
    ON
};

struct mosquitto * MqttConnect(void);

void MqttControllOnOff(string deviceID, uint8_t value);
void MqttControllDim(string deviceID, uint8_t value);
void MqttControllCct(string deviceID, uint8_t value);
void MqttControllHue(string deviceID, uint8_t value);
void MqttControllSaturation(string deviceID, uint8_t value);
void MqttControllHSV(string deviceID, uint8_t h, uint8_t s, uint8_t l, uint8_t dim);
void MqttGetStatusDevice(void);