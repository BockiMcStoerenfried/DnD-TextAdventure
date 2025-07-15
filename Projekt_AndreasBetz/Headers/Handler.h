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


    std::string setSentencePart(std::string word, std::string type){

        return data->getJSONState(word, type);
    }

    // void writeJSON(){}


};



#endif