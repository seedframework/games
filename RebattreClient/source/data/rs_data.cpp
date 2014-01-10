#include "rs_data.h"

RSData::RSData()
{
	sPacketData.iID = 1;

	sPacketData.fBallPosX = 0;
	sPacketData.fBallPosY = 0;

	sPacketData.fPlayerLeftX = -10;
	sPacketData.fPlayerLeftY = 0;

	sPacketData.fPlayerRightX = 0;
	sPacketData.fPlayerRightY = 0;
}

RSData::~RSData()
{
}
