#include <sstream>
#include <vector>


//Headers
#include "Headers/Handler.h"
#include "Headers/View.h"


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

    std::string interactor = "storyteller"; 
    std::string interaction = "beginning";
    std::string with = "";  


    do{

        view->printView(interactor, interaction, with);

        std::vector<std::string> uInput = getUserInput();

        if(uInput.size() == 2){

            if(event->setSentencePart(uInput[0], "verbs") != "" && event->setSentencePart(uInput[1], "interactors") != ""){

                interaction = event->setSentencePart(uInput[0], "verbs");
                interactor = event->setSentencePart(uInput[1], "interactors");
            }else{

                std::cout << "Invalid Sentence!" << std::endl;                
            }

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


    }while (true);
}


int main(){

    handleCommands();

    return 0;
}   


