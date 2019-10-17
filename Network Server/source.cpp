#include<winsock2.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
//using namespace std; 
// Conflicts will occur when we use the function of 'bind' in the enviroment of 'opencv' and 'socket' simultaneously.
// The solution to this problem is not to using the 'using namespace std'.

#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define BUFFER_SIZE 10240 // The size of the buffer used to store the content being sent or received.
int main()
{
	// Create the socket network enviroment
	WSADATA WSAData;
	char receBuf[BUFFER_SIZE];
	char Response[] = "";

	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		printf("Initialization failed");
		exit(1);
	}
	SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		return 0;
	}
	SOCKADDR_IN addr_Server; // The information of server address
	addr_Server.sin_family = AF_INET;
	addr_Server.sin_port = htons(1234);// Make sure it is same as the client's port
	addr_Server.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(sockServer, (SOCKADDR*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR)
	{
		// Bind the server with local address
		printf("Failed socket() %d \n", WSAGetLastError());
		return 0;
	}

	SOCKADDR_IN addr_Clt;
	int count = 0;
	int fromlen = sizeof(SOCKADDR);
	// Process the received data from here
	while (true)
	{
		std::cout << "wait..." << std::endl;
		cv::Point abc;
		//recvfrom(sockServer, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&addr_Clt, &fromlen);
		//sendto(sockServer, Response, sizeof(Response), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR)); 
		recv(sockServer, (char*)&abc, sizeof(abc), 0);
		std::cout << abc << std::endl;
		// Simple transmission system
		/*
		int last = recvfrom(sockServer, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&addr_Clt, &fromlen); // Receive the data.
		//recv(sockServer, receBuf, sizeof(receBuf), 0); // This is also OK.
		if (last > 0)
		{
			// Determine if the received data is empty
			receBuf[last] = '\0';// Add the '\0' at the end of the character array，otherwise there will be garbled characters.
			if (strcmp(receBuf, "bye") == 0)
			{
				// If received data is 'bye', close the socket system.
				std::cout << " off..." << std::endl;
				closesocket(sockServer);
				return 0;
			}
			else
			{
				printf("Address is %s, receive: %s\n", inet_ntoa(addr_Clt.sin_addr), receBuf);
			}
		}
		// If you want to reply the message
		std::cout << "Reply:";
		std::cin >> Response; // The message you want to reply
		sendto(sockServer, Response, sizeof(Response), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));*/



		// Detection of packet loss
		/*
		int last = recvfrom(sockServer, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&addr_Clt, &fromlen); // Receive the data.
		if (last > 0) {
			receBuf[last] = '\0';
			count++;
			printf("%d \n", count);
		}
		// If you want to reset the count of each loop
		if (count == 10000) {
			count = 0;
		} // In this case I sent 10000 times of data.
		*/



		// Test whether the received data is in wrong order
		/*
		int last = recvfrom(sockServer, receBuf, sizeof(receBuf), 0, (SOCKADDR*)&addr_Clt, &fromlen); // Receive the data.
		int t = 0;
		int f = 0;
		if (last > 0)
		{
				char b[1024];
				printf("Address is %s, receive: %s\n", inet_ntoa(addr_Clt.sin_addr), receBuf);
				sprintf(b, "%g", count); 
				if (strcmp(receBuf, b) == 0) {
					printf("true\n");
					t++;
				}
				else
				{
					printf("false\n");
					f++;
				}
				count++;
				// If you want to reset the count of each loop
				if (count == 1000)
				{
					printf("True:%d,False:%d\n", t, f);
					t = 0;
					f = 0;
					count = 0;
				}
			}
		}*/



		// Receive the image coordinate data
		
		//float coorarr[1024];
		//std::vector<Point2f> imgvec;
		//Point2f imgcoordinate;
		//recv(sockServer, (char*)&coorarr, sizeof(coorarr), 0);
		//// In the case I sent an array of 20 float numbers (totally ten sets of coordinates)
		////for (int a = 0; a < 20; a++) {
		////	printf("%f\n", coorarr[a]);
		////}
		//for (int a = 0; a < 10; a++) {
		//	imgcoordinate.x = coorarr[2 * a];
		//	imgcoordinate.y = coorarr[2 * a + 1];
		//	imgvec.push_back(imgcoordinate);
		//}
		//for (int a = 0; a < 10; a++) {
		//	std::cout << imgvec[a] << std::endl;
		//}
		//

	}
	closesocket(sockServer);
	WSACleanup();
	return 0;
}

