#pragma once
#include<memory>

class Application;

class ICommmandHandler{
public:
    virtual bool begin(Application* ) = 0;
    virtual bool end(Application*)=0;
    virtual bool add_command(Application*)=0;
    virtual bool end_of_f(Application*)=0;
};

using ICommmandHandlerPtr = std::unique_ptr<ICommmandHandler>;

class Application{
public:
    Application(int counter):counter(counter){}

    void set_current(ICommmandHandlerPtr hPtr){
        m_handler = std::move(hPtr);
    }
    bool begin(){
        return m_handler->begin(this);
    }
    bool end(){
        return m_handler->end(this);
    }
    bool end_of_f(){
        return m_handler->end_of_f(this);
    }
    bool add_command(){
        return m_handler->add_command(this);
    }

    int get_counter() const{
        return counter;
    }

private:
    ICommmandHandlerPtr m_handler;
    int counter;
};

class StaticState: public ICommmandHandler{
public:
    bool begin(Application* app) override;

    bool end(Application* ) override;

    bool add_command(Application* app) override;

    bool end_of_f(Application* ) override;

private:
    int counter = 0;
};

class DynamicState: public ICommmandHandler{
public:
    bool begin(Application*) override;
    bool end(Application* app) override;
    bool end_of_f(Application*) override;
    bool add_command(Application*) override;
    
private:
    int counter =1;
};





