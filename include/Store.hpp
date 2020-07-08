//
// Created by Thomas Zayouna on 05/07/2020.
//
#ifndef STORE_STORE_HPP
#define STORE_STORE_HPP
#include <vector>
#include <map>
#include <store/Action.hpp>
#include <store/Effect.hpp>
#include <store/StoreSubscriber.hpp>

template<typename T>
using Reducer = std::function<T(Action,T)>;
template<typename T>
using ReducerMap = std::map<std::string, Reducer<T>>;

template<typename T>
struct StoreConfiguration {
public:
    T initialState;
    Reducer<T> reducer;
    std::vector<Effect<T> > effects;
};

template<typename T>
class Store {

public:

    T state;

    Store<T>(StoreConfiguration<T> storeConfiguration) {
        this->reducer = storeConfiguration.reducer;
        this->state = storeConfiguration.initialState;
        for(auto effect : storeConfiguration.effects) {
            this->effects.push_back(effect);
        }
    }

    void subscribe(StoreSubscriber<T> * storeSubscriber) {
        this->subscribers.push_back(storeSubscriber);
        storeSubscriber->newState(this->state);
    }

    void unsubscribe(StoreSubscriber<T>* storeSubscriber) {
        auto it = this->subscribers.begin();
        while (it != this->subscribers.end()) {
            if (*it == storeSubscriber) {
                it = this->subscribers.erase(it);
            } else {
                ++it;
            }
        }
    }

    void dispatch(Action action) {
        this->state = this->reducer(action, this->state);
        for (auto sub: this->subscribers) {
            sub->newState(this->state);
        }
        this->runEffects(action);
    }

private:
    Reducer<T> reducer;
    std::vector<Effect<T> > effects;
    std::vector<StoreSubscriber<T>*> subscribers;

    void runEffects(Action action) {
        for(auto effect : this->effects) {
            std::bind(effect, action, [this] (Action action) { this->dispatch(action); }, this->state)();
        }
    }
};

template<typename T>
Store<T> createStore(
        Reducer<T> reducer,
        T initialState,
        std::vector<Effect<T> > effects = std::vector<Effect<T> >()
) {
    StoreConfiguration<T> CONFIG({initialState, reducer, effects});
    auto store = Store<T>(CONFIG);
    auto initAction = InitAction<T>(initialState);
    store.dispatch(initAction);
    return store;
}

template<typename T>
T reduce(Action action, T state) {
    std::cout << action.type;
    return state;
}

template<typename T>
Reducer<T> createReducer(ReducerMap<T> reducerMap) {
    auto handler = [reducerMap] (Action a, T s) {
        if (reducerMap.count(a.type) == 0) {
            return s;
        }
        return reducerMap.find(a.type)->second(a, s);
    };
    return handler;
}
#endif //STORE_STORE_H
