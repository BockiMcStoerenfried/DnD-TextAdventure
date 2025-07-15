#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <string>
#include <iostream>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using nlohmann::json;


class ModelDataHolder{

private:

//HTTP-Request mit libcurl==========================================================================
    static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp){

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

    std::string monsterFilter(){

        std::string baseURL = "https://api.open5e.com/monsters/?";

        baseURL += "cr=2&hit_points__gte=30&hit_points__lte=50&document__slug=wotc-srd";

        return baseURL;
    }

public:

    void getMonster(){

        std::string filterURL = monsterFilter();

        nlohmann::json rndMonster = httpGET(filterURL);

        for(const auto& item : rndMonster["results"]){

            std::cout << item["speed"]["walk"].get<int>() << std::endl;
        }

    }


    //For Handler.h
    std::string getJSONState(std::string inputWord, std::string sentencePart){

        std::ifstream jsonFile("JSON/" + sentencePart + ".JSON");
        json jsonData = json::parse(jsonFile);

        for(auto& pairs : jsonData.items()){

            std::cout << pairs.key() << std::endl;
            if(pairs.key() == inputWord){

                return pairs.value().get<std::string>();
            }
        }

        return 0;
    }



    //For View.h
    std::string getData(std::string interactor, std::string interaction, std::string with){

        json jsonData = json::parse(std::ifstream("JSON/interactors.json"));

        if(with == "" && interaction == "combine"){

            return jsonData[interactor][interaction][with].get<std::string>();

        }else{

            return jsonData[interactor][interaction].get<std::string>();
        }

    }
};

#endif