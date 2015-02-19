#ifndef _SYSTEMCONTROLLER_H_
#define _SYSTEMCONTROLLER_H_

class SystemController
{
private:

public:
	SystemController();
	SystemController(const SystemController&);
	~SystemController();


	//Controller Funktionen
	void closeFrame();
	void moveCamera(float left, float right, float top, float bottom);
	void rotateZ(float angle);
};

#endif