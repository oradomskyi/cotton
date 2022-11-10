#ifndef THREADMASTER_PARALLELBOOSTFIBER_H
#define THREADMASTER_PARALLELBOOSTFIBER_H

#include <boost/fiber/all.hpp>
#include "../ThreadMaster.h"

class ParallelBoostFiber : public ThreadMaster
{
private:
    static const threadmaster::Type type = threadmaster::Type::PARALLEL_BOOSTFIBER;
	int n_threads;

public:
    ParallelBoostFiber(vector<Flood*>* new_floodsPtr);
    ParallelBoostFiber(vector<Flood*>* new_floodsPtr, const int& n_threads);
    ~ParallelBoostFiber();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };

};

#endif
