#ifndef CENTERSTATE_H
#define CENTERSTATE_H
#include "IState.h"
#include "EventTable.h"
#include "MQTTAdapter.h"
class CenterState : public IState
{
    private:
    static std::shared_ptr<CenterState> mInstance;
    public:
    CenterState();
    ~CenterState();
    static CenterState *getInstance();
    void handleAction () override;
    void preEnterState () override;
    void preReleaseState () override;
};

class EventCenter : public EventData
{
    private:
    std::string mDataStringCenter;
    public:
    EventCenter(uint32_t messageID) : EventData(messageID)
    {

    }
    void setData(const std::string data)
    {
        mDataStringCenter = data;
    }
    const std::string getData()
    {
        return mDataStringCenter;
    }
};

#endif