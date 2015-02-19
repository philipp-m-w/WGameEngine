#ifndef _SYSTEMCONTROLLER_H_
#define _SYSTEMCONTROLLER_H_

#include "display.h"
#include "input.h"

class SystemController
{
private:
	Display* display;
	InputController* inputController;

public:
	SystemController();
	SystemController(const SystemController&);
	~SystemController();

	bool Initialize();
	bool Shutdown();
	bool StartDisplaying();


	//Controller Funktionen
	void closeFrame();
	void moveCamera(float left, float right, float top, float bottom);
	void rotateZ(float angle);
};

#endif