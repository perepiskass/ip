#include <ip.h>
#include <iomanip>
#include <lib.h>

using namespace std;

void PrintLine ()
{
    for (int i = 0;i <= 86;++i) cout << '-';
    cout << endl;
}

int main()

{
	cout << "Programm version: " << version() << endl;
    cout << "Enter IP address and mask (in the number of bits or four octets)" << endl;
    char next = 'y';
    do
    {
        string ipmask = "";
        string ipaddres = "";
        cout << "\nEnter IP : ";
        cin >> ipaddres;
        cout << "\nEnter Mask : ";
        cin >> ipmask;
    IP Ipv4;
    try {
        Ipv4.Set_Address(ipaddres);
        Ipv4.Set_Netmask(ipmask);
        int z = 15;
        int z2 = 20;
        int z3 = 16;
        int z4 = 35;
        PrintLine();
        cout <<left << setw(z)<<"Name" <<left << setw(z2) << "Value" << left <<setw(z3)<< "HEX code" << left << setw(z4) << "Binary code"<< endl;
        PrintLine();
        cout <<left << setw(z)<<"Address" <<left << setw(z2) << Ipv4.Get_Address() << left<<setw(z3)<< Ipv4.Get_Address_Hex() <<left << setw(z4) << Ipv4.Get_Address_Bin() << endl;
        cout <<left << setw(z)<<"Mask" <<left << setw(z2) << Ipv4.Get_Netmask() << left<<setw(z3)<< Ipv4.Get_Netmask_Hex() <<left << setw(z4) << Ipv4.Get_Netmask_Bin() << endl;
        cout <<left << setw(z)<<"Bitmask" <<left << setw(z2)<< Ipv4.Get_Bitmask() <<endl;
        cout <<left << setw(z)<<"Network" <<left << setw(z2) << Ipv4.Get_Network() << left<<setw(z3)<< Ipv4.Get_Network_Hex() <<left << setw(z4) << Ipv4.Get_Network_Bin() << endl;
        cout <<left << setw(z)<<"Wildcard" <<left << setw(z2)<< Ipv4.Get_Wildcard() << left<<setw(z3) << Ipv4.Get_Wildcard_Hex() <<left << setw(z4) << Ipv4.Get_Wildcard_Bin() << endl;
        cout <<left << setw(z)<<"Broadcast" <<left << setw(z2)<< Ipv4.Get_Broadcast() << left<<setw(z3) << Ipv4.Get_Broadcast_Hex() <<left << setw(z4) << Ipv4.Get_Broadcast_Bin() << endl;
        cout <<left << setw(z)<<"Hostmin" <<left << setw(z2)<< Ipv4.Get_Hostmin() << left<<setw(z3) << Ipv4.Get_Hostmin_Hex() <<left << setw(z4) << Ipv4.Get_Hostmin_Bin() << endl;
        cout <<left << setw(z)<<"Hostmax" <<left << setw(z2)<< Ipv4.Get_Hostmax() << left<<setw(z3) << Ipv4.Get_Hostmax_Hex() <<left << setw(z4) << Ipv4.Get_Hostmax_Bin() << endl;
        cout <<left << setw(z)<<"Hosts" <<left << setw(z2)<< Ipv4.Get_Hosts() <<endl;
        PrintLine();

        cout <<"Following? (y - yes , eny key - no) : ";
        cin >> next;
        }
     catch (const char *error)
        {
            cout << error << endl;
            cout << "Enter the correct data!" << endl;
            next = 'y';
        }
    } while (next == 'y');

    return 0;
}
