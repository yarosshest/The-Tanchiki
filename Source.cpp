#include "Engine.h"
int main()
{
	do
	{
		Engine engine;
		engine.start();
		if (!engine.GameRestart)
			return 0;
	} while (true);
}