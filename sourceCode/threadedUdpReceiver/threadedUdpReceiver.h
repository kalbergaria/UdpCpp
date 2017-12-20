#ifndef THREADED_UDP_RECEIVER_H
#define THREADED_UDP_RECEIVER_H

// Extrernal Files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// System Files
#include "ThreadBase.h"
#include "CharPtrQueue.h"
#include "K_NetworkDefines.h"

class UDPReceiver : public ThreadBase
{
	public:
		// constructor
		UDPReceiver(int providedPortNumber, int providedBufferSize, int providedNumBuffers);
		~UDPReceiver();

		//public methods
		void InitializeUDPReceiver(int portNumber);
		void ThreadMethod();
		bool GetDataBuffer(char** tempBufferPtr);
		bool ReleaseDataBuffer(char* tempBufferPtr);
		int GetDataQOccupancy();

		// public data
		int portNumber;
		int numBuffers;
		int bufferSize;
		char** dataBuffers;
		int qSize;

	private:
		// default constructor is private so that it cannot be called
		// to instantiate the class
		UDPReceiver();

		// private methods
		void ReceiveData();
		void ResyncFreeQAndDataQ();

		// private data
		CharPtrQueue* freeQ;
		CharPtrQueue* dataQ;
		char* bufferBeingFilled;
		int mySocket;
		int port;
		int bytesRead;
		unsigned int sockaddrSize;
		struct sockaddr_in destinationAddr, sourceAddr;
		char dataReceived[MAX_UDP_SIZE_BYTES];
};

#endif
