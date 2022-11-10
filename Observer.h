#pragma once
#include<vector>
#include<thread>
#include<mutex>
#include<deque>
#include<string>


struct Element{
std::string _cmd;
int64_t _time;
};

class Observer{
public:
    virtual void update(const std::deque<Element>&) = 0;
};

class Observable{
public:
    void addObserver(Observer* observer){
        _observers.push_back(observer);
    }

    void notifyUpdate(const std::deque<Element>& temp_cont){
        for(unsigned int i=0;i<_observers.size();++i){
            _observers[i]->update(temp_cont);
        }
    }
private:
    std::vector<Observer*>_observers;   
    std::mutex lock_actions_command; 
};