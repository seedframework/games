#ifndef _GAME_DATA_H
#define _GAME_DATA_H

#include "../defines.h"

class GameData
{
	public:
		GameData();
		~GameData();

		u32 GetLeftPlayerPoints() const;
		void SetLeftPlayerPoints(u32);

		bool IsSfxEnabled() const;
		void SetSfxEnabled(bool);

		bool IsBgmEnabled() const;
		void SetBgmEnabled(bool);

		bool IsFullScreenEnabled() const;
		void SetFullScreenEnabled(bool);

		f32 GetBgmVolume() const;
		void SetBgmVolume(f32 v);

		f32 GetSfxVolume() const;
		void SetSfxVolume(f32 v);

		struct PlayerData
		{
			u32 iLeftPlayerPoints;
			bool bGameOver;
		} sPlayer;

		struct OptinsData
		{
			bool bSfxEnabled;
			bool bBgmEnabled;
			bool bFullScreenEnabled;
			f32 fSfxVol;
			f32 fBgmVol;
		} sOptions;
};

#endif // _GAME_DATA_H
