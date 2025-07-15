#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include "Model.h"


class ViewManager{

private:

    ModelDataHolder* data;

public:

    ViewManager(int state){

        data = new ModelDataHolder();
    }

    //To Do - JSON-Format muss festgelegt werden
    void printView(std::string interactor, std::string interaction, std::string with){

        //variable = (condition) ? expressionTrue : expressionFalse;
        std::cout << data->getData(interactor, interaction, with) << std::endl;
    }

};


#endif