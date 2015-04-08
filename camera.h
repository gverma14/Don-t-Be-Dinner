//The camera object utilizes the rendering features set up in class
//It also contains a render function that passes in a Player, and sets its coordinates equal to that

#ifndef CAMERA_DEFINED
#define CAMERA_DEFINED

const double pi = 3.14;
const double YsPi=3.1415927;

#include "player.h"

class CameraObject
{
public:
    double x,y,z;
    double h,p,b;

	int l1, p1, l2, p2, l3, p3;

    double fov,nearZ,farZ;
	int l;
	int test;
    CameraObject();
	CameraObject(int ab);
    void Initialize(void);
    void SetUpCameraProjection(int multi);
    void SetUpCameraTransformation();
	void Render(const Player &p);
    void GetForwardVector(double &vx,double &vy,double &vz);
	int camerano;
};

#endif