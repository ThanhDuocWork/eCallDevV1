#include "IDLEState.h"

std::shared_ptr<IDLEState> IDLEState::mInstanceIDLE = nullptr;
IDLEState::IDLEState () : mFlag (false)
{
}
IDLEState::~IDLEState ()
{
}
IDLEState *IDLEState::getInstance ()
{
    if (mInstanceIDLE == nullptr)
    {
        mInstanceIDLE = std::make_shared<IDLEState> ();
    }
    return mInstanceIDLE.get ();
}
void IDLEState::preEnterState ()
{
    printLog_I ("State at IDLEState preEnterState!!");
    std::shared_ptr<EventIDLE> eventIDLE = std::make_shared<EventIDLE> (static_cast<uint32_t> (MESSAGE_EVENT::ENUM_ESTATE_MESSAGE::eState_IDLE_Enter));
    printLog_I ("Wait for user press SOS Button!!");
    eventIDLE->setData ("Enter_IDLE_State");
    ManagerMessage::getInstance ()->addEventData (eventIDLE);
    // stop Audio by HandleAction_CancelTimer_State_LongPress
    // std::lock_guard<std::mutex> audioLock (AudioAdapter::getInstance ()->getMutex ());
    // AudioAdapter::getInstance ()->stopAudio ();
}
void IDLEState::handleAction ()
{
    printLog_I ("State at IDLEState handleAction!!");
    std::shared_ptr<EventIDLE> eventIDLE = std::make_shared<EventIDLE> (static_cast<uint32_t> (MESSAGE_EVENT::ENUM_ESTATE_MESSAGE::eState_IDLE_Action));
    if (!mFlag)
    {
        mThreadEventIDLE = std::thread (
        [this, eventIDLE] ()
        {
            std::unique_lock<std::mutex> lock (mMutex);
            while (!mFlag)
            {
                std::string key = HMIAdapter::getInstance ()->getSocketCommand ();
                // printLog_I("value Key: %s",key.c_str());
                if (key == "ON")
                {
                    // HMIAdapter::getInstance ()->clearSocketCommand ();
                    printLog_I ("------------------------");
                    printLog_I ("User press button SOS!!!");
                    printLog_I ("Detect short Press!! -> Play (Audio 1) -> turn ON led SOS!!!");
                    //***bug audio run than more 3s
                    std::lock_guard<std::mutex> audioLock (AudioAdapter::getInstance ()->getMutex ());
                    AudioAdapter::getInstance ()->stopAudio ();
                    AudioAdapter::getInstance ()->handleLogicAudioCommandHMI (key);

                    printLog_I ("------------------------");
                    mFlag = true;
                    mCondition.notify_all ();
                    break;
                }
                std::this_thread::sleep_for (std::chrono::milliseconds (500));
            }
            eventIDLE->setData ("HandleAction_IDLE_State");
            ManagerMessage::getInstance ()->addEventData (eventIDLE);
        });
        mThreadEventIDLE.detach ();
    }
    std::unique_lock<std::mutex> lock (mMutex);
    mCondition.wait (lock, [this] { return mFlag; });
    // printLog_I ("Variable mFlag: %s", mFlag ? "True" : "False");
}

void IDLEState::preReleaseState ()
{
    printLog_I ("State at IDLEState preReleaseState!!");
    mFlag                                = false;
    std::shared_ptr<EventIDLE> eventIDLE = std::make_shared<EventIDLE> (static_cast<uint32_t> (MESSAGE_EVENT::ENUM_ESTATE_MESSAGE::eState_IDLE_Release));
    eventIDLE->setData ("Release_IDLE_State");
    ManagerMessage::getInstance ()->addEventData (eventIDLE);
}