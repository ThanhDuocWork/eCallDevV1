#include "AudioAdapter.h"
#include "HMIAdapter.h"
#include "MQTTAdapter.h"

void handle()
{
    std::string input;
    std::cin>>input;
    if(input == "s")
    {
        HMIAdapter::getInstance()->initSocket();
        HMIAdapter::getInstance()->runServerSocketHMI();
    }
    else 
    {
        printLog_I("input valid!!");
    }
}
int main(){ 
    
    while (true)
    {
        printLog_I("Press:"); 
        handle();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return 0;
}