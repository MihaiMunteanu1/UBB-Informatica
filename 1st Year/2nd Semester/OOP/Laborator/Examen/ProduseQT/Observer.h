#pragma once
#include <algorithm>
#include <vector>
using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
protected:
    void notify() {
        for (auto& obs : observers) {
            obs->update();
        }
    }
};