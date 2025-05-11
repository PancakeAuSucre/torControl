#include "../include/torControl.hpp"
#include <iostream>



int main(int argc, char* argv[]){

    torHandler::init("/etc/home/arthur/Documents/tor/tor/tor", "/etc/home/arthur/Documents/tor/tor/torrc", OperatingSystems::Linux);

    std::string clientOnionServiceName = "client";
    std::string clientOnionServiceAddress = "";
    
    if(torHandler::getServiceAddressByName(clientOnionServiceName) == "error"){
                    std::cout << "test2" << std::endl;

        clientOnionServiceAddress = torHandler::addNewOnionService(clientOnionServiceName, "/var/tor/clientService", 5000, 5000);
    }



    return 0;
}