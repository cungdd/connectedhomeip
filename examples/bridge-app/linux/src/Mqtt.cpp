#include "Mqtt.h"

#include <platform/CHIPDeviceLayer.h>
#include <CHIPProjectAppConfig.h>

static struct mosquitto *mosq;
string mqtt_topic_publish;  

static string parse(uint8_t _mode, string deviceId, uint8_t _value);
static void publish(string data);

static void connect_callback(struct mosquitto *_mosq, void *obj, int result)
{
    
    // cout << "\n Connected MQTT - RC=" << result << "\n" << endl;
    ChipLogProgress(MessageLayer, "RANG DONG-Connected MQTT - RC=%d", result);
}


struct mosquitto * MqttConnect(void){

    Json::Value mqttInfo;

    ifstream fileJson(PATH_MQTT, ifstream::binary);
    
    fileJson >> (mqttInfo);
    fileJson.close();

	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, true, NULL);
	if(mosq){
        mqtt_topic_publish = mqttInfo["topic_publish"].asString();

		mosquitto_connect_callback_set(mosq, connect_callback);
        
        mosquitto_username_pw_set(mosq, mqttInfo["user"].asCString(), mqttInfo["password"].asCString());
	    mosquitto_connect(mosq, mqttInfo["host"].asCString(), mqttInfo["port"].asInt(), 60);
        mosquitto_loop_start(mosq);
        mosquitto_subscribe(mosq, NULL, mqttInfo["topic_subscribe"].asCString(), 0);
 
        ChipLogProgress(MessageLayer, "RANG DONG-MQTT Host:%s", mqttInfo["host"].asCString());
        ChipLogProgress(MessageLayer, "RANG DONG-MQTT Port:%d", mqttInfo["port"].asInt());
        ChipLogProgress(MessageLayer, "RANG DONG-MQTT Username:%s", mqttInfo["user"].asCString());
        ChipLogProgress(MessageLayer, "RANG DONG-MQTT Password:%s", mqttInfo["host"].asCString());
        ChipLogProgress(MessageLayer, "RANG DONG-MQTT Connecting...");
    }    
    return mosq;
}


void MqttControllOnOff(string deviceID, uint8_t value){
    publish(parse(ONOFF, deviceID, value));
}

void MqttControllDim(string deviceID, uint8_t value){
    publish(parse(DIM, deviceID, value));
}
void MqttControllCct(string deviceID, uint8_t value){
    publish(parse(CCT, deviceID, value));
}
void MqttControllHue(string deviceID, uint8_t value){
    publish(parse(HUE, deviceID, value));
}
void MqttControllSaturation(string deviceID, uint8_t value){
    publish(parse(SATURATION, deviceID, value));
}

void MqttControllHSV(string deviceID, uint8_t h, uint8_t s, uint8_t l, uint8_t dim){
    Json::Value cmd;
    cmd["cmd"] = "controlDev";
    cmd["rqi"] = "abc123456";
    cmd["data"]["id"] = deviceID;
    cmd["data"]["data"]["dim"] = dim;
    cmd["data"]["data"]["h"] = h*65535/255;
    cmd["data"]["data"]["s"] = s*65535/225;
    cmd["data"]["data"]["l"] = l*65535/225;
    Json::FastWriter writer;    
    publish(writer.write(cmd));
}

void MqttGetStatusDevice(void){
    const char* msg = "{\"CMD\":\"DEVICE_UPDATE\"}";
    mosquitto_publish(mosq, NULL, mqtt_topic_publish.c_str(), (int) sizeof(msg), msg, 2, false);
}

static string parse(uint8_t mode, string deviceID, uint8_t value){
    
    Json::Value cmd;

    cmd["cmd"] = "controlDev";
    cmd["rqi"] = "abc123456";
    cmd["data"]["id"] = deviceID;
    if(mode == ONOFF)
        cmd["data"]["data"]["onoff"] = value;
    else if(mode == DIM)
        cmd["data"]["data"]["dim"] = value;
    else if(mode == CCT)
        cmd["data"]["data"]["cct"] = value;
    else if(mode == HUE)
        cmd["data"]["data"]["h"] = value;
    else if(mode == SATURATION)
        cmd["data"]["data"]["s"] = value;

    Json::FastWriter writer;    
    return writer.write(cmd);
}

static void publish(string data){
    // printf("Send MQTT:%s", data.c_str());
    mosquitto_publish(mosq, NULL, mqtt_topic_publish.c_str(), (int) data.length(), data.c_str(), 2, false);
}
