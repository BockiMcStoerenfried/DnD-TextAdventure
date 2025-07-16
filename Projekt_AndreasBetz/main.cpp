//Headers
#include "Headers/Handler.h"
#include "Headers/View.h"-+++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void handleCommands(){

    EventHandler* event = new EventHandler();
    ViewManager* view = new ViewManager(); //Start-State

    bool gameRunning = true;
    json interactor = "storyteller"; 
    json interaction = "beginning";
    json with = "";  


//Empty JSON + Print Start
    event->resetJSON(); 
    view->printView(interactor, interaction, with);


//GameLoop
    do{

        //UserInput =========================================================
            
        std::vector<std::string> uInput = event->getUserInput();

        //Check UserInput + set  ============================================================

        
        if(uInput.size() == 2){

            if(event->setSentencePart(uInput[0], "verbs") != "" && event->setSentencePart(uInput[1], "interactors") != ""){

                interaction = event->setSentencePart(uInput[0], "verbs");
                interactor = event->setSentencePart(uInput[1], "interactors");
                with = "";
            }else{

                std::cout << std::endl;
                view->typeWrite("I don't know how to do that!!", 40);                
            }

        //Verb + Subject + (Preposition) + Object ===========================================
        }else if(uInput.size() == 4){

            if(event->setSentencePart(uInput[0], "verbs") != "" 
            && event->setSentencePart(uInput[1], "interactors") != ""
            && event->setSentencePart(uInput[3], "interactors") != ""){

                interaction = event->setSentencePart(uInput[0], "verbs");
                interactor = event->setSentencePart(uInput[1], "interactors");
                with = (interaction == "combine") ? event->setSentencePart(uInput[3], "interactors") : "";
            }else{

            std::cout << std::endl;
              view->typeWrite("I don't know how to do that!!", 40);                  
            }
        }else{

            std::cout << std::endl;
            view->typeWrite("I don't know how to do that!!", 40);     
        }

        if(uInput[0] == "quit") break;

        view->printView(interactor, interaction, with);
        event->statusChanger(interactor, interaction, with);

        if(event->checkEndGame()){

            break;
        }       

    }while (true);

    delete event;
    delete view;
}



int main(){

    handleCommands();

    return 0;
}   