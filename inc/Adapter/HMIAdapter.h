#ifndef HMIADAPTER_H
#define HMIADAPTER_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include "json.hpp"  // Nlohmann JSON library
#include <cstring>
#include "Logger.h"
#include<thread>
#include<chrono>
#include "MQTTAdapter.h"
#include"AudioAdapter.h"
#include<condition_variable>
#include<mutex>

#define SOCKET_PORT 65432

using json = nlohmann::json;
class HMIAdapter
{
    private:
        int server_fd;
        int mClientSocket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        static std::shared_ptr<HMIAdapter> mIntanceHMI;
        std::string cachedDataVin;
        std::condition_variable dataReadyCv;
        bool dataReady;
        std::mutex cacheMutex;
        std::mutex mCommandMutex;

        std::string mSocketCommand;
        std::string mDataFromMQTT;
        std::mutex mSocketMutex;

    public:
        // HMIAdapter();
        // ~HMIAdapter();
        void initSocket();
        static HMIAdapter *getInstance(); 
        void runServerSocketHMI();
        void handleReceivedCommand();
        json stringCommand(const std::string& command);
        void onHMIScreen(const std::string& response);

        const std::string getSocketCommand();
        void clearSocketCommand();

        void handleDataFromMQTT(const std::string& data);

};
#endif