#include "MQTTAdapter.h"
std::shared_ptr<MQTTAdapter> MQTTAdapter::mInstanceMQTT = nullptr;
bool MQTTAdapter::running;
MQTTAdapter::MQTTAdapter ()
{
    mosquitto_lib_init ();
}

MQTTAdapter::~MQTTAdapter ()
{
    mosquitto_lib_cleanup ();
}
void MQTTAdapter::sendMessage (const std::string &message)
{
    MQTTAdapter::PubMQTT (message);
}
void MQTTAdapter::PubMQTT (const std::string &commandMessage)
{
    const char *id = "publisher-client";
    std::shared_ptr<struct mosquitto> mosq (mosquitto_new (id, true, NULL), mosquitto_destroy);
    if (!mosq)
    {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        return;
    }

    const char *host   = "192.168.137.180";
    u_int32_t port     = 1883;
    u_int32_t timeLive = 60;

    if (mosquitto_connect (mosq.get (), host, port, timeLive) != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Failed to connect to broker." << std::endl;
        return;
    }

    const char *topic     = "ecall/response";
    std::string flagTopic = topic;
    std::string commandPayload;
    if (commandMessage == "ON")
    {
        nlohmann::json jsonMessage = { { "vin_id", "FPT53516551000141999" }, { "ip", "192.168.2.1" }, { "latitude", 10.011280 }, { "longitude", 105.730525 } };
        commandPayload             = jsonMessage.dump ();
    }
    else if (commandMessage == "OFF")
    {
        // commandPayload = R"({"status":"off"})";
    }
    else
    {
        std::cerr << "Invalid command message: " << commandMessage << std::endl;
        return;
    }

    if (mosquitto_publish (mosq.get (), NULL, topic, commandPayload.size (), commandPayload.c_str (), 1, true) != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Failed to publish message." << std::endl;
        return;
    }

    printLog_I ("Message published to topic: %s", flagTopic.c_str ());
    printLog_I ("Message: %s", commandPayload.c_str ());
}

void MQTTAdapter::SubMQTT ()
{
    const char *id = "subscriber-client";
    mMosq          = std::shared_ptr<struct mosquitto> (mosquitto_new (id, true, this), mosquitto_destroy);
    if (!mMosq)
    {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        return;
    }

    mosquitto_connect_callback_set (mMosq.get (),
    [] (struct mosquitto *mosq, void *userdata, int result)
    {
        auto *adapter = static_cast<MQTTAdapter *> (userdata);
        if (adapter)
        {
            adapter->connectToBroker (mosq, userdata, result);
        }
        else
        {
            std::cerr << "MQTTAdapter userdata is null in connect callback." << std::endl;
        }
    });

    mosquitto_message_callback_set (mMosq.get (),
    [] (struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
    {
        auto *adapter = static_cast<MQTTAdapter *> (userdata);
        if (adapter)
        {
            adapter->handleMessage (mosq, userdata, message);
        }
        else
        {
            std::cerr << "MQTTAdapter userdata is null in message callback." << std::endl;
        }
    });

    const char *host = "192.168.137.180";
    if (mosquitto_connect (mMosq.get (), host, 1883, 60) != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Failed to connect to broker: " << host << std::endl;
        return;
    }

    if (mosquitto_loop_start (mMosq.get ()) != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Failed to start Mosquitto loop." << std::endl;
        return;
    }

    printLog_I ("Waiting for connection to complete...");
}


void MQTTAdapter::messageCallback (struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
}

void MQTTAdapter::connectToBroker (struct mosquitto *mosq, void *userdata, int result)
{
    if (result == MOSQ_ERR_SUCCESS)
    {
        const char *topic     = "response/ecall";
        std::string flagTopic = topic;
        mosquitto_subscribe (mosq, NULL, topic, 0);
        printLog_I ("Connected to broker. Subscribing to topic: %s", flagTopic.c_str ());
    }
    else
    {
        std::cerr << "Failed to connect to broker. Reason: " << result << std::endl;
    }
}
void MQTTAdapter::disconnectToBroker (struct mosquitto *mosq, void *userdata, int rc)
{
    printLog_I ("Disconnected from broker. Reason: ", rc);
}
void MQTTAdapter::handleSignal (int signal)
{
    MQTTAdapter::running = false;
}
void MQTTAdapter::handleMessage (struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    try
    {
        std::string topic = message->topic;
        std::string payload ((char *)message->payload, message->payloadlen);

        printLog_I ("Received MQTT message on topic: %s, payload: %s", topic.c_str (), payload.c_str ());
        if (mOnMessageCallback)
        {
            std::lock_guard<std::mutex> lock (mCallbackMutex);
            mOnMessageCallback (topic, payload);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error processing message: " << e.what () << std::endl;
    }
}


const std::string MQTTAdapter::getResponseFromSub ()
{
    return mMessageResponse;
}
MQTTAdapter *MQTTAdapter::getInstance ()
{
    if (mInstanceMQTT == nullptr)
    {
        mInstanceMQTT = std::make_shared<MQTTAdapter> ();
    }
    return mInstanceMQTT.get ();
}

void MQTTAdapter::handleEventSub ()
{
    printLog_I ("State at MQTTSUB!!");

    auto mqttAdapter = MQTTAdapter::getInstance ();
    mqttAdapter->SubMQTT ();
    mqttAdapter->setOnMessageCallback (
    [this] (const std::string &topic, const std::string &payload)
    {
        printLog_I ("Callback: Received message on topic: %s, payload: %s", topic.c_str (), payload.c_str ());
        if (topic == "response/ecall")
        {
            nlohmann::json parsedPayload = nlohmann::json::parse (payload);
            if (parsedPayload.contains ("response"))
            {
                std::string response = parsedPayload["response"];
                mMessageResponse     = response;

                size_t findStatus = response.find ("confirmed");
                if (findStatus != std::string::npos)
                {
                    std::string getStatus = response.substr (findStatus);
                    printLog_I ("Get Status: %s", getStatus.c_str ());
                    HMIAdapter::getInstance ()->handleDataFromMQTT (getStatus);
                }
            }
            else
            {
                printLog_E ("Invalid payload: Missing 'response' field.");
            }
        }
        else
        {
            printLog_E ("Unhandled topic: %s", topic.c_str ());
        }
    });

    printLog_I ("MQTT subscription set and callback registered.");
}


void MQTTAdapter::setOnMessageCallback (const std::function<void (const std::string &topic, const std::string &payload)> &callback)
{
    mOnMessageCallback = callback;
}