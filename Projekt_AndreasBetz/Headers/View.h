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
    void printView(int viewType, int viewState){

        std::cout << data->getData(viewType, viewState) << std::endl;
    }

};


#endif