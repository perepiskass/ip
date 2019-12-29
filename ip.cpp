#include <ip.h>

IP::IP(std::string ip ,std::string mask)
{
    Address.resize(4);
    Netmask.resize(4);
    Network.resize(4);

    Set_Address(ip);
    Set_Netmask(mask);
}

void IP::Set_Address(std::string ipaddress)
{
    if (3!=count_if (ipaddress.begin(), ipaddress.end(),[](char symbol){
           if (symbol == '.')return  true;
           else return false;
        })) throw "Invalid IP addr format, missing octet or invalid delimiting character (through dot)";
    for (int i = 3;i>=0;--i)
    {
           int index = ipaddress.length()-1;
           int count = 0;
           while (ipaddress[index]!='.' && index >=0)
           {
               if((ipaddress[index] - '0') <0 || (ipaddress[index] - '0') > 9 ) throw "Invalid character in determining the IP address";
                 Address[i]+= (ipaddress[index--] - '0') *pow(10,count++);
           }
           if (count == 0) throw "Missing octet number for IP address";
           if (index >= 0) ipaddress.erase(index,index + count);
           if (Address[i] < 0 || Address[i] > 255) throw "The number does not correspond to the range for the octet IP address";
    }
}

void IP::Set_Netmask(std::string netmask)
{
    if (netmask.length() <=2 && netmask.length() >0)
    {
        Bitmask = 0;
        int count = 0;
        for (int i = netmask.length()-1;i >= 0;--i)
        {
            if((netmask[i] - '0') < 0 || (netmask[i] - '0') > 9 ) throw  "Invalid character in subnet mask definition";
            Bitmask += (netmask[i]-'0') * pow(10,count++);
        }
        if(Bitmask < 0 || Bitmask > 32 ) throw  "Invalid value for subnet mask";

        count = Bitmask;
        Netmask = {0,0,0,0};
        for (auto &it : Netmask)
        {
            for (int i = 0;i < 8;++i)
            {
                if (count > 0)
                {
                    it += (128 >> i);
                    count--;
                }
            }
        }
    }

    else
    {
        if (3!=count_if (netmask.begin(), netmask.end(),[](char symbol){
               if (symbol == '.')return  true;
               else return false;
            })) throw "Invalid Netmask format, missing octet or invalid delimiting character (through dot)";
        const std::vector<int> VariableMask = {0,128,192,224,240,248,252,254,255};
        for (int i = 3;i>=0;--i)
        {
               int index = netmask.length()-1;
               int count = 0;
               while (netmask[index]!='.' && index >=0)
               {
                   if((netmask[index] - '0') <0 || (netmask[index] - '0') > 9 ) throw  "Invalid character in subnet mask definition";
                     Netmask[i]+= (netmask[index--] - '0') *pow(10,count++);
               }
               if (index >= 0) netmask.erase(index,index + count);
               if (count == 0) throw "Missing octet entry for subnet mask";
               if (std::find(begin(VariableMask),end(VariableMask),Netmask[i]) == end(VariableMask)) throw "Invalid value range for subnet mask";

        }
        Set_Bitmask();
    }
    Set_Wildcard();
    Set_Network();
    Set_Broadcast();
    Set_Hostmin();
    Set_Hostmax();
}

 std::string IP::Get_Address()
 {
    return To_String(Address);
 }

 std::string IP::Get_Address_Hex()
 {
     return To_Hex(Address);
 }

 std::string IP::Get_Address_Bin()
 {
     return To_Bin(Address);
 }

 int IP::Get_Bitmask()
 {
     return Bitmask;
 }

std::string IP::Get_Wildcard()
{
    return To_String(Wildcard);
}

std::string IP::Get_Wildcard_Hex()
{
    return To_Hex(Wildcard);
}

std::string IP::Get_Wildcard_Bin()
{
    return To_Bin(Wildcard);
}

std::string IP::Get_Network()
{
    return To_String(Network);
}

std::string IP::Get_Network_Hex()
{
    return To_Hex(Network);
}

std::string IP::Get_Network_Bin()
{
    return To_Bin(Network);
}

std::string IP::Get_Netmask()
{
    return To_String(Netmask);
}

std::string IP::Get_Netmask_Hex()
{
    return To_Hex(Netmask);
}
std::string IP::Get_Netmask_Bin()
{
    return To_Bin(Netmask);
}

std::string IP::Get_Broadcast()
{
    return To_String(Broadcast);
}

std::string IP::Get_Broadcast_Hex()
{
    return To_Hex(Broadcast);
}

std::string IP::Get_Broadcast_Bin()
{
    return To_Bin(Broadcast);
}

std::string IP::Get_Hostmin()
{
    return To_String(Hostmin);
}

std::string IP::Get_Hostmin_Hex()
{
    return To_Hex(Hostmin);
}

std::string IP::Get_Hostmin_Bin()
{
    return To_Bin(Hostmin);
}

std::string IP::Get_Hostmax()
{
    return To_String(Hostmax);
}

std::string IP::Get_Hostmax_Hex()
{
    return To_Hex(Hostmax);
}

std::string IP::Get_Hostmax_Bin()
{
    return To_Bin(Hostmax);
}

uint IP::Get_Hosts()
{
    if (Bitmask >=31) return 0;
    return pow(2,32-Bitmask)-2;
}

//------------------------Private method---------------------------------//

std::string IP::To_Hex(std::vector<int> value)
{
    std::string result;
    for (auto it : value)
    {
            char res[3] = "00";
            const char* digits = "0123456789ABCDEF";
            int i = 0;
            while( it )
            {
                res[i++] = digits[it%16];
                it/=16;
            }
            i = 2;
            while( i-- )
            {
                result+= res[i];
            }
            result+= '.';
    }
    result.erase(end(result)-1);
    return result;
}

std::string IP::To_Bin(std::vector<int> value)
{
    std::string result;
    int count = Bitmask;
    for (auto it : value)
    {
            char res[9] = "00000000";
            const char* digits = "01";
            int i = 0;
            while( it )
            {
                res[i++] = digits[it%2];
                it/=2;
            }
            i = 8;
            while( i-- )
            {
                result+= res[i];
                if (count == 1) result += '|';
                count --;
            }
            if (count != 0) result+= '.' ;
    }
    result.erase(end(result)-1);
    return result;
}

std::string IP::To_String(std::vector<int> value)
{
    std::string result;
    for (auto it : value)
    {
        result += std::to_string(it) + '.';
    }
    result.erase(end(result)-1);
    return result;
}

void IP::Set_Wildcard()
{
    Wildcard.erase(begin(Wildcard),end(Wildcard));
    for (auto it : Netmask)
    {
            it = it ^ 255;
            Wildcard.push_back(it);
    }
}
void IP::Set_Network()
{
    for (int i = 0;i < 4;++i)
    {
        Network[i] = Address[i] & Netmask[i];
    }
}
void IP::Set_Broadcast()
{
    Broadcast.erase(begin(Broadcast),end(Broadcast));
    std::copy(begin(Network),end(Network),back_inserter(Broadcast));
    int count = 32 - Bitmask;
    for (auto it = Broadcast.rbegin(); it!=Broadcast.rend(); ++it)
    {
        for (int i = 0;i < 8;++i)
        {
            if (count > 0)
            {
                *it = *it + (1 << i);
                count --;
            }
        }
    }

}
void IP::Set_Hostmin()
{
    Hostmin.erase(begin(Hostmin),end(Hostmin));
    if (Bitmask == 32)
    {
        std::copy(begin(Network),end(Network),back_inserter(Hostmin));
        bool triger = false;
        for (auto it = Hostmin.rbegin(); it!=Hostmin.rend() && triger == false; ++it)
        {
            for (int i = 0;i < 8 && triger == false;++i)
            {
                if (*it & (1 << i)) *it = *it ^ (1 << i);
                else
                    {
                        *it = *it | (1 << i);
                        triger = true;
                    }
            }
        }
    }
    else
    {
        std::copy(begin(Network),end(Network),back_inserter(Hostmin));
        Hostmin[3] = Hostmin[3] + 1;
    }

}
void IP::Set_Hostmax()
{
    Hostmax.erase(begin(Hostmax),end(Hostmax));
    std::copy(begin(Broadcast),end(Broadcast),back_inserter (Hostmax));
    Hostmax[3] -= 1;
}

void IP::Set_Bitmask()
{
    Bitmask = 0;
    for (auto it : Netmask)
    {
        for (int i = 0;i < 8;++i)
        {
            if (it & 1) Bitmask ++;
            it = it >> 1;
        }
    }
}










