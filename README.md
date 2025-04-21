# Tor Control

### Simple Tor Controller Library for C++
##### Licensed under the MIT License. See LICENSE for details.

## Case of Use:
This Library was originally developped to manage tor and tor onion services via a C++ program. It aims to be cross plateform. It was quickly developped and is for sure not optimized. Any contribution is encourage!

## Usage:
Simply init the Handler with your tor path, torrc path destined OS and the desired database path. 
The database path is used to store onion services to be able to manage it in a more simple way. A list of functions is given at the end of this file.

The Tor path should be the path to your tor executable
The Torrc path should be the path to a config file (you can put it anywhere but I would put it alongside the tor executable)

every functions is stored in namespace torHandler
This is not a class so you have one configuration possible at a time.


## Links
Please Download Tor Expert Bundle from the official Tor Project Website for your desired OS:
https://www.torproject.org/fr/download/tor/

## Main Functions:

    void init(
        std::string torPath,
        std::string torrcPath,
        OperatingSystems os
    );

    int torStart(); 
    int torStop(); 

    void setTorPath(std::string torPath);
    void setTorrcPath(std::string torrcPath);
    void setOS(OperatingSystems os);
    void setDatabasePath(std::string databasePath);

    std::string addNewOnionService(
        std::string name,
        std::string path, 
        unsigned int requested_port, 
        unsigned int destination_port
    );

    const std::string getServiceAddressByName(std::string& name);
    const std::string getServiceAddressByPath(std::string& path);


