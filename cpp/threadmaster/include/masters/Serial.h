#ifndef THREADMASTERSERIAL_H
#define THREADMASTERSERIAL_H

#include "../ThreadMaster.h"

class Serial : public ThreadMaster
{
private:
    static const threadmaster::Type type = threadmaster::Type::SERIAL;
public:
    Serial(vector<Flood*>* _floodsPtr);
    ~Serial();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };
};

#endif
