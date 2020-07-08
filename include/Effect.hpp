//
// Created by Thomas Zayouna on 05/07/2020.
//

#ifndef STORE_MIDDLEWARE_HPP
#define STORE_MIDDLEWARE_HPP

typedef std::function<void(Action)> DispatchFunction;

template<typename T>
using Effect = std::function<void(Action,DispatchFunction,T)>;

#endif //STORE_MIDDLEWARE_H
