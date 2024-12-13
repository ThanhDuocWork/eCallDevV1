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
#include "json.hpp" 

using json = nlohmann::json;

class MQTTAdapter {
private:
    static std::shared_ptr <MQTTAdapter> mInstanceMQTT;

public:
    MQTTAdapter();
    ~MQTTAdapter();

    static MQTTAdapter *getInstance();
    void SubMQTT();
    void PubMQTT(const json &command_json);
    void handleMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    static void onDisconnectCallback(struct mosquitto *mosq, void *userdata, int rc);
    void sendMessage(const json  *message);
};

#endif
