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
        iss >> temp;
        inputVec.push_back(temp);
    } while(iss);

    return inputVec;
}

void handleCommands(){

    EventHandler* event = new EventHandler();
    ViewManager* view = new ViewManager(0); //Start-State

    int viewType = 1;
    int viewState = 0;

    do{

        view->printView(viewType, viewState);

        std::vector<std::string> uInput = getUserInput();

        if(event->setVerb(uInput[0]) != 0){

            //change viewType & viewState

        }else{

            std::cout   << "Invalid sentence or verb! \n" 
                        << "Remember: A sentence has to start with a valid verb!"
                        << std::endl;
        }

    }while (true);
}


int main(){

    handleCommands();

    return 0;
}   


