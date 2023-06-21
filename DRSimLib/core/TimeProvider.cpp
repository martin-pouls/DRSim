#include "include/drsim/TimeProvider.h"

namespace drsim {

void TimeProvider::registerTimeObserver(TimeObserver* observer) {
    observers.push_back(observer);
}

void TimeProvider::notifyTimeObservers() {
    for (auto* observer : observers) {
        observer->updateTime(getTime());
    }
}

} // namespace drsim