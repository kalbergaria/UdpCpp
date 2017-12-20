// External Libraries
#include <string.h>
#include <iostream>

using namespace std;

// System Files
#include "../K_Network/ThreadedUdpReceiver.h"

//
//
// Default Constructor
UDPReceiver::UDPReceiver() {}

//
//
// Constructor
UDPReceiver::UDPReceiver(int providedPortNumber, int providedBufferSize, int providedNumBuffers)
{
	// Init receiver
	sockaddrSize = sizeof(struct sockaddr);
	portNumber = providedPortNumber;
	InitializeUDPReceiver(providedPortNumber);

	// Record buffer and queue specs
	numBuffers = providedNumBuffers;
	qSize = providedNumBuffers;
	bufferSize = providedBufferSize;

	// Create data destination synchronization queues
	dataQ = new CharPtrQueue(providedNumBuffers);
	freeQ = new CharPtrQueue(providedNumBuffers);

	// Dynamically allocate space for the user-defined buffers
	dataBuffers = (char**)malloc(numBuffers * sizeof(char*));
	for (int bufferIndex = 0; bufferIndex < numBuffers; bufferIndex++)
	{
		dataBuffers[bufferIndex] = (char*)malloc(bufferSize * sizeof(char));
		freeQ->Enqueue(dataBuffers[bufferIndex]);
	}
}

//
//
//
UDPReceiver::~UDPReceiver()
{
	delete dataQ;
	delete freeQ;

	// delete the 2D array dataBuffers
    for(int i = 0; i < numBuffers; ++i)
        delete[] dataBuffers[i];
    delete[] dataBuffers;
}

//
//
//
void UDPReceiver::InitializeUDPReceiver(int portNumber)
{
	if ((mySocket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		printf("ThreadedUdpReceiver: error creating socket!\n");

	destinationAddr.sin_family = AF_INET;
	destinationAddr.sin_port = htons(portNumber);
	destinationAddr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(destinationAddr.sin_zero), 8);

	if (bind(mySocket, (struct sockaddr *)&destinationAddr, sizeof(struct sockaddr)) == -1)
		printf("ThreadedUdpReceiver: Binding error");
}

//
//
//
void UDPReceiver::ThreadMethod()
{
	while (true)
	{
		ReceiveData();
	}
}

//
//
// Receive obstruction data from the LIDAR Pis
void UDPReceiver::ReceiveData()
{
	//printf("Waiting for a message on port %d...\n", portNumber);

	// If there are no additional buffers available, resynchronize with the
	// data destination by emptying the dataQ
	ResyncFreeQAndDataQ();

	// Reserve a buffer to place the incoming data
	freeQ->Dequeue(&bufferBeingFilled);

	// Receive data and place in buffer
	bytesRead = recvfrom(mySocket, bufferBeingFilled, bufferSize, 0, (struct sockaddr *)&sourceAddr, &sockaddrSize);
	if(bytesRead < 0)
		cout << "An error occurred while receiving on port " << portNumber << endl;

	// Now that the buffer has been filled place it in the dataQ
	dataQ->Enqueue(bufferBeingFilled);
}

//
//
//
// TODO: What type does this need to be in order for me to be able to
// pass to return a char* two layers up?
bool UDPReceiver::GetDataBuffer(char** tempBufferPtr)
{
	bool dequeueFlag = false;

	if(!dataQ->IsEmpty())
	{
		dataQ->Dequeue(tempBufferPtr);
		dequeueFlag = true;
	}

	return dequeueFlag;
}

//
//
//
bool UDPReceiver::ReleaseDataBuffer(char* tempBufferPtr)
{
	return freeQ->Enqueue(tempBufferPtr);
}

//
//
//
void UDPReceiver::ResyncFreeQAndDataQ()
{
	if(freeQ->IsEmpty())
	{
		for (int elementNum = 0; elementNum < qSize; elementNum++)
		{
			dataQ->Dequeue(&bufferBeingFilled);
			freeQ->Enqueue(bufferBeingFilled);
		}
		//cout << "Resyncing was required on port " << portNumber << endl;
	}
}

int UDPReceiver::GetDataQOccupancy()
{
	int occupancy;
	dataQ->GetOccupancy(&occupancy);
	return occupancy;
}
