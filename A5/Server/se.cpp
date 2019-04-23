
//SERVER
#include <iostream>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<fstream>
using namespace std;

#define PORT 9999
#define buflen 1000;
void die(char *s) 
{
	perror(s);
	exit(1);
}

int main() {
	struct sockaddr_in server_addr,client_addr;

	//step 1: Creating Socket
	int sock;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1) 
	{											
		die("Error in socket");
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
	
	if(bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1)
		die(" Not Binding ");
	else
		cout<<"\n server connected to client ";

	int client_len=sizeof(client_addr);
	socklen_t cli=sizeof(client_addr);
	int choice,msg_len;
	char buffer[1000];
	bzero((char *)buffer,sizeof(buffer));
	msg_len=recvfrom(sock,buffer,1000,0,(struct sockaddr *)&client_addr,&cli);

	if(msg_len>0)
	{
		cout<<"Client :- "<<buffer<<endl;
		bzero((char *)buffer,sizeof(buffer));
	}
	do
	{
		cout<<"\n1.Peer chat \n2.send file to client \n3.Receive file from client \n0.close \nENter your choice:";

		cin>>choice;
		switch(choice)
		{
		case 1:
			int n;
			while(1)
			{
				bzero((char *)buffer,sizeof(buffer));
				msg_len=recvfrom(sock,buffer,1000,0,(struct sockaddr *)&client_addr,&cli);

				if(msg_len>0)
				{
					cout<<"client msg  :- "<<buffer<<endl;
					bzero((char *)buffer,sizeof(buffer));

				}
				cout<<"\nYour msg:";
				cin.getline(buffer,sizeof(buffer));
				msg_len=sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,client_len);
				if(msg_len<0)
				{
					cout<<"Sending error"<<endl;
				}
				if(strcmp(buffer,"bye")==0)
					break;
				bzero((char *)buffer,sizeof(buffer));
			}
			break;

		case 2:
		{
			cout<<"\nEnter Filename:";
			char filename[100];
			cin>>filename;
			fstream fout;
			fout.open(filename,ios::in|ios::out|ios::binary);
			fout.seekg(0,ios::end);
			int filesize=fout.tellg();
			char *filebuff=new char[filesize];
			fout.seekg(0,ios::beg);
			fout.read(filebuff,filesize);
			msg_len=sendto(sock,filename,strlen(filename),0,(struct sockaddr *)&client_addr,client_len);
						if(msg_len==-1)
							die("Filename error");

			msg_len=sendto(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&client_addr,client_len);
			if(msg_len==-1)
				die("Filesize error");



			msg_len=sendto(sock,filebuff,filesize,0,(struct sockaddr *)&client_addr,client_len); 
			if(msg_len==-1)
				die("File not sent");
			else
				cout<<"File sent  Successful";
			fout.close();
		}
		break;
		case 3:
		{
					char filename[100];
						bzero((char *)filename,sizeof(filename));
						msg_len=recvfrom(sock,filename,99,0,(struct sockaddr*)&client_addr,&cli);
						if(msg_len==-1)
							die("Filename error");
						cout<<"\nFilename:"<<filename;

						int filesize;
						msg_len=recvfrom(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr*)&client_addr,&cli);
						cout<<"\nFileSize:"<<filesize;
						char *filebuff=new char[filesize];


						bzero((char *)filebuff,sizeof(filebuff));
						msg_len=recvfrom(sock,filebuff,filesize,0,(struct sockaddr*)&client_addr,&cli);
						ofstream fout1;
						fout1.open(filename,ios::out|ios::binary);
						if(!fout1)
							die("CANNOT CREATE FILE");
						else
						{
							fout1.write(filebuff,filesize);
							fout1.close();
							cout<<"File received";
						}
		}
						break;
		}
	}while(choice!=0);
close(sock);
	return 0;
}


