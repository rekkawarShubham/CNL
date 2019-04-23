#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <errno.h>
#include<fstream>

using namespace std;

#define PORT_NUMBER     5001
#define SERVER_ADDRESS "127.0.0.1"

class myClient
{
	int client_socket;
	sockaddr_in remote_addr;

public:
	void c_construct();
	void c_create();
	void c_connect();
	void c_close()
	{
		close(client_socket);
	}
	void c_chat();
	void c_file();
	void trigo();
};

void myClient::c_create()
{
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1)
        {
                fprintf(stderr, "Error creating socket --> %s\n", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Socket created\n";
	}

	

}

void myClient::c_construct()
{
	/* Zeroing remote_addr struct */
        memset(&remote_addr, 0, sizeof(remote_addr));

        /* Construct remote_addr struct */
        remote_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(remote_addr.sin_addr));
        remote_addr.sin_port = htons(PORT_NUMBER);

}

void myClient::c_connect()
{
	/* Connect to the server */
        if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
        {
                fprintf(stderr, "Error on connect --> %s\n", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Connection established\n";
	}
	
}

void myClient::c_chat()
{
	char buffer[256];
	cin.ignore();
	 while(1)
	 {
		 bzero((char *)buffer,256);
		 	cout<<"\nmsg >> ";
		 	string data;
			
		 	getline(cin, data);
		 	strcpy(buffer,data.c_str());

		 send(client_socket,buffer,strlen(buffer),0);

		 bzero(buffer,256);
		 cout <<endl<< "..." << endl;
		 recv(client_socket,(char*)&buffer,sizeof(buffer),0);
		 cout<<"Server: "<<buffer<<endl;

		if(buffer[0]=='e' && buffer[1]=='x' && buffer[2]=='i' && buffer[3]=='t'){
			c_close();
 			break;
		}
	}

}

void myClient::c_file()
{
	long long int msg_len;

		char buffer[256];
	
		char filename[BUFSIZ];

			cout<<"\nEnter filename: ";
			cin>>filename;

			msg_len = send(client_socket,filename,BUFSIZ,0);

			if(msg_len==-1)
			{
				fprintf(stderr, "Error sending filename --> %s", strerror(errno));
			}
			else
			{
				cout<<"File requested: "<<filename<<endl;
			}


			char *filebuff=new char[90000*80];


			bzero((char *)filebuff,sizeof(filebuff));

			msg_len = recv(client_socket,filebuff,90000*80,0);

			ofstream fout;

			fout.open(filename,ios::out|ios::binary);
			if(!fout)
				fprintf(stderr, "Could not create file --> %s", strerror(errno));
			else
			{
				fout.write(filebuff,msg_len);
				fout.close();
				cout<<"File received";
			}
		c_close();	

}

void myClient::trigo()
{

	char angle[3];
	char s_ans[20],c_ans[20],t_ans[20];

	while(1)
	{
		cout<<"Enter angle "<<endl;
		cin>>angle;

		send(client_socket,angle,strlen(angle),0);

		cout<<"Sine of angle "<<angle<<" is ";
		recv(client_socket,s_ans,20,0);
		cout<<s_ans<<endl;
		cout<<"Cosine of angle "<<angle<<" is ";
		recv(client_socket,c_ans,20,0);
		cout<<c_ans<<endl;
		

		cout<<"Tangent of angle "<<angle<<" is ";
		recv(client_socket,t_ans,20,0);
		cout<<t_ans<<endl;

		c_close();
		
		break;
	}



}

int main()
{
	myClient cl;
	int choice;
	do{

	cout<<"\n1.Chat \n";
	cout<<"2.File Transfer\n";
	cout<<"3.Trigonometric Calci\n";
	cout<<"4.Exit\n";
	cin>>choice;

	switch(choice)	
	{
	case 1:
		
	cl.c_create();
	cl.c_construct();
	cl.c_connect();
	cl.c_chat();
	
	break;
	case 2:
	
	cl.c_create();
	cl.c_construct();
	cl.c_connect();
	cl.c_file();

	break;
	case 3:

	cl.c_create();
	cl.c_construct();
	cl.c_connect();
	cl.trigo();
	cl.c_close();

	break;

	case 4:

	cl.c_close();
	exit(1);
	}

	}while(choice<=4);
	
	
	
	return 0;
}

