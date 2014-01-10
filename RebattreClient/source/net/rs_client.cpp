#include "rs_client.h"

#define TAG "[Client]"

SEED_SINGLETON_DEFINE(RSClient)

RSClient::RSClient()
	: iPort(3000)
	, cAddress(127, 0, 0, 1, iPort)
{
	sPacketData.vRemotePlayer = b2Vec2(100, 100);
}

RSClient::~RSClient()
{
}

void RSClient::Connect()
{
	// Create socket
	cSocket.Open(iPort);

	// Start comunication with other client
	int bytesRead = 0;
	cSocket.Send(cAddress, &sPacketData, sizeof(sPacketData));

	while(!bytesRead)
	{
		Address sender;
		bytesRead = cSocket.Receive(sender, &sPacketData, sizeof(sPacketData));
	}

	if(bytesRead)
		cSocket.Send(cAddress, &sPacketData, sizeof(sPacketData));
}

void RSClient::Receive()
{
	// Comunicate with other client
	Address sender;
	int bytesRead = cSocket.Receive(sender, &sPacketData, sizeof(sPacketData));

	if(bytesRead)
	{
		vEnemyPlayer = sPacketData.vRemotePlayer;
		vBall = sPacketData.vRemotePlayer;
	}
}

void RSClient::Disconnect()
{
	// Close socket
	cSocket.Close();
}

void RSClient::SetAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
	iPort = port;
	this->cAddress = Address(a, b, c, d, port);
}

Address RSClient::GetAddress()
{
	return this->cAddress;
}
