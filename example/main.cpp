//
// Created by Thomas Zayouna on 05/07/2020.
//
#include <iostream>
#include <store/Store.hpp>
#include <store/StoreSubscriber.hpp>

struct MyState {
    int count;
};

const std::string INCREMENT_ACTION = "[INCREMENT] Here comes the increment action";
const std::string DECREMENT_ACTION = "[INCREMENT] Here comes the decrement action";

struct Increment : Action {
    Increment() : Action(INCREMENT_ACTION) {}
};

struct Decrement : Action {
    Decrement() : Action(DECREMENT_ACTION) {}
};

MyState reducer(Action action, MyState state) {
    return state;
}

class MyStateStoreSubscriber : public StoreSubscriber<MyState> {
public:
    void newState(MyState newState) {
        std::cout << newState.count << std::endl;
    }
};

const std::map<std::string, Reducer<MyState>> REDUCER({
    { INCREMENT_ACTION, [](Action action, MyState state) {
        state.count++;
        return state;
    }},
    { DECREMENT_ACTION, [](Action action, MyState state) {
        state.count--;
        return state;
    }}
});

int main() {
    MyState initialState = { 0 };
    Store<MyState> store = createStore(
            createReducer<MyState>(REDUCER),
            initialState,
            std::vector<Effect<MyState> >({
                [](Action action, DispatchFunction dispatch, MyState state) {
                    if (action.type == INCREMENT_ACTION) {
                        dispatch(Decrement());
                    }
                }
            })
        );
    MyStateStoreSubscriber* sub = new MyStateStoreSubscriber;
    store.subscribe(sub);
    store.dispatch(Increment());
    //store.dispatch(Decrement());
    store.unsubscribe(sub);
    return 0;
}
