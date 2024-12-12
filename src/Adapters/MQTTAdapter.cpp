#include "MQTTAdapter.h"
std::shared_ptr<MQTTAdapter> MQTTAdapter::mInstanceMQTT = nullptr;
MQTTAdapter::MQTTAdapter() {
    mosquitto_lib_init();
}

MQTTAdapter::~MQTTAdapter() {
    mosquitto_lib_cleanup();
}

void MQTTAdapter::PubMQTT() {
    const char *id = "publisher-client";
    struct mosquitto *mosq = mosquitto_new(id, true, NULL);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client." << std::endl;
        return;
    }

    const char *host = "localhost";
    u_int32_t port = 1883;
    u_int32_t timeLive = 60;

    if (mosquitto_connect(mosq, host, port, timeLive) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker." << std::endl;
        mosquitto_destroy(mosq);
        return;
    }

    const char *message = "Hello from Publisher!";
    const char *toppic = "example/topic";

    if (mosquitto_publish(mosq, NULL, toppic, strlen(message), message, 1, true) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to publish message." << std::endl;
        mosquitto_destroy(mosq);
        return;
    }

    std::cout << "Message published to topic 'example/topic'." << std::endl;
    mosquitto_destroy(mosq);
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

    std::cout << "Subscribed to topic 'example/topic'. Waiting for messages..." << std::endl;
    int mosquittoLoop = mosquitto_loop_forever(mosq, -1, 1);
    if(mosquittoLoop != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Error in MQTT loop: " << mosquitto_strerror(mosquittoLoop) << std::endl;
    }
    mosquitto_destroy(mosq);
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
    std::string topic = message->topic;
    std::string payload = (char *)message->payload;

    std::cout << "Received message on topic '" << topic << "': " << payload << std::endl;

    CURL *curl = curl_easy_init();
    if (curl) {
        const char *url = "http://localhost:3000/api/endpoint";
        curl_easy_setopt(curl, CURLOPT_URL, url);

        std::string json_payload = "{\"topic\": \"" + topic + "\", \"message\": \"" + payload + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());

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
                std::cout << "Data sent to server successfully!" << std::endl;
            } else {
                std::cerr << "Failed to send data. HTTP Response Code: " << response_code << std::endl;
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
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