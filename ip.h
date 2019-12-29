#ifndef IP_H
#define IP_H
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>



class IP
{
public:
    IP(std::string ip = "0.0.0.0",std::string mask = "0.0.0.0");
    void Set_Address(std::string ipaddres);
    void Set_Netmask(std::string netmask);

    std::string Get_Address();
    std::string Get_Address_Hex();
    std::string Get_Address_Bin();

    std::string Get_Netmask();
    std::string Get_Netmask_Hex();
    std::string Get_Netmask_Bin();

    int Get_Bitmask();

    std::string Get_Wildcard();
    std::string Get_Wildcard_Hex();
    std::string Get_Wildcard_Bin();

    std::string Get_Network();
    std::string Get_Network_Hex();
    std::string Get_Network_Bin();

    std::string Get_Broadcast();
    std::string Get_Broadcast_Hex();
    std::string Get_Broadcast_Bin();

    std::string Get_Hostmin();
    std::string Get_Hostmin_Hex();
    std::string Get_Hostmin_Bin();

    std::string Get_Hostmax();
    std::string Get_Hostmax_Hex();
    std::string Get_Hostmax_Bin();

    uint Get_Hosts();

private:
    std::string To_Hex(std::vector<int> value);
    std::string To_Bin(std::vector<int> value);
    std::string To_String(std::vector<int> value);
    void Set_Wildcard();
    void Set_Network();
    void Set_Broadcast();
    void Set_Hostmin();
    void Set_Hostmax();
    void Set_Bitmask();
    std::vector<int> Address;
    std::vector<int> Netmask;
    int Bitmask;
    std::vector<int> Wildcard;
    std::vector<int> Network;
    std::vector<int> Broadcast;
    std::vector<int> Hostmin;
    std::vector<int> Hostmax;
    int Hosts;
};

#endif // IP_H
