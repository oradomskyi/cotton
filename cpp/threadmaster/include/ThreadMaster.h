#ifndef THREADMASTER_H
#define THREADMASTER_H

#include <vector>

#include "ThreadMasterInterface.h"
#include "../../flood/include/Flood.h"
#include "../../flood/include/methods/allmethods.h"

using std::vector;

class ThreadMaster : public ThreadMasterInterface
{
protected:
    threadmaster::State state;    
    vector<Flood*>* floodsPtr;
    void setState(const threadmaster::State& new_state) { this->state = new_state; };

public:
    ThreadMaster(vector<Flood*>* new_floodsPtr);
    virtual ~ThreadMaster();

    threadmaster::State getState() { return this->state; };
	vector<Flood*>* getFloodsPtr() { return this->floodsPtr; };
};

#endif
