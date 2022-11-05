#include "../../include/masters/Serial.h"

Serial::Serial(vector<Flood*>* new_floodsPtr)
    : ThreadMaster(new_floodsPtr)
{
    this->setState(threadmaster::State::READY);
}

Serial::~Serial()
{}

void Serial::start()
{
    this->setState(threadmaster::State::RUNNING);
    
    //while(this->state != threadmaster::State::HALT)
    {
        for(Flood* flood : *(this->floodsPtr))
        {
        	flood->enable();
        	flood->run();
        }
    }
}

void Serial::stop()
{
    for(Flood* flood : *(this->floodsPtr))
            flood->disable();
    
    this->setState(threadmaster::State::HALT);
}

