#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

#include "../base/mutex.h"

using namespace std;
using namespace boost;

class StockFactory : public boost::enable_shared_from_this<StockFactory>, boost::noncopyable
{
public:
    shared_ptr<Stock> get(const string &key)
    {
        shared_ptr<Stock> pstock;
        Mutex::Locker lock(mutex_);
        weak_ptr<Stock> wstock = stocks_[key];
        pstock = wstock.lock();
        if (!pstock)
        {
            pstock.reset(new Stock(key), boost::bind(&StockFactory::weakDeleteCallback, boost::weak_ptr<StockFactory>(shared_from_this()), -1))
            wstock = pstock;
        }

        return pstock;
    }

    
private:
    Mutex mutex_;
    map<string, weak_ptr<Stock> > stocks_;
};
