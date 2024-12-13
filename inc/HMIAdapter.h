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
#define SOCKET_PORT 65432

using json = nlohmann::json;
class HMIAdapter
{
    private:
        int server_fd, client_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        static std::shared_ptr<HMIAdapter> mIntanceHMI;
        
        
    public:
        void initSocket();
        static HMIAdapter *getInstance(); 
        void runServerSocketHMI();
        void handleReceivedCommand(int client_socket);
        json stringCommand(const std::string& command);
        void onHMIScreen(int client_socket, const json& response);
};
#endif