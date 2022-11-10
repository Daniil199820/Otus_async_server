#pragma once 

#include<string>
#include<memory>
#include<iostream>
#include "Storage.h"
#include "State_machine.h"


class CommandModel{
private:
    std::string _command;
    
    std::unique_ptr<Application> app;

    std::shared_ptr<Storage> store;


    void begin(){
        if(!app.get()->begin()){
            store.get()->pull_commands();
        }
    }

    void end(){
        if(!app.get()->end()){
            store.get()->pull_commands();
        }
    }

    void add_command(const std::string& cur_command){
        if(app.get()->add_command()){
            store.get()->add_command(cur_command);
        }
        else{
            store.get()->add_command(cur_command);
            store.get()->pull_commands();
        }
    }

    
public:
     CommandModel(std::unique_ptr<Application> app, std::shared_ptr<Storage> store):app(std::move(app)),store(store){
        app.get()->set_current(ICommmandHandlerPtr{new StaticState()});
    }

    void end_of_f(){
        if(!app->end_of_f()){
            store->pull_commands();
            }
    }

    CommandModel(int block_size, std::shared_ptr<Storage> store):store(store){
        app = std::make_unique<Application>(block_size);  
        app.get()->set_current(ICommmandHandlerPtr{new StaticState()});
    }

    Storage* get_ref_store(){
        return store.get();
    }

    int setCommand(const std::string& cur_command){

        if(cur_command==""){
             return 0;
        }

        if(cur_command == "{"){
            begin();
            return 0;
        }

        if(cur_command == "}"){
            end();
            return 0;
        }

        add_command(cur_command);
                
        return 0;
    }

    std::string getCommand() const{
        return _command;
    }
};

