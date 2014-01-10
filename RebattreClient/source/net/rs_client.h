#ifndef _RS_CLIENT_H
#define _RS_CLIENT_H

#include <Seed.h>
#include <api/net/Socket.h>
#include <Box2D/Box2D.h>

using namespace Seed;
using namespace Seed::Net;

class RSClient
{
	SEED_DECLARE_SINGLETON(RSClient)
	SEED_DISABLE_COPY(RSClient)

	public:
		struct PacketData
		{
			b2Vec2 vBall;
			b2Vec2 vRemotePlayer;
		} sPacketData;

		enum ePlayerNumber {PlayerOne = 1, PlayerTwo = 2};

		void Connect();
		void Receive();
		void Disconnect();
		b2Vec2 vBall;
		b2Vec2 vEnemyPlayer;
		Socket cSocket;
		int iIDPlayer;
		void SetAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
		Address GetAddress();


	private:
		int iPort;
		Address cAddress;

};

#define pRSClient RSClient::GetInstance()

#endif // _RS_CLIENT_H
