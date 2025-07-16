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

    bool checkEndGame(){

        return data->getData("storyteller", "endState", "").get<std::string>() == "end";

        return false;

    }

    std::vector<std::string> getUserInput(){

        std::string userInput = {}; 
        std::vector<std::string> inputVec{};

        std::cout << "What do you want to do?" << std::endl;
        std::getline(std::cin, userInput);

        std::istringstream iss(userInput);

        do{

            std::string temp;
            std::string temp2 = "";
            iss >> temp;

            for(char x : temp){
                
                temp2 += std::tolower(x);
            }

            if(temp2 != "")
                inputVec.push_back(temp2);

        } while(iss);

        return inputVec;
    }


};



#endif