#pragma once 

#include "Observer.h"
#include "Storage.h"
#include <atomic>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <queue>

class CommandView:public Observer{
public: 
    CommandView(std::shared_ptr<Storage> store, std::ostream& out = std::cout):store(store),out_stream(out),
    thread_executer(&CommandView::execute,this){
        store.get()->addObserver(this);
    }
    
    ~CommandView(){
        count = true;
        commands_wait.notify_all();
        if(thread_executer.joinable()){
            thread_executer.join();
        }
    }

    void update(const std::deque<Element>& cont) override{
        if(!start_thread){ 
        std::unique_lock<std::mutex>lock(lock_viewer);
        wait_thread.wait(lock,[&](){return start_thread==true;});
        }

        {std::lock_guard<std::mutex> lock(lock_viewer);
        container.push(cont);}
        commands_wait.notify_one();
    }

    void print(const std::deque<Element>& temp_c){
        std::lock_guard<std::mutex>locker(print_lock);
        if(!temp_c.empty()){
        out_stream<<"bulk: "<<temp_c[0]._cmd;
            for(size_t i=1;i<temp_c.size();++i){
                out_stream<<", "<<temp_c[i]._cmd;
            }
            out_stream<<'\n';
        }
    }
     
    void execute(){
        while(count==false){
            if(start_thread==false){
            start_thread = true;
            wait_thread.notify_all();
            }
            std::unique_lock<std::mutex>locker(lock_viewer);
            commands_wait.wait(locker,[&](){return !container.empty()||count==true;});
            locker.unlock();
            while(!container.empty()){
                lock_viewer.lock();
                std::deque<Element> temp_c = container.front();
                container.pop();
                lock_viewer.unlock();
                print(temp_c); 
            }
        }
    }
private:
    std::shared_ptr<Storage> store;
    std::mutex lock_viewer;
    std::condition_variable commands_wait;
    std::queue<std::deque<Element>> container;
    std::thread thread_executer;
    std::mutex print_lock;
    std::atomic<bool> count=false;
    std::atomic<bool> start_thread = false;
    std::condition_variable wait_thread;
    std::ostream& out_stream;
};