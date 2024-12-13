#include "MQTTAdapter.h"
std::shared_ptr<MQTTAdapter> MQTTAdapter::mInstanceMQTT = nullptr;
MQTTAdapter::MQTTAdapter() {
    mosquitto_lib_init();
}

MQTTAdapter::~MQTTAdapter() {
    mosquitto_lib_cleanup();
}
void MQTTAdapter::sendMessage(const json *Message)
{
   MQTTAdapter::PubMQTT(*Message);
}
void MQTTAdapter::PubMQTT(const json &command_json) {
    const char *id = "publisher-client";
    std::shared_ptr<struct mosquitto> mosq(
        mosquitto_new(id, true, NULL),
        mosquitto_destroy 
    );
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        return;
    }

    const char *host = "localhost";
    u_int32_t port = 1883;
    u_int32_t timeLive = 60;

    if (mosquitto_connect(mosq.get(), host, port, timeLive) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker." << std::endl;
        return;
    }

    //const char *message = "Hello from Publisher!";
    std::string message = command_json.dump();
    const char *toppic = "ecall/topic";

    if (mosquitto_publish(mosq.get(), NULL, toppic, message.size(), message.c_str(), 1, true) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to publish message." << std::endl;
        return;
    }

    printLog_I("Message published to topic 'example/topic'." );
}

void MQTTAdapter::SubMQTT() {
    const char *id = "subscriber-client";
    struct mosquitto *mosq = mosquitto_new(id, true, this);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        return;
    }

    mosquitto_message_callback_set(mosq, MQTTAdapter::messageCallback);
    mosquitto_disconnect_callback_set(mosq, MQTTAdapter::onDisconnectCallback);  
    
    const char *host = "localhost";
    u_int32_t port = 1883;
    u_int32_t timeLive = 60;  

    if (mosquitto_connect(mosq, host, port, timeLive) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker." << std::endl;
        mosquitto_destroy(mosq);
        return;
    }

    const char *toppic = "example/topic";
    if (mosquitto_subscribe(mosq, NULL, toppic, 0) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to subscribe to topic." << std::endl;
        mosquitto_destroy(mosq);
        return;
    }

    printLog_I("Subscribed to topic 'example/topic'. Waiting for messages...");
    
    std::thread([mosq]() {
        if (mosquitto_loop_forever(mosq, -1, 1) != MOSQ_ERR_SUCCESS) {
            std::cerr << "Error in MQTT loop." << std::endl;
        }
        mosquitto_destroy(mosq);
    }).detach();

}
void MQTTAdapter::messageCallback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    MQTTAdapter *adapter = static_cast<MQTTAdapter *>(userdata);
    if (!userdata || !message) {
        std::cerr << "Invalid userdata or message in callback!" << std::endl;
        return;
    }
    if (adapter) {
        adapter->handleMessage(mosq, userdata, message);
    }
}
void MQTTAdapter::onDisconnectCallback(struct mosquitto *mosq, void *userdata, int rc) {
    MQTTAdapter *adapter = static_cast<MQTTAdapter *>(userdata);
    if (adapter) {
        std::cerr << "Disconnected from broker! Reason code: " << rc << std::endl;
    }
}
void MQTTAdapter::handleMessage(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    try {
        std::string topic = message->topic;
        std::string payload = std::string((char *)message->payload, message->payloadlen);

        printLog_I("Received message on topic: %s payload: %s", topic.c_str(), payload.c_str());

        // Khởi tạo cURL
        CURL *curl = curl_easy_init();
        if (curl) {
            const char *url = "http://localhost:3000/api/endpoint";
            curl_easy_setopt(curl, CURLOPT_URL, url);

            // Đảm bảo JSON payload đúng định dạng
            json json_payload = {
                {"topic", topic},
                {"message", json::parse(payload)} // Parse payload thành JSON nếu cần
            };
            std::string json_str = json_payload.dump();

            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            } else {
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                if (response_code == 200) {
                    printLog_I("Data sent to server successfully!");
                } else {
                    std::cerr << "Failed to send data. HTTP Response Code: " << response_code << std::endl;
                }
            }

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception in handleMessage: " << e.what() << std::endl;
    }
}



MQTTAdapter *MQTTAdapter::getInstance()
{
    if(mInstanceMQTT==nullptr)
    {
        mInstanceMQTT = std::make_shared<MQTTAdapter>();
    }
    return mInstanceMQTT.get();
}