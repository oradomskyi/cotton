#ifndef THREADMASTER_PARALLELBOOSTFIBER_H
#define THREADMASTER_PARALLELBOOSTFIBER_H

#include <thread>
#include <boost/fiber/all.hpp> // todo replace with only necessary includes
#include "../ThreadMaster.h"

using boost::fibers::fiber;
using boost::fibers::use_scheduling_algorithm;

using std::ref;
using std::move;
using std::thread;

namespace parallelboostfiber
{
    void master_fiber_routine(vector<Flood*>* floodsPtr);
}

class ParallelBoostFiber : public ThreadMaster
{
private:
    static const threadmaster::Type type = threadmaster::Type::PARALLEL_BOOSTFIBER;

public:
    ParallelBoostFiber(vector<Flood*>* _floodsPtr);
    ParallelBoostFiber(vector<Flood*>* _floodsPtr, int _n_threads);
    ~ParallelBoostFiber();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };
};

#endif
