//
// Created by Thomas Zayouna on 05/07/2020.
//
#ifndef STORE_ACTION_HPP
#define STORE_ACTION_HPP

#include <string>

struct Action {
    std::string type;
    Action(std::string typeStr) {
        type = typeStr;
    }
};

template<typename T>
struct InitAction : Action {
    T state;
    InitAction(T initState) : Action("@INIT") {
        state = initState;
        type = "@INIT";
    }
};

#endif //STORE_ACTION_H
