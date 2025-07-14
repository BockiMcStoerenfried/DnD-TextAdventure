#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


//HTTP-Request mit libcurl==========================================================================
    size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp){

        size_t totalSize = size * nmemb;
        std::string* response = static_cast<std::string*>(userp);
        response->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    nlohmann::json httpGET(std::string apiURL){

        CURL* curl;
        CURLcode res;   
        std::string readBuffer;

        const char* cstrURL = apiURL.c_str();

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, cstrURL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        nlohmann::json jsonData;

        if(res != CURLE_OK){

            std::cerr << "curl_easy_perform() does not work" << curl_easy_strerror(res);
        }else{

            try{
                jsonData = nlohmann::json::parse(readBuffer);

            }catch (nlohmann::json::parse_error& e){

                std::cerr << "JSON parse error: " << e.what() << "\n";
            }
        }

        curl_easy_cleanup(curl);

        return jsonData;
    }
//==============================================================================================

std::string monsterFilter(){

    std::string baseURL = "https://api.open5e.com/monsters/?";

    baseURL += "cr=2&hit_points__gte=30&hit_points__lte=50&document__slug=wotc-srd";

    return baseURL;
}

void handleCommands(std::vector<std::string> uInput){

    std::ifstream ifs("verbs.json");
    nlohmann::json jf = nlohmann::json::parse(ifs);


    for(std::string verb : uInput){

        for(auto& el : jf.items()){

            bool found = jf.items() == verb;
        } 
    }



}



int main(){

//Test API-Call Monster


    // std::string filterURL = monsterFilter();

    // nlohmann::json rndMonster = httpGET(filterURL);

    // for(const auto& item : rndMonster["results"]){

    //     std::cout << item["speed"]["walk"].get<int>() << std::endl;
    // }
  
// Catch User-Input


    std::string userInput = {};
    std::vector<std::string> v = {};

    std::cout << "Bitte gib was ein:";
    std::getline(std::cin, userInput);

    std::istringstream iss(userInput);

    do{

        std::string temp;
        iss >> temp;
        v.push_back(temp);
    
    } while(iss);

    handleCommands(v);

}   