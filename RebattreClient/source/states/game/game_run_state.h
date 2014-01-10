#ifndef _GAME_RUN_STATE_H
#define _GAME_RUN_STATE_H

#include <Seed.h>
using namespace Seed;

class GameRunState : public StateMachineState
{
	public:
		GameRunState();
		virtual ~GameRunState();
		virtual void OnStart(void *);
		virtual void OnUpdate(f32);
		virtual void OnStop(void *);
};

#endif // _GAME_RUN_STATE_H
