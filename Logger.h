#pragma once  

#include <fstream>
#include <string>
#include "Observer.h"
#include "Storage.h"
#include <condition_variable>
#include <memory>
#include <thread>
#include <vector>
#include <queue>
#include<atomic>
#include <sstream>
#include <map>
class Logger: public Observer{
public:
    Logger(std::shared_ptr<Storage> store):store(store){
        store.get()->addObserver(this);

        for(size_t i=1;i<3;++i){
            check_thr_maps[i] = false;
            threads.emplace_back(std::thread(&Logger::execute,this,i));
        }
    }

    ~Logger(){
        count = true;
        commands_wait.notify_all();
        for(auto& cur_thread:threads){
            if(cur_thread.joinable()){
                cur_thread.join();
            }
        }
    }

    void update(const std::deque<Element>& cont) override{
        if(!start_thread){ 
        std::unique_lock<std::mutex>lock(lock_viewer);
        wait_thread.wait(lock,[&](){return start_thread==true;});
        }
        {std::lock_guard<std::mutex> lock(lock_viewer);
        container.push(cont);}
        commands_wait.notify_all();
    }
    
    void execute(const size_t& thread_name){
        while(count==false){

            if(start_thread==false){
                std::lock_guard<std::mutex>lock3(lock_viewer);
                check_thr_maps[thread_name] = true;
                start_thread = true;
                for(auto& it:check_thr_maps){
                    start_thread = start_thread&&it.second;
                    if(start_thread){
                        start_thread = true;
                        wait_thread.notify_one();
                    }
                }
            }
            
            std::unique_lock<std::mutex>locker(lock_viewer);
            commands_wait.wait(locker,[&](){return !container.empty()||count==true;});
            while(!container.empty()){
                std::deque<Element> temp_c = container.front();
                container.pop();
                print(temp_c,thread_name);
            }
        }
    }

    void SetContextName(void* CntxName){
        ContextName = CntxName;
    }

private:
    std::ofstream file;
    std::atomic<bool> flag_opened_file = false;
    std::shared_ptr<Storage> store;
    std::mutex lock_viewer;
    std::condition_variable commands_wait;
    std::queue<decltype(store->container_commands)> container;
    std::thread thread_executer;
    std::mutex print_lock;
    void* ContextName;
    std::vector<std::thread> threads;
    std::atomic<bool> count=false;
    std::atomic<bool> start_thread = {false};
    std::condition_variable wait_thread;
    std::atomic<int> counter = {0};
    std::mutex dd;
    std::map<size_t,bool> check_thr_maps;

    void open_log(const std::string& filename){
       
        close_log();
        file.open(filename,std::ios::out);
        flag_opened_file = true;
    }

    void write(const std::string& message){
        if(flag_opened_file){
            file << message << "\n";
        }
    }

    void close_log(){
        if(flag_opened_file){
            file.close();
            flag_opened_file = false;
        }
    }

    void print(const std::deque<Element>& temp_c,const size_t& thread_name){
        if(!temp_c.empty()){
            std::stringstream file_name;
            file_name<<"bulk_"<<temp_c[0]._cmd <<"_"<<"file"<<thread_name <<"_"<<ContextName<<"_"<<std::to_string(temp_c[0]._time)<<".log";
            open_log(file_name.str());
            write(temp_c[0]._cmd); 
            for(size_t i=1;i<temp_c.size();++i){
                write(temp_c[i]._cmd);
            }
            close_log(); 
        }
    } 

};