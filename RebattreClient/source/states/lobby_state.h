#ifndef _LOBBY_STATE_H
#define _LOBBY_STATE_H

#include <Seed.h>

using namespace Seed;

class LobbyState : public StateMachineState
{
	public:
		LobbyState();
		virtual ~LobbyState();
		virtual void OnStart(void *);
		virtual void OnUpdate(f32);
		virtual void OnStop(void *);
};

#endif // _LOBBY_STATE_H
