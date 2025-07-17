#ifndef HANDLER_H
#define HANDLER_H

#include <vector>

#include "Model.h"
#include "View.h"

class EventHandler{

private:

    ModelDataHolder* data;
    ViewManager* view;

public:

    EventHandler(){

        data = new ModelDataHolder();
        view = new ViewManager();
    }

    ~EventHandler() {
        delete data;
        delete view;
    }

    void handleCommands(){

        bool gameRunning = true;
        json interactor = "storyteller"; 
        json interaction = "beginning";
        json with = "";  


    //Empty JSON + Print Start
        resetJSON(); 
        view->printView(data->getData(interactor, interaction, with));


    //GameLoop
        do{

            //UserInput =========================================================
                
            std::vector<std::string> uInput = getUserInput();

            //Check UserInput + set  ============================================================

            if(uInput[0] == "quit") break;

            if(uInput.size() == 2){

                if(setSentencePart(uInput[0], "verbs") != "" && setSentencePart(uInput[1], "interactors") != ""){

                    interaction = setSentencePart(uInput[0], "verbs");
                    interactor = setSentencePart(uInput[1], "interactors");
                    with = "";

                    view->printView(data->getData(interactor, interaction, with));
                    statusChanger(interactor, interaction, with);
                }else{

                    std::cout << std::endl;
                    view->typeWrite("You don't know how!!", 40);                
                }

            //Verb + Subject + (Preposition) + Object ===========================================
            }else if(uInput.size() == 4){

                if(setSentencePart(uInput[0], "verbs") != "" 
                && setSentencePart(uInput[1], "interactors") != ""
                && setSentencePart(uInput[3], "interactors") != ""){

                    interaction = setSentencePart(uInput[0], "verbs");
                    interactor = setSentencePart(uInput[1], "interactors");
                    with = (interaction == "combine") ? setSentencePart(uInput[3], "interactors") : "";

                    view->printView(data->getData(interactor, interaction, with));
                    statusChanger(interactor, interaction, with);
                }else{

                std::cout << std::endl;
                view->typeWrite("You don't know how!!!", 40);                  
                }
            }else{

                std::cout << std::endl;
                view->typeWrite("You don't know how!!!", 40);     
            }

            if(checkEndGame()){

                break;
            }       

        }while (true);

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

            case 50:

                data->combineItems(interactor.get<std::string>() , with.get<std::string>());
            return;

            case 99:

                data->changeEnd();
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

        return data->getEnd().get<std::string>() == "true";
    }

    std::vector<std::string> getUserInput(){

        std::string userInput = {}; 
        std::vector<std::string> inputVec{};
        view = new ViewManager();

        view->typeWrite("What do you want to do?", 40);
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

        if(inputVec.empty()){

            inputVec.push_back("");
        }

        return inputVec;
    }

};



#endif