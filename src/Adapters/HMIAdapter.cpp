#include"HMIAdapter.h"
std::shared_ptr<HMIAdapter> HMIAdapter::mIntanceHMI = nullptr;

void HMIAdapter::handleReceivedCommand(int client_socket) {
    char buffer[1024] = {0};
    int valread = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (valread > 0) {
        std::string command(buffer);
        printLog_I("Receive command from client: %s",command.c_str());

        json command_json = json::parse(command);
        MQTTAdapter::getInstance()->sendMessage(&command_json);

        if (command_json.contains("command")) {
            std::string audioCommand = command_json["command"];
            AudioAdapter::getInstance()->handleLogicRunAudio(audioCommand);
        }

        json response = stringCommand(command);
        onHMIScreen(client_socket, response);
    } else if (valread == 0) {
        printLog_I("Client closed connection. Please reconnect!");
    } else {
        perror("Error receiving data from client");
    }
}

json HMIAdapter::stringCommand(const std::string& command) {
    json response;
    json command_json = json::parse(command);
    std::string actual_command = command_json["command"];
    if (actual_command == "ON") {
        response["status"] = "success";
        response["message"] = "LED turned on!";
    } else if (actual_command == "OFF") {
        response["status"] = "success";
        response["message"] = "LED turned off!";
    } else {
        response["status"] = "error";
        response["message"] = "Unknown command!";
    }
    return response;
}

void HMIAdapter::onHMIScreen(int client_socket, const json& response) {
    std::string jsonResponse = response.dump();
    ssize_t bytes_sent = send(client_socket, jsonResponse.c_str(), jsonResponse.size(), 0);

    if (bytes_sent == -1) {
        perror("Send response failed!!");
    } else {
        printLog_I("Send response to client: %s",jsonResponse.c_str());
    }
}

void HMIAdapter::initSocket()
{
    if ((server_fd = socket (AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror ("Socket failed");
        exit (EXIT_FAILURE);
    }
 
    int opt = 1;
    if (setsockopt (server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof (opt)))
    {
        perror ("setsockopt");
        close (server_fd);
        exit (EXIT_FAILURE);
    }
 
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons (SOCKET_PORT);
 
    if (bind (server_fd, (struct sockaddr *)&address, sizeof (address)) < 0)
    {
        perror ("Bind failed");
        close (server_fd);
        exit (EXIT_FAILURE);
    }
 
    if (listen (server_fd, 3) < 0)
    {
        perror ("Listen");
        close (server_fd);
        exit (EXIT_FAILURE);
    }
}

void HMIAdapter::runServerSocketHMI()
{
//    initSocket(); 
    while (true) {
    printLog_I ("Server running on port: %d", SOCKET_PORT);
 
    if ((client_socket = accept (server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror ("Accept");
        close (server_fd);
        exit (EXIT_FAILURE);
    }
    json response;
    handleReceivedCommand (client_socket);
   
    close (client_socket);
    }

    close(server_fd); 
}

HMIAdapter *HMIAdapter::getInstance()
{
    if(mIntanceHMI==nullptr)
    {
        mIntanceHMI = std::make_shared<HMIAdapter>();
    }
    return mIntanceHMI.get();
}
