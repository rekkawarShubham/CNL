#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
int main()
{
	cout<<"\n\t\t Packet Tracer"<<endl;
	string value,time, sr_no,source,destination,info,protocol,len;
	int count=-1,i=0;

	int choice;
		do{
			ifstream file("pack.csv");
			count=-1;
			i=0;

			cout<<"\n Enter the protocol packet "<<endl;
			cout<<"\n1.Ip Packet"
				"\n2.UDP packet"
				"\n3.tcp packet	"
				"\n 4.ethernet packet"
				"\n0.exit "
				"\n Enter your choice :"<<endl;
			cin>>choice;
			string pChoice;
			switch(choice)
			{
				case 1: pChoice="ICMPv6";
				break;
				case 2: pChoice="UDP";
				break;
				case 3:  pChoice="TCP";
				break;
				case 4: pChoice="ARP";
				break;
				default:pChoice="Exit";
				break;
			}	
			while(file.good())
			{
				getline(file,sr_no,',');
				getline(file,time,',');
				getline(file,source,',');
				getline(file,destination,',');
				getline(file,protocol,',');
				getline(file,len,',');
				getline(file,info,'\n');

				protocol=string(protocol,1,protocol.length()-2);

				if(protocol=="Protocol"|| protocol==pChoice)
				{
					cout<<setw(4)<<left<<i++;
					cout<<setw(12)<<left<<string(time ,1,time.length()-2);
					cout<<setw(30)<<left<<string(source,1,source.length()-2);
					cout<<setw(30)<<left<<string(destination,1,destination.length()-2);
					cout<<setw(8)<<left<<protocol;
					cout<<setw(8)<<left<<string(len,1,len.length()-2);
					cout<<string(info,1,info.length()-2)<<"\n";
					count++;
							}


			}
			file.close();
			cout<<"\n PacketCounts for protocol :  "<<count;
		}while(choice!=0);
		return 0;
}