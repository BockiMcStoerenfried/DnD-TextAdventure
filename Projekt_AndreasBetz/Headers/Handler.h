#ifndef HANDLER_H
#define HANDLER_H

#include "Model.h"

class EventHandler{

private:

    ModelDataHolder* data;

public:

    EventHandler(){

        data = new ModelDataHolder();
    }

    int setVerb(std::string verb){

        int verbState = data->getEventState(verb);
        //calls actions that change JSON
        if(verbState != 0){

            return verbState;
        } else{
            return 0;
        }
    }
};



#endif