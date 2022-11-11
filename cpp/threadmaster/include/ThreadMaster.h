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
	int n_threads;

    void setState(const threadmaster::State& new_state) { this->state = new_state; };

public:
    ThreadMaster(vector<Flood*>* _floodsPtr);
    ThreadMaster(vector<Flood*>* _floodsPtr, int _n_threads);
    virtual ~ThreadMaster();

    threadmaster::State getState() { return this->state; };
	vector<Flood*>* getFloodsPtr() { return this->floodsPtr; };
};

#endif
