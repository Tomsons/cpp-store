//
// Created by Thomas Zayouna on 05/07/2020.
//

#ifndef STORE_STORESUBSCRIBER_HPP
#define STORE_STORESUBSCRIBER_HPP

template<typename T>
class StoreSubscriber {
public:
    virtual void newState(T newState) {}
};

#endif //STORE_STORESUBSCRIBER_H
