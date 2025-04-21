#include "../include/torControl.hpp"
#include "../include/databaseLogic.hpp"

#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

//DATABASE FORMAT:
/*

name;path;requestedPort(=listen);destinatedPort

*/




struct Tor {
    bool isInit = false;
    std::string pathToTor;
    std::string pathToTorrc;
    OperatingSystems OS;

    bool osIsComputer = true;
    std::string pathToDatabase = "./torOnionServices.csv";

};

Tor torConfig;


/*

TOR HANDLER FUNCTIONS


*/



void torHandler::init(std::string torPath,
    std::string torrcPath,
    OperatingSystems os){

    torHandler::setTorPath(torPath);
    torHandler::setTorrcPath(torrcPath);
    torHandler::setOS(os);
}


int torHandler::torStart(){
    if(torConfig.osIsComputer){
        if(torConfig.isInit == false) return 1;
        std::string cmd = torConfig.pathToTor + " -f " + (torConfig.pathToTorrc);
        std::cout << system(cmd.c_str());
    }
    else{
        //TO IMPLEMENT MOBILE SUPPORT
    }
    
    return 0;

}


int torHandler::torStop(){
    if(torConfig.isInit == false) return 1;

    if(torConfig.osIsComputer){
        switch(torConfig.OS){
            case OperatingSystems::Windows:
                std::system("taskkill /IM tor.exe /F");
                break;
            case OperatingSystems::Linux:
                std::system("pkill tor");
                break;
            case OperatingSystems::MacOS:
                std::system("pkill tor");
                break;
            default:
                return 1;
                break;
        }
    }
    else{
        //TO IMPLEMENT MOBILE SUPPORT
    }

}


void torHandler::rebuildTorrc(){

    torHandler::torStop();

    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    
    std::filesystem::path path(torHandler::getTorrcPath()); 

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path.c_str() << std::endl;
        return;
    }


    file << "SOCKSPort 127.0.0.1:9050" << std::endl;
    file << "ControlPort 9051" << std::endl;

    file << "\n\n";

    for(auto it = onionServices.begin(); it != onionServices.end(); it++){

        std::vector<std::string> onion = parser((*it), ';');

        file << "HiddenServiceDir " << onion[1] << std::endl;
        file << "HiddenServicePort " << onion[2] << "127.0.0.1:" << onion[3] << std::endl;
        file << "HiddenServiceVersion 3" << std::endl;

        file << "\n";
    }

    file.close();

    torHandler::torStart();


}



/*

TOR HANDLER SETTERS


*/



void torHandler::setTorPath(std::string torPath){
    torConfig.pathToTor = torPath;
}
void torHandler::setTorrcPath(std::string torrcPath){
    torConfig.pathToTorrc = torrcPath;
}
void torHandler::setOS(OperatingSystems os){
    torConfig.OS = os;

    if(torConfig.OS == OperatingSystems::Android || torConfig.OS == OperatingSystems::IOS){
        torConfig.osIsComputer = false;
    }

    else{
        torConfig.osIsComputer = true;
    }
}
void torHandler::setDatabasePath(std::string databasePath){
    torConfig.pathToDatabase = databasePath;
}


/*


TOR HANDLER GETTERS



*/


const std::string & torHandler::getTorPath(){
    return torConfig.pathToTor;
}
const std::string &torHandler::getTorrcPath(){
    return torConfig.pathToTorrc;
}
const OperatingSystems &torHandler::getOS(){
    return torConfig.OS;
}
const std::string &torHandler::getDatabasePath(){
    return torConfig.pathToDatabase;
}




/*

TOR ONION SERVICE OPERATOR

*/

std::string torHandler::addNewOnionService(
    std::string name,
    std::string path, 
    unsigned int requested_port, 
    unsigned int destination_port
){


    std::string onionToAdd = name + ";";
    onionToAdd += path + ";";
    onionToAdd += std::to_string(requested_port) + ";";
    onionToAdd += std::to_string(destination_port);


    appendDB(torHandler::getDatabasePath(), onionToAdd);

    torHandler::rebuildTorrc();
}

void torHandler::delOnionService(std::string name){
    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());


    for(std::vector<std::string>::iterator it = onionServices.begin(); it != onionServices.end(); it++){
        std::string currentName = "";

        unsigned short int index=0;
        while(index < 256 && ((*it)[index] != ';')){
            currentName += (*it)[index];
        }

        if(currentName == name){
            onionServices.erase(it);
            break; 
        }

    }

    writeDB(torHandler::getDatabasePath(), onionServices);
    torHandler::rebuildTorrc();

}


void torHandler::changeName(std::string oldName, std::string newName){
    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    for(unsigned int i = 0; i <= onionServices.size(); i++){
        std::string currentName = "";

        unsigned short int index=0;


        //Get the name of the actual onion analyzed
        while(index < 256 && (onionServices[i][index] != ';')){
            currentName += onionServices[i][index];
            index++;
        }


        //Logic to change name
        if(currentName == oldName){
            std::string newOnion = newName;
            for(int j = index; j < onionServices[i].size(); j++){
                newOnion += onionServices[i][j];
            }
            onionServices[i] = newOnion;
            break; 
        }

    }
    writeDB(torHandler::getDatabasePath(), onionServices);
    torHandler::rebuildTorrc();

}
void torHandler::changePath(std::string name, std::string newPath){

    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    for(unsigned int i = 0; i <= onionServices.size(); i++){
        std::string currentName = "";

        unsigned short int endOfName=0;


        //Get the name of the actual onion analyzed
        while(endOfName < 256 && (onionServices[i][endOfName] != ';')){
            currentName += onionServices[i][endOfName];
            endOfName++;
        }

        if(currentName == name){

            std::vector<std::string> newOnionVector = parser(onionServices[i], ';');
            newOnionVector[1] = newPath;
            std::string newOnion = "";

            for(unsigned int j = 0; j < newOnionVector.size(); j++){
                newOnion+=newOnionVector[i];
                newOnion+=';';
            }

            newOnion.pop_back();
            onionServices[i] = newOnion;
            break;
        }
        




    }

    writeDB(torHandler::getDatabasePath(), onionServices);
    torHandler::rebuildTorrc();
}
void torHandler::changeRequestedPort(std::string name, unsigned int newRequestedPort){
    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    for(unsigned int i = 0; i <= onionServices.size(); i++){
        std::string currentName = "";

        unsigned short int endOfName=0;


        //Get the name of the actual onion analyzed
        while(endOfName < 256 && (onionServices[i][endOfName] != ';')){
            currentName += onionServices[i][endOfName];
            endOfName++;
        }

        if(currentName == name){
            std::vector<std::string> newOnionVector = parser(onionServices[i], ';');
            newOnionVector[2] = newRequestedPort;
            std::string newOnion = "";

            for(unsigned int j = 0; j < newOnionVector.size(); j++){
                newOnion+=newOnionVector[i];
                newOnion+=';';
            }

            newOnion.pop_back();
            onionServices[i] = newOnion;
            break;
            
        }
        




    }

    writeDB(torHandler::getDatabasePath(), onionServices);
    torHandler::rebuildTorrc();
}
void torHandler::changeDestinationPort(std::string name, unsigned int newDestinationPort){
    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    for(unsigned int i = 0; i <= onionServices.size(); i++){
        std::string currentName = "";

        unsigned short int endOfName=0;


        //Get the name of the actual onion analyzed
        while(endOfName < 256 && (onionServices[i][endOfName] != ';')){
            currentName += onionServices[i][endOfName];
            endOfName++;
        }

        if(currentName == name){
            std::vector<std::string> newOnionVector = parser(onionServices[i], ';');
            newOnionVector[3] = newDestinationPort;
            std::string newOnion = "";

            for(unsigned int j = 0; j < newOnionVector.size(); j++){
                newOnion+=newOnionVector[i];
                newOnion+=';';
            }

            newOnion.pop_back();
            onionServices[i] = newOnion;
            break;
            
        }
    }

    writeDB(torHandler::getDatabasePath(), onionServices);
    torHandler::rebuildTorrc();
}


const std::string torHandler::getServiceAddressByName(std::string& name){

    std::vector<std::string> onionServices = readDB(torHandler::getDatabasePath());

    for(unsigned int i = 0; i <= onionServices.size(); i++){
        std::string currentName = "";

        unsigned short int endOfName=0;


        //Get the name of the actual onion analyzed
        while(endOfName < 256 && (onionServices[i][endOfName] != ';')){
            currentName += onionServices[i][endOfName];
            endOfName++;
        }

        if(currentName == name){
            return torHandler::getServiceAddressByPath(parser(onionServices[i], 'j')[1]);            
        }
    }

}
const std::string torHandler::getServiceAddressByPath(std::string& path){

    path+="/hostname";

    std::filesystem::path path(path);  

    if (!std::filesystem::exists(path)) {
        std::cerr << "File does not exist: " << path << std::endl;
        return "";  
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }
    std::string output;
    std::getline(file, output);

    return output;


}

/*

MANAGE DATABASE

*/

std::vector<std::string> readDB(const std::string& filePath) {
    std::vector<std::string> lines;
    std::filesystem::path path(filePath);  


    if (!std::filesystem::exists(path)) {
        std::cerr << "File does not exist: " << filePath << std::endl;
        return lines;  
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);  
    }

    file.close();
    return lines;
}

void writeDB(const std::string& filePath, const std::vector<std::string>& lines) {
    std::filesystem::path path(filePath); 

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    for (const auto& line : lines) {
        file << line << std::endl;
    }

    file.close();
}

void appendDB(const std::string& filePath, const std::string& line) {
    std::filesystem::path path(filePath);

    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    file << line << std::endl;

    file.close();
}

std::vector<std::string> parser(std::string stringToParse, char separator){
    std::vector<std::string> output;

    std::string currentReading;
    
    for(unsigned int i = 0; i < stringToParse.size(); i++){
        if(stringToParse[i] != separator){
            currentReading+=stringToParse[i];
        }

        else{
            output.push_back(currentReading);
            currentReading="";
        }

    }

    


    return output;

}

