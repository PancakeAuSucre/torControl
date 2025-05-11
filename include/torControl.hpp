#pragma once
#include <string>

enum OperatingSystems{
    Windows,
    Linux,
    MacOS,
    Android,
    IOS
};


namespace torHandler{

    void init(
        std::string torPath,
        std::string torrcPath,
        std::string torServiceDatabasePath,
        OperatingSystems os
    );

//Tor Basic Functions
    int torStart(); //TO IMPLEMENT MOBILE SUPPORT

    int torStop(); //TO IMPLEMENT MOBILE SUPPORT

    void rebuildTorrc();

//Handler Data Setters
    void setTorPath(std::string torPath);
    void setTorrcPath(std::string torrcPath);
    void setOS(OperatingSystems os);
    void setDatabasePath(std::string databasePath);

//Handler Data Getters
    const std::string &getTorPath();
    const std::string &getTorrcPath();
    const OperatingSystems &getOS();
    const std::string &getDatabasePath();



//Operations on Onion Services              //TO IMPLEMENT MOBILE SUPPORT
    std::string addNewOnionService(
        std::string name,
        std::string path, 
        unsigned int requested_port, 
        unsigned int destination_port
    );

    void delOnionService(
        std::string name
    );

    void changeName(std::string oldName, std::string newName);
    void changePath(std::string name, std::string newPath);
    void changeRequestedPort(std::string name, unsigned int newRequestedPort);
    void changeDestinationPort(std::string name, unsigned int newDestinationPort);

    const std::string getServiceAddressByName(std::string name);
    const std::string getServiceAddressByPath(std::string path);
}
