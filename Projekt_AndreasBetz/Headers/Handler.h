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

    //
    json setSentencePart(std::string word, std::string type){


        return data->getJSONState(word, type);
    }

    void statusChanger(json interactor, json interaction, json with){

        json changer = data->getData(interactor, interaction, with);
        
        switch(changer[1].get<int>()){

            case 1:
                if(with != ""){
                    data->changeJSONState(with, "dead");    
                }else{
                    data->changeJSONState(interactor, "dead");
                }

            return;

            case 2:
                if(with != ""){
                    data->changeJSONState(with, "broken");    
                }else{
                    data->changeJSONState(interactor, "broken");
                }
            return;

            default:
                return;


        }

    }

    void resetJSON(){


        json file = data->getFile("JSON/baseInteractors.json");
        json file2 = data->getFile("JSON/baseVerbs.json");

        std::ofstream offFile("JSON/interactors.json");
        offFile << file;

        std::ofstream offFile2("JSON/verbs.json");
        offFile2 << file2;
    }

};



#endif