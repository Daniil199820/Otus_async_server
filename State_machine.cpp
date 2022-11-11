#include "State_machine.h"

bool StaticState::begin(Application* app){
        app-> set_current(ICommmandHandlerPtr{new DynamicState()});
        return false;
    } 

bool StaticState::end(Application* ){ return true;}

bool StaticState::add_command(Application* app){
        ++counter;
        if(counter>(app->get_counter()-1)){
            counter = 0;
            return false;
        }
        return true;
    }

bool StaticState::end_of_f(Application*){
    return false;
}

int StaticState::get_status(Application*){
    return Static_status;
}

bool DynamicState::begin(Application* ){
    ++counter;
    return true;
} 

bool DynamicState::end(Application* app){ 
    --counter;
    if(counter==0){   
        app-> set_current(ICommmandHandlerPtr{new StaticState()});
        return false;
    }
    return true;
}

bool DynamicState::add_command(Application* app){
    return true;
}

bool DynamicState::end_of_f(Application*){
    return true;
}

int DynamicState::get_status(Application*){
    return Dynamic_status;
}

