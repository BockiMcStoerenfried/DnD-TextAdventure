#ifndef VIEW_H
#define VIEW_H

#include <chrono>
#include <thread>
#include <iostream>

class ViewManager{

private:

    ModelDataHolder* data;

public:

    void typeWrite(const std::string& text, int delayMs = 50) {
        for (char c : text) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
        std::cout << std::endl;
    }

    void printView(json printFile){

        std::cout << "\n" << std::endl;
        typeWrite(printFile[0], 40);
    }
};


#endif