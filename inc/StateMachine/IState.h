#ifndef ISTATE_H
#define ISTATE_H

#include <iostream>
#include <mutex>
#include <thread>
#include<chrono>
#include<condition_variable>
#include<memory>
#include<vector>
#include<queue>

#include "Logger.h"
#include"SimulateButton.h"
#include "ManagerMessage.h"
#include "EventData.h"

class IState
{
    private:
    public:
    virtual void handleAction ()    = 0;
    virtual void preEnterState ()   = 0;
    virtual void preReleaseState () = 0;
};
#endif
