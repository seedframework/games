#ifndef RS_DATA_H
#define RS_DATA_H

class RSData
{
	public:
		struct PacketData
		{
			int iID;
			float fBallPosX;
			float fBallPosY;

			float fPlayerLeftX;
			float fPlayerLeftY;
			float fPlayerRightX;
			float fPlayerRightY;
		} sPacketData;

	public:
		RSData();
		virtual ~RSData();
};

#endif // RS_DATA_H
