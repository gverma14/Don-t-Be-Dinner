//The camera object utilizes the rendering features set up in class
//It also contains a render function that passes in a Player, and sets its coordinates equal to that


#include "camera.h"
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "player.h"

CameraObject::CameraObject()
{
    Initialize();
}

CameraObject::CameraObject(int ab)  
{
	test = ab;
	Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=1;
    z=0;
    h=0;
    p=-YsPi/20;
	p1 = p;
    b=0;
	l = 8.25;
	l1 = l;
    fov=30*YsPi/180;  // 30 degree
    nearZ=0.1;
    farZ=100;
}

void CameraObject::SetUpCameraProjection(int multi)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
	if(multi)
		aspect=(double)wid/(double)(hei/4);
	else
		aspect=(double)wid/(double)(hei/2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-x,-y,-z);
}

void CameraObject::Render(const Player &p)
{
	double cx=p.x-l*cos(p.t*3.141592/180);
	double cz=p.z+l*sin(p.t*3.141592/180);
	double ctheta=p.t;

	
	y = p.y+1;
	x = cx;
	z = -cz;
	h = (270-p.t)*YsPi/180;
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}
/*
voiid drawmodel_fish(void)
{
	if (!pmodel1) 
	{
		pmodel1 = glmReadOBJ("Amago.obj");	 //glm.cpp
        if (!pmodel1) exit(0);
		glmUnitize(pmodel1);				 //glm.cpp
		glmFacetNormals(pmodel1);			 //glm.cpp   
		glmVertexNormals(pmodel1, 90.0);     //glm.cpp
    }
    glmDraw(pmodel1, GLM_SMOOTH| GLM_TEXTURE);//glm.cpp
}

*/