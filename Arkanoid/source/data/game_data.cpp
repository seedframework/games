#include "game_data.h"

GameData::GameData()
	: sPlayer()
	, sOptions()
{
	sPlayer.iLeftPlayerPoints = 0;

	sOptions.bSfxEnabled = true;
	sOptions.bBgmEnabled = true;
	sOptions.fSfxVol = 1.0f;
	sOptions.fBgmVol = 1.0f;
}

GameData::~GameData()
{
}

u32 GameData::GetLeftPlayerPoints() const
{
	return sPlayer.iLeftPlayerPoints;
}

void GameData::SetLeftPlayerPoints(const u32 points)
{
	sPlayer.iLeftPlayerPoints = points;
}

bool GameData::IsSfxEnabled() const
{
	return sOptions.bSfxEnabled;
}

void GameData::SetSfxEnabled(bool b)
{
	sOptions.bSfxEnabled = b;
}

bool GameData::IsBgmEnabled() const
{
	return sOptions.bBgmEnabled;
}

void GameData::SetBgmEnabled(bool b)
{
	sOptions.bBgmEnabled = b;
}

bool GameData::IsFullScreenEnabled() const
{
	return sOptions.bFullScreenEnabled;
}

void GameData::SetFullScreenEnabled(bool b)
{
	sOptions.bFullScreenEnabled = b;
}

f32 GameData::GetSfxVolume() const
{
	return sOptions.fSfxVol;
}

void GameData::SetSfxVolume(f32 v)
{
	sOptions.fSfxVol = v;
}

f32 GameData::GetBgmVolume() const
{
	return sOptions.fBgmVol;
}

void GameData::SetBgmVolume(f32 v)
{
	sOptions.fBgmVol = v;
}
