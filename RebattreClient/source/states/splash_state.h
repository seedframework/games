#ifndef _SPLASH_STATE_H
#define _SPLASH_STATE_H

#include <Seed.h>
using namespace Seed;

class SplashState : public StateMachineState
{
	public:
		SplashState();
		virtual ~SplashState();
		virtual void OnStart(void *);
		virtual void OnUpdate(f32);
		virtual void OnStop(void *);

	private:
		u64 iBeginStateTime;
};

#endif // _SPLASH_STATE_H
