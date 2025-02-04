#ifndef MQTTADAPTER_H
#define MQTTADAPTER_H

#include "AudioAdapter.h"
#include "HMIAdapter.h"
#include "Logger.h"
#include "json.hpp"
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <memory>
#include <mosquitto.h>
#include <string>
#include <thread>

#include "EventData.h"
#include "EventTable.h"
using json = nlohmann::json;
class EventMQTT : public EventData
{
    private:
    std::string mEventString;
    static EventMQTT* instancePtr;
    public:
    EventMQTT (uint32_t messageID) : EventData (messageID)
    {
    }
    ~EventMQTT()
    {

    }
    void setData (std::string data)
    {
        mEventString = data;
    }
    std::string getData ()
    {
        return mEventString;
    }
    // static EventMQTT *getInstance()
    // {
    //     if(instancePtr == nullptr)
    //     {
    //         // check this constructor
    //         uint32_t messageID = 10;
    //         instancePtr = new EventMQTT(messageID);
    //     }
    //     return instancePtr;
    // }
};
class MQTTAdapter
{
    private:
    static std::shared_ptr<MQTTAdapter> mInstanceMQTT;
    static bool running;
    std::string mMessageResponse;

    std::function<void(const std::string& topic, const std::string& payload)> mOnMessageCallback;
    std::shared_ptr<struct mosquitto> mMosq;
    std::mutex mCallbackMutex;

    public:
    MQTTAdapter ();
    ~MQTTAdapter ();

    static MQTTAdapter *getInstance ();
    void SubMQTT ();
    void PubMQTT (const std::string &command_json);
    void handleMessage (struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    void connectToBroker (struct mosquitto *mosq, void *userdata, int result);
    void disconnectToBroker (struct mosquitto *mosq, void *userdata, int rc);
    void messageCallback (struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);
    void sendMessage (const std::string &message);
    static void handleSignal (int signal);
    const std::string getResponseFromSub();

    void handleEventSub ();
    void setOnMessageCallback(const std::function<void(const std::string& topic, const std::string& payload)>& callback);
};
#endif
