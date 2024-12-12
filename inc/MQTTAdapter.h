#ifndef MQTTADAPTER_H
#define MQTTADAPTER_H

#include <iostream>
#include <mosquitto.h>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include <memory>
#include "Logger.h"
#include<thread>
#include<chrono>

class MQTTAdapter {
private:
    static std::shared_ptr <MQTTAdapter> mInstanceMQTT;

public:
    MQTTAdapter();
    ~MQTTAdapter();

    static MQTTAdapter *getInstance();
    void SubMQTT();
    void PubMQTT();
    void handleMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void onDisconnectCallback(struct mosquitto *mosq, void *userdata, int rc);
};

#endif
