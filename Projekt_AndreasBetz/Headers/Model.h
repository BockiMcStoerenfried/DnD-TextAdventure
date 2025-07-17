#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>


using nlohmann::json;


class ModelDataHolder{

private:

// //HTTP-Request mit libcurl==========================================================================
//     static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp){

//         size_t totalSize = size * nmemb;
//         std::string* response = static_cast<std::string*>(userp);
//         response->append(static_cast<char*>(contents), totalSize);
//         return totalSize;
//     }

//     json httpGET(std::string apiURL){

//         CURL* curl;
//         CURLcode res;   
//         std::string readBuffer;

//         const char* cstrURL = apiURL.c_str();

//         curl = curl_easy_init();
//         curl_easy_setopt(curl, CURLOPT_URL, cstrURL);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

//         res = curl_easy_perform(curl);

//         nlohmann::json jsonData;

//         if(res != CURLE_OK){

//             std::cerr << "curl_easy_perform() does not work" << curl_easy_strerror(res);
//         }else{

//             try{
//                 jsonData = nlohmann::json::parse(readBuffer);

//             }catch (nlohmann::json::parse_error& e){

//                 std::cerr << "JSON parse error: " << e.what() << "\n";
//             }
//         }

//         curl_easy_cleanup(curl);

//         return jsonData;
//     }

//     std::string monsterFilter(){

//         std::string baseURL = "https://api.open5e.com/monsters/?";

//         baseURL += "cr=2&hit_points__gte=30&hit_points__lte=50&document__slug=wotc-srd";

//         return baseURL;
//     }

public:

    // void getMonster(){

    //     std::string filterURL = monsterFilter();

    //     nlohmann::json rndMonster = httpGET(filterURL);

    //     for(const auto& item : rndMonster["results"]){

    //         std::cout << item["speed"]["walk"].get<int>() << std::endl;
    //     }

    // }


//Get Key from interactions and Value from verbs
    std::string getJSONState(std::string inputWord, std::string sentencePart){

        std::ifstream jsonFile("JSON/" + sentencePart + ".JSON");
        json jsonData = json::parse(jsonFile);

        for(auto& pairs : jsonData.items()){

            if(pairs.key() == inputWord){

                if(sentencePart == "verbs"){
                    return pairs.value().get<std::string>();
                }else{
                    return pairs.key();
                }
            }
        }

        return "";
    }

    //Changing status in JSON-File
    void changeJSONState(std::string interactor, std::string status){

        json writeOffFile = json::parse(std::ifstream("JSON/interactors.json"));


        writeOffFile[interactor]["status"] = "_" + status;

        std::ofstream file("JSON/interactors.json");
        file << writeOffFile ;
    }


    void combineItems(std::string a, std::string b){


        std::ifstream jsonFile("JSON/combine.JSON");


        json combinedItem = json::parse(jsonFile);
        json oldItems = json::parse(std::ifstream("JSON/interactors.json"));   

        oldItems[a + b] = combinedItem[a + b];
        oldItems.erase(a);
        oldItems.erase(b);


        std::ofstream file("JSON/interactors.json");
        file << oldItems;

        

    }




//Getting data ========================================================================
    json getData(std::string interactor, std::string interaction, std::string with){

        json jsonData = json::parse(std::ifstream("JSON/interactors.json"));

        interaction += jsonData[interactor]["status"];

        if(with != "" && interaction == "combine_"){

            return jsonData[interactor][interaction][with];

        }else{

            return jsonData[interactor][interaction];
        }

    }


//Ending===============================================================================
    json getEnd(){

        json jsonData = json::parse(std::ifstream("JSON/interactors.json"));

        return jsonData["storyteller"]["endState"];
    }

    void changeEnd(){


        json jsonData = json::parse(std::ifstream("JSON/interactors.json"));

        jsonData["storyteller"]["endState"] = "true";

        std::ofstream file ("JSON/interactors.json");
        file << jsonData;

    }

//===============================================================================

//GetFile

    json getFile(std::string fileName){

        return json::parse(std::ifstream(fileName));
    }
};

#endif