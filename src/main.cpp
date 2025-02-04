#include "AudioAdapter.h"
#include "EventTable.h"
#include "HMIAdapter.h"
#include "IState.h"
#include "MQTTAdapter.h"

void handle ()
{

    HMIAdapter::getInstance ()->initSocket ();
    HMIAdapter::getInstance ()->runServerSocketHMI ();
}
int main ()
{
    std::thread threadMQTT;
    threadMQTT = std::thread([]() {
        MQTTAdapter::getInstance()->handleEventSub();
    });

    threadMQTT.detach();

    // MQTTAdapter::getInstance()->handleEventSub();

    ManagerMessage::getInstance ()->startThreadMessage ();
    ManagerMessage::getInstance ()->registerEventHandler (EventTable::getInstance ()->getEventStateFunction ());
    IDLEState::getInstance ()->preEnterState ();
    SimutaleButton::getInstance ()->startInputThread ();
    handle();
    while (true)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds (100));
    }

    return 0;
}