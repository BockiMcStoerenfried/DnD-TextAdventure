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

 
    void printView(json interactor, json interaction, json with){

        json printFile =  data->getData(interactor, interaction, with);

        std::cout << printFile[0] << std::endl;


    }
};


#endif