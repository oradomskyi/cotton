#ifndef THREADMASTER_PARALLELBOOSTFIBER_H
#define THREADMASTER_PARALLELBOOSTFIBER_H

#include <boost/fiber/all.hpp> // todo replace with only necessary includes
#include "../ThreadMaster.h"

using boost::fibers::fiber;

class ParallelBoostFiber : public ThreadMaster
{
private:
    static const threadmaster::Type type = threadmaster::Type::PARALLEL_BOOSTFIBER;
    size_t n_fibers;
    vector<fiber> fibers;

public:
    ParallelBoostFiber(vector<Flood*>* _floodsPtr);
    ParallelBoostFiber(vector<Flood*>* _floodsPtr, int _n_threads);
    ~ParallelBoostFiber();

    void start();
    void stop();
    threadmaster::Type getType() { return this->type; };
};

#endif
