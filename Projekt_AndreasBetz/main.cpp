#include <sstream>
#include <vector>


//Headers
#include "Headers/Handler.h"
#include "Headers/View.h"-+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


std::vector<std::string> getUserInput(){

    std::string userInput = {}; 
    std::vector<std::string> inputVec{};

    std::cout << "What do you want to do?";
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

void handleCommands(){

    EventHandler* event = new EventHandler();
    ViewManager* view = new ViewManager(0); //Start-State

    json interactor = "storyteller"; 
    json interaction = "beginning";
    json with = "";  


    event->resetJSON(); 
    view->printView(interactor, interaction, with);

    do{

//UserInput =========================================================
        

    std::vector<std::string> uInput = getUserInput();

//Logic ============================================================

    //Only Verb and Subject
    if(uInput.size() == 2){

        if(event->setSentencePart(uInput[0], "verbs") != "" && event->setSentencePart(uInput[1], "interactors") != ""){

            interaction = event->setSentencePart(uInput[0], "verbs");
            interactor = event->setSentencePart(uInput[1], "interactors");
            with = "";
        }else{

            std::cout << "Invalid Sentence!" << std::endl;                
        }

    //Verb + Subject + (Preposition) + Object 
    }else if(uInput.size() == 4){

        if(event->setSentencePart(uInput[0], "verbs") != "" 
        && event->setSentencePart(uInput[1], "interactors") != ""
        && event->setSentencePart(uInput[3], "interactors") != ""){

            interaction = event->setSentencePart(uInput[0], "verbs");
            interactor = event->setSentencePart(uInput[1], "interactors");
            with = (interaction == "combine") ? event->setSentencePart(uInput[3], "interactors") : "";
        }else{

            std::cout << "Invalid Sentence!" << std::endl;                
        }
    }else{

        std::cout << "Invalid Sentence!" << std::endl;
    }

    view->printView(interactor, interaction, with);
    event->statusChanger(interactor, interaction, with);


    }while (true);
}



int main(){


    handleCommands();

    return 0;
}   