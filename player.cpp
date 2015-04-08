#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "player.h"
#include "button.h"
#include "boundary.h"
#include "mathfunc.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "glm.h"
#include <windows.h>
#include "stdafx.h"

	// Player class. 
	// Keeps track of the position, velocity, acceleration, angle, and angular velocity. 
	// Also limits the maximum velocities that it can go
	// Contains a button object, and takes in boundaries
	// Many functions that check for interactions between fish and hooks
	


const int speedLength=100;//Arbitrary length used to scale the player speeds
const double times=0.015;// Times is the timestep in seconds. (leave it at 0.01 plz)
const double pie=3.14159;// pi

double Player::getT()
{
	return t;
}

Player::Player()
{
	x0 = 0;
	z0 = 0;
	t=270.010;
	pt = -1;
	dragc = 1;
	goal = 2;
	bounceID=-1;
	switchtime = 500;
	y = .5;
	caught = 0;
	Reset();
}

Player::~Player()
{ 
}


void Player::Erase()
{
	Reset();
	pt=-1;//Change playertype to unknown type
}
void Player::Reset()
{
	// Reset to initial positions, angles, velocites etc.
	// (initial starting position x0 is not changed here)
	//printf("Stuffs reset\r");
	z=z0;
	x=x0;
	y = .5;
	goal = 2;//First goal is the third node
	t=270.010; //0.01 necesary to keep trig from breaking
	//printf("Reset  %lf\n", t);
	dt=0;
	Vp=0;
	Ap=0;
	usedtobeinabound=0;
	inabound=0;
	boundid='q';
	finish=0;
	caught = 0;
	camerano = 1;
}
void Player::SetPlayerType(int ptt)
{
	double leaderspeed=speedLength*times/4;// Leaders take 4 seconds to move 800 pixels
	// Save player type
	pt=ptt;
	dragc=1; // Drag coeff. (1=critical damping, >1: Over, <1: under
	goal = 2;
	switch( pt)
	{
	case 0://User
		Vmax=speedLength*times/.8;		// Takes 1 second to pass bounds at max speed
		Vmin=-speedLength*times/2;		// Takes 2 seconds to cross bounds going backwards
		Apmax=Vmax*times/1;		// Take 1s to reach max speed
		Apmin=-Vmax*times/0.5;	// 0.5 s to stop
		dtmax=360*times/2.0;	//1.2s to complete a spin
		ddtmax=dtmax*times/0.1;	//.1s to accelerate to max velocity
		break;
	case 1:
		Vmax=speedLength*times/1;		// Takes 1 second to pass bounds at max speed
		Vmin=-speedLength*times/2;		// Takes 2 seconds to cross bounds going backwards
		Apmax=Vmax*times/1;		// Take 1s to reach max speed
		Apmin=-Vmax*times/0.5;	// 0.5 s to stop
		dtmax=360*times/2.0;	//1.2s to complete a spin
		ddtmax=dtmax*times/0.1;	//.1s to accelerate to max velocity
		break;
	/*case 1://Racer
		Vmax=speedLength*times/1;		//Exactly the same as a User
		Vmin=-speedLength*times/2;		
		Apmax=Vmax*times/1;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/1.2;	
		ddtmax=dtmax*times/0.1;	
		break;*/
	case 2://Leader	
		Vmax=leaderspeed;		// Initiated above
		Vmin=-speedLength*times/1;		
		Apmax=Vmax*times/1;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/0.25;		
		ddtmax=dtmax*times/0.25;	
		break;
	case 3://Follower
		Vmax=leaderspeed*1.5;	// Seems to work pretty well
		Vmin=-speedLength*times/1;		
		Apmax=Vmax*times/1;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/1;		
		ddtmax=dtmax*times/.1;
		break;
	case 4://Hunter
		Vmax=speedLength*times/2;	
		Vmin=-speedLength*times/1;		
		Apmax=Vmax*times/0.4;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/0.75;		
		ddtmax=dtmax*times/.1;	
		break;	
	case 5://Prey
		Vmax=speedLength*times/2;	
		Vmin=-speedLength*times/1;		
		Apmax=Vmax*times/0.75;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/0.5;	
		ddtmax=dtmax*times/.1;	
		break;
	case 6://Spaz
		Vmax=speedLength*times/2;	
		Vmin=-speedLength*times/1;		
		Apmax=Vmax*times/1;		
		Apmin=-Vmax*times/0.5;	
		dtmax=360*times/1;		
		ddtmax=dtmax*times/.1;
		break;
	default://Shouldnt happen, if it does, print error
		Vmax=0;
		Vmin=0;
		Apmax=0;
		Apmin=0;
		dtmax=0;
		printf("Err: Unknown player type\n");
		break;
	}
}

void Player::Place(const Boundary &Path, const Boundary &BL, const Boundary &BR)
{
	//(z>Path.z[Path.length-3])&&(pt==0||pt==1)
	
	if(pt==1||pt==0)
	{
		do{
			//Place the player, and see if it is between the two boundaries
			x0=Path.x[3]*(double)(rand()%100)/100;	// create initial x coord
			z0=Path.z[3]*(double)(rand()%100)/100;	// create initial z coordinate
		}while(0==BetweenBounds(BL,BR,(int)x0,(int)z0)||!(z0<Path.z[2])||!(z0>Path.z[1]));
	}
	else
	{
		do{
			//Place the player, and see if it is between the two boundaries
			x0=Path.x[Path.length-1]*(double)(rand()%100)/100;	// create initial x coord
			z0=Path.z[Path.length-1]*(double)(rand()%100)/100;	// create initial z coordinate
		}while(0==BetweenBounds(BL,BR,(int)x0,(int)z0)||!(z0<Path.z[Path.length-2])||!(z0>Path.z[3]));
	}
	x=x0;
	z=z0;

		
}


void Player::Go(Player *P, int numplayers, const Boundary &Path, const Boundary &BLL,const Boundary &BL,const Boundary &BR,const Boundary &BRR, const Button &B, Hook h[],int numHooks)
{
	if(B.reset)
	{
		Reset();
	}

	if(caught)
	{
		Hook myHookobj = *myHook;

		y = myHookobj.getY();
		caught = myHookobj.caughtOrNot();
		
		if(!caught)
		{
			y = .5;
			z += myHookobj.getRadius()+2;
		}

	}
	else
	{
			//Does everything for the player
		//Works for every type of player. no specifications need to be given, just a lot of objects get passed in

		Input(B);//Keyboard input for all players

		//Player-Player interaction
		if(!finish)//The player hasn't finished
		{
			Race(Path);//Follow the path
			AI(P,numplayers);//Act
		}
		else
			Finished();		//Act finished
		Bounce(P,numplayers);	//Check for bounces between each player

		//Player-Env. Interaction
		DetectBoundary(BLL,BL);	//Check left boundary
		DetectBoundary(BR,BRR);	//Check right boundary
		DetectEndCond(Path);	//Check end line&beginning


	
		if(usedtobeinabound==1||inabound==1)
			MoveBound();
		else//if not in a boundary
			MoveDamp();
	
		//Combine all
		Move();
	
		//Check to see that the Players have not exicted the outer boundary
		Check(BLL, BL,Path,BR, BRR);
		CheckFinished(Path);//Check to see if the player is passed the ifinish line
		if(pt == 0)
		{
			CheckCollision(h, numHooks);
		}

	}
}

void Player::CheckCollision(Hook h[], int numHooks)
{
	
	for(int i = 0; i < numHooks; i++)
	{
		Hook tempHook = h[i];
		double dist = TrueDist(x,tempHook.getX(), z,tempHook.getZ());
		//printf ("%lf truedist  %lf radius\n", dist, tempHook.getRadius());
		if(dist < tempHook.getRadius())
		{
			//printf("Caught\n");
			caught = 1;
			h[i].catchFish();
			myHook = &(h[i]);
			break;
		}
	}

}

void Player::Input(const Button &B)
{
	
	
	// If Space Bar is pressed, Reset player
	if(B.reset)
		Reset();

	
	if(pt==0)//If the player is controlled by a user
	{
		
		// Find Forward/Backward Accel
		if(B.F&&!B.B)
		{	// Hitting the gas
				Ap=Apmax;
		}
		if(!B.F&&B.B)
		{
			if(Vp>=0)	// If hitting brake
				Ap=Apmin;	
			else		// If Backing up
				Ap=-Apmax;
		}
		if((!B.F&&!B.B)||(B.F&&B.B))
			Ap=0;
	
		// Find L/R turning
		if(B.L&&!B.R)
			ddt=-ddtmax;
		if(!B.L&&B.R)
			ddt=ddtmax; 
		if(!B.L&&!B.R)
			ddt=0;
		if(B.L&&B.R)
			ddt=0;
	}
}


void Player::Race(const Boundary &Path)
{
	//Racer types follow the racepath
	if(pt==1)//if a racer
	{
		double dist, alpha, dalpha, alpha2, dalpha2;
		int goal2;

		// Find the distance between the player and the next track node
		dist=TrueDist(Path.x[goal],x,Path.z[goal],z);
		// Find the difference between the current heading and the desired heading
		alpha=TrueAng(Path.x[goal],x,Path.z[goal],z);
		dalpha=FormAng(t-alpha,180);
		
		//Find the next for added weight
		goal2=goal+1;
		if(goal2>=Path.length)
			goal2=goal;
		alpha2=TrueAng(Path.x[goal2],x,Path.z[goal2],z);
		dalpha2=FormAng(t-alpha2,180);
		
		//If large angle, turn
		if(abs(dalpha)>5)
			ddt=-(dalpha/abs(dalpha)-abs(dt)/dtmax)*ddtmax;
		else //Prevent oscillations
			ddt=0;
		
		// A=kx+cX^.  --> first term is difference, second is damping
		Ap=Apmax;//*((50-abs(dalpha))/50*3/4+(50-abs(dalpha2))/50/4);

		if(dist<50)//If close to the node
		{
			goal++; //Aim for the next node
			if(goal>=Path.length)//If end is reached
			{ 
				goal=Path.length-1;
				ddt=0;
				Ap=0;
			}
		}
		Ap=Ap*(double)(rand()%3+8)/10;		//80% to 100% (adding variation)
		ddt=ddt*(double)(rand()%4+7)/10;	//70% to 100%
	}
}


void Player::AI(Player *P, int numplayers)
{
	int TID=ClosestPlayer(P,idno,numplayers);//Target ID number
	int per=rand()%3+1; //randomly 1 2 or 3, used to step some things
	double alpha, dalpha, dist;

	switch(pt)//Different actions for different player types
	{
	case 2://Leader
		Ap=Apmax*(double)(rand()%2+9)/10;//Accelerate 90-100%
		if(per==1)// about once every three seconds
			ddt=ddtmax*(double)(rand()%11-5)/5;//Turn maximum in a random direction
		else
			ddt=0;//No angular acceleration
		break;

	case 3://Follower
		// Find the angle between the player and the nearest leader
		alpha=TrueAng(P[TID].x,x,P[TID].z,z);
		//Find the distance between the leader and the follower
		dist = TrueDist(P[TID].x,x,P[TID].z,z);
		// Find the difference between the current heading and the desired heading
		dalpha=FormAng(t-alpha,180);
		if(dist<40)	//If close to the leader
			ddt=-(dalpha/abs(dalpha))*ddtmax;//no angular damping
		else
			ddt=-(dalpha/abs(dalpha)-abs(dt)/dtmax)*ddtmax;//Add angular damping to prevent oscillatons
		Ap=Apmax;//Maximize acceleration
		break;

	case 4://Hunter
		//Find the angle between the player and the nearest prey
		alpha=TrueAng(P[TID].x,x,P[TID].z,z);
		// Find the distance between the player and the closest prey
		dist = TrueDist(P[TID].x,x,P[TID].z,z);
		// Find the difference between the current heading and the desired heading
		dalpha=FormAng(t-alpha,180);

		if(dist>100)//If far away, stop moving
		{
			ddt=0;
			Ap=0;
		}
		else if(dist>50)//if between 50 and 100, chase the prey
		{
			ddt=-dalpha/abs(dalpha)*ddtmax;
			Ap=Apmax;
		}
		else//if very close
		{
			dt=-dalpha/abs(dalpha)*ddtmax;
			Ap=Apmax*(dist-25)/25;//Try to stay on top of it (not perfect)
		}
		break;

	case 5://Prey
		//Find the angle between the player and the nearest hunter
		alpha=TrueAng(P[TID].x,x,P[TID].z,z);
		// Find the distance between the player and the closest hunter
		dist = TrueDist(P[TID].x,x,P[TID].z,z);
		// Find the difference between the current heading and the desired heading
		dalpha=FormAng(t-alpha+180,180);

		if(dist>90)//Relaxing
		{
			Ap=Apmax*(double)(rand()%2+3)/10;
			if(per==1)// about once every three seconds
				ddt=ddtmax*(double)(rand()%11-5)/5;//Spin randomly
			else
				ddt=0;
		}
		else if (dist>30)//Running
		{			
			Ap=Apmax*(double)(rand()%2+9)/10;
			if(per>=1)// about once every three seconds
				ddt=ddtmax*(double)(rand()%11-5)/5;//Evade
			else
				ddt=0;
		}
		else// Caught (option to change this to something else)
		{
			Ap=Apmax*(double)(rand()%2+9)/10;//Keep running
			if(per==1)// about once every three seconds
				ddt=ddtmax*(double)(rand()%11-5)/5;
			else
				ddt=0;
		}
		break;

	case 6://Spaz
		//Randomly move
		Ap=(((double)(rand()%11))/20+0.5)*Apmax;
		if(per>2)
		{
			ddt=((double)(rand()%11)/5-1)*ddtmax;
		}
		break;

	default://Any non player based AI or Users
		//printf("error#Derpaderp");
		break;
	}
}


void Player::Finished()
{
	Ap=0;//Stop acceleration
	ddt=0;//Stop turning
}


void Player::Bounce(Player *P, int numplayers)
{
	//Bounces certain players apart
	int racerdist=1;//each player has a radius of 5 at the moment
	int leaderdist=3;//each player has a radius of 5 at the moment
	int count , tempbouncecount=0;
	double dt;
	double temp1,temp2;
	for(count=idno+1; count<numplayers;count++)
	{	
		//For all following players
		if(idno!=count)//Not the same player
		{
			if((pt==1||pt==0)&&(P[count].pt==1||P[count].pt==0))
			{
				if(TrueDist(P[count].x,x,P[count].z,z)<racerdist)//If collision detected
				{	
					if(bounceID!=P[count].idno)
					{
						//Racer and user types must bounce and swap velocites (essentially) but also depends on the angle and velocity
						bounceID=idno;
						dt=FormAng(P[count].t-t,360);
						temp1=-Vp*abs(sin(dt*pie/180))+P[count].Vp*cos(dt*pie/180);
						temp2=-P[count].Vp*abs(sin(dt*pie/180))+Vp*cos(dt*pie/180);
						Vp=temp1;
						P[count].Vp=temp2;
						tempbouncecount=1;
					}
				}
			}
			else if((pt==1||pt==0)&&(P[count].pt==2||P[count].pt==3))
			{
				if(TrueDist(P[count].x,x,P[count].z,z)<leaderdist)//If collision detected
				{	
					//If a user or racer hits a follower or leader, slow down
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					MoveDamp();
					tempbouncecount=1;
				}
			}
		}
	}
	if(tempbouncecount==0)
		bounceID=-1;

}


void Player::DetectBoundary(const Boundary &BL, const Boundary &BR)
{
	//Check each segment of a boundary as a polygon to make sure that the player is not in it
	int count; // Counting variable for the number of segments in the boundary
	double x1,x2,x3,x4,z1,z2,z3,z4;//Four corners of the segment
	double m1,m2,m3,m4;//slopes of each line segment
	double line1,line2,line3,line4;
	double currin=0;//Currently in the boundary flag
	double tempt=0;//Temporary theta value
	for(count=0;count<=BR.length-2;count++)	// Check the location for every section in the boundary
	{
		x1=BL.x[count];
		z1=BL.z[count];
		x2=BR.x[count];
		z2=BR.z[count];
		x3=BR.x[count+1];
		z3=BR.z[count+1];
		x4=BL.x[count+1];
		z4=BL.z[count+1];
	
		//x=mz+b   m=dx/dz   b=x1-m*z1  x=m(z-z1)+x1
		m1=((x1-x2)/(z1-z2));
		m2=((x2-x3)/(z2-z3));
		m3=((x3-x4)/(z3-z4));
		m4=((x4-x1)/(z4-z1));

		line1=m1*(z-z1)+x1;
		line2=m2*(z-z2)+x2;
		line3=m3*(z-z3)+x3;
		line4=m4*(z-z4)+x4;

		if( ((x>line3&&x<line1&&(m3>0&&m1>0))||
			(x>line3&&x>line1&&(m3>0&&m1<0))||
			(x<line3&&x<line1&&(m3<0&&m1>0))||
			(x<line3&&x>line1&&(m3<0&&m1<0)))&&
			((line2<line4&&x>line2&&x<line4)||
			(line2>line4&&x<line2&&x>line4)))//If between line3 and line1 and line 2 and line 4.
		{
				currin=1;//currently in a boundary
				tempt=2*atan(1/m2)*180/3.141592;//Calculate the bounce angle that it ould have to take
		}
	//printf("C:%d  x: %lf  z: %lf  l1: %lf  l2: %lf  l3: %lf  l4: %lf  \n",count,x,z,line1,line2,line3,line4);//For debugging purposes
	}
	if(currin==1&&boundid==BL.side)
	{
		//If in the boundary that you were previously in
		inabound=1;
		tboundtemp =tempt;
	}
	else if(currin==1&&boundid!=BL.side)
	{
		inabound=1;
		boundid=BL.side;//Save current boundary name
		tboundtemp =tempt;
	}
	else if(currin==0&&boundid==BL.side)
	{
		inabound=0;//If you were previously in this boundary, and are no longer. Reset inabound
	}
}

void Player::DetectEndCond(const Boundary &Path)
{
	//Assumes that the end boundaries are flat, and are the 2nd to last element in path
	double currin=0;
	double tempt=0;
	if(z>Path.z[Path.length-2]||z<Path.z[1])//If passed the end boundary
	{
		currin=1;
		tempt=0;
	}
	if(currin==1&&boundid==Path.side)//If previously in the end boundary
	{
		inabound=1;
		tboundtemp =tempt;
	}
	else if(currin==1&&boundid!=Path.side)
	{
		inabound=1;
		boundid=Path.side;//Save the name of the boundary youre passing
		tboundtemp =tempt;
	}
	else if(currin==0&&boundid==Path.side)
	{
		inabound=0;//If previously in the end boundary, reset it
	}
}

void Player::MoveBound()//Move if a boundary has been crossed
{
	if(inabound==1&&usedtobeinabound==0)//If first time in a boundary, save Vbound, tbound
	{
		if(pt==0)//If user, bounce back
		{
			if(abs(Vp)>abs(Vmax)/10)
				Vbound=-Vp;
			else if(abs(Vp)<abs(Vmax)/10)//Prevents the user from slowing to a crawl to get throught the barrier
				Vbound=-Vp/abs(Vp)*abs(Vmax)/9;
			Vp=Vbound; 
			Ap=0;
			tbound=t;
		}
		if(pt!=0)//else, reflect
		{
			if(abs(Vp)>abs(Vmax)/10)
				Vbound=Vp;
			else if(abs(Vp)<abs(Vmax)/10)
				Vbound=Vp/abs(Vp)*abs(Vmax)/9;
			Vp=Vbound; 
			Ap=0;
			tbound=	-tboundtemp -t;
			dt=0;
			ddt=0;
			t=tbound;
		}
		usedtobeinabound=1;//Remember that youve been through a boundary
	}
	else if(inabound==1&&usedtobeinabound==1)
	{
		//Every other time youre in the boundary
		Ap=0;
		Vp=Vbound;
		t=tbound;
	}
	else if(inabound==0&&usedtobeinabound==1)//If you used to be in the boundary, and youre not anymore
		usedtobeinabound=0;
}
void Player::MoveDamp()
{
	// Motion takes the acceleration and dt and calculates a new position. 
	double Vdamp=(Vmax/Apmax)*(Vmax/Apmax)*times*times*times*dragc;
	//Damping coefficient
	// Slow down the player (drag/damping)
	if(Vp>0)
	{
		Ap-=Apmax*Vp/Vmax*4/5+Apmax*1/5; //always remove apmax/5 (to help with hystoresis) 
	}	
	else if(Vp<0)
	{
		Ap+=abs(Vp)*Vmax/abs(Vmin)*Vdamp*4/5+Vmax*Vdamp*1/5;//Same as above
	}
	if((Vp+Ap<0&&Vp>0)||(Vp+Ap>0&&Vp<0))
	{
		//If the velocity would pass 0, stop the player
		Vp=0;
		Ap=0;
	}
	if(dt>0)//Angular damping
		ddt-=dt*ddtmax/dtmax;
	if(dt<0)
		ddt-=dt*ddtmax/dtmax;
}


void Player::Move()//Calculate the new position
{
	//Check Ap
	if(Ap>Apmax)
		Ap=Apmax;
	else if (Ap<Apmin)
		Ap=Apmin;

	Vp+=Ap;//Calc Velocity

	// Check Velocity
	if(Vp>Vmax)
		Vp=Vmax;
	if(Vp<Vmin)
		Vp=Vmin;

	//Check ddt
	if(ddt>ddtmax)
		ddt=ddtmax;
	else if (ddt<-ddtmax)
		ddt=-ddtmax;	

	dt=dt+ddt;//Calculate dt

	//Check dt
	if(dt>dtmax)
		dt=dtmax;
	else if (dt<-dtmax)
		dt=-dtmax;

	t+=dt;//Calc new angle

	// Keep the angle t between 0 and 360. 
	if(t>360)
		t-=360;
	if(t<0)
		t+=360;

	// Calculate new position
	x+=Vp*cos(-t*3.141592/180);
	z+=Vp*sin(-t*3.141592/180);

	//Camera coordinates
	double l=8.25;// Distance between player and camera
	cx=x-l*cos(t*3.141592/180);
	cz=z+l*sin(t*3.141592/180);
	ctheta=t;
}

void Player::Check(const Boundary &BLL, const Boundary &BL, const Boundary &Path, const Boundary &BR,const Boundary &BRR)
{
	//Check that the player is between any two of the boundaries
	if(0==(BetweenBounds(BLL,BL,x,z)+BetweenBounds(BL,Path,x,z)+BetweenBounds(Path,BR,x,z)+BetweenBounds(BR,BRR,x,z)))
		Reset();
}

void Player::CheckFinished(const Boundary &Path)
{
	if((z>Path.z[Path.length-3])&&(pt==0||pt==1))//If racer or user, and the player has gone above the top point on the path
	{
		finish=1;//Race has finished
	}
}



int Player::ClosestPlayer(Player *P, int pid,int tot)
{
	//Find the closest player of interest
	int id=-1;//PlayerID
	int n;
	double dist;
	double olddist=8000000;
	int type=-1;
	//Different target types for different player types
	switch( P[pid].pt)
	{
	case 3://Follower
		type=2;
		break;
	case 4://Hunter
		type=5;
		break;	
	case 5://Prey
		type=4;
		break;
	default://Everything else
		break;
	}
	//Check every player
	for(n=1;n<=tot;n++)
	{
		if(n!=pid)//Ignore the original player
		{
			if(P[n].pt==type)//If it is the correct type
			{
				dist= TrueDist(P[pid].x,P[n].x,P[pid].z,P[n].z);
				if(dist<olddist)//check to see if it is closer than the last one
				{
					olddist=dist;//save it
					id=n;
				}
			}
		}
	}
	if(id==-1)//If not really looking
		return -1;
	else//Return the target ID number
		return id;
}



GLMmodel* pmodel1 = NULL;
GLMmodel* pmodel2 = NULL;
GLMmodel* pmodel3 = NULL;
GLMmodel* pmodel4 = NULL;


void Player:: drawmodel_fish(void)
{
	glTranslatef(x, y, -z);
	glRotatef(180-t,0,1,0);
	
	
	if (!pmodel1) 
	{
		pmodel1 = glmReadOBJ("test3.obj");	 //glm.cpp
        if (!pmodel1) exit(0);
		//glmUnitize(pmodel1);				 //glm.cpp
		glmFacetNormals(pmodel1);			 //glm.cpp   
		glmVertexNormals(pmodel1, 90.0);     //glm.cpp
    }
	
   glmDraw(pmodel1, GLM_SMOOTH| GLM_TEXTURE);//glm.cpp
	
}


void Player:: drawmodel_fish_mod()
{
	glTranslatef(x, y, -z);
	glRotatef(180-t,0,1,0);

	if (!pmodel2) 
	{
		pmodel2 = glmReadOBJ("fishLL.obj");	 //glm.cpp
        if (!pmodel2) exit(0);
	//	glmUnitize(pmodel1);				 //glm.cpp
		glmFacetNormals(pmodel2);			 //glm.cpp   
		glmVertexNormals(pmodel2, 90.0);     //glm.cpp
    }

    glmDraw(pmodel2, GLM_SMOOTH| GLM_TEXTURE);//glm.cpp
	
}

void Player:: drawmodel_fish_mod2()
{

	
	glTranslatef(x, y, -z);
	glRotatef(180-t,0,1,0);

	if (!pmodel3) 
	{
		//printf("Loaded\n");
		pmodel3 = glmReadOBJ("fishRR.obj");	 //glm.cpp
        if (!pmodel3) exit(0);
	//	glmUnitize(pmodel1);				 //glm.cpp
		glmFacetNormals(pmodel3);			 //glm.cpp   
		glmVertexNormals(pmodel3, 90.0);     //glm.cpp
    }

    glmDraw(pmodel3, GLM_SMOOTH| GLM_TEXTURE);//glm.cpp
	
}

void Player::drawmodel_fish_AI()
{
	
	double x1 = x-2;
	double x2 = x+2;
	double y1 = y;
	double y2 = y+10;
	double z1 = -(z-2);
	double z2 = -(z+2);

	
	
	glTranslatef(x, y, -z);
	glRotatef(180-t,0,1,0);

	if (!pmodel4) 
	{
		//printf("Simple Loaded\n");
		pmodel4 = glmReadOBJ("test3.obj");	 //glm.cpp
        if (!pmodel4) exit(0);
	//	glmUnitize(pmodel1);				 //glm.cpp
		glmFacetNormals(pmodel4);			 //glm.cpp   
		glmVertexNormals(pmodel4, 90.0);     //glm.cpp
    }

    glmDraw(pmodel4, GLM_SMOOTH| GLM_TEXTURE);//glm.cpp
	


}

void Player::drawfishes(int runtime)
{
	if(pt == 0)
	{
		glColor3ub(35,234,23);
		int runt = runtime%switchtime;

		if(runt >=0 && runt < switchtime/4)
		{
				drawmodel_fish();
		}
		else if (runt >=switchtime/5 && runt < 2*switchtime/4)
		{
			drawmodel_fish_mod2();
		
		}
		else if(runt >=2*switchtime/5 && runt < 3*switchtime/4)
		{
			drawmodel_fish();
		}
		else if(runt >=3*switchtime/5 && runt < 4*switchtime/4-1)
		{
			drawmodel_fish_mod();
		}
	}

	else
	{
		if(pt == 1)
		{
			glColor3ub(255,0,0);
		}
		else
			glColor3ub(255,10,200);
		drawmodel_fish_AI();
		//drawmodel_fish();
	}
        	
	glEnd();

}


void Player::Draw(int runtime)
{
	glPushMatrix();		
	glColor3ub(0,100,255);
	drawfishes(runtime);
	glPopMatrix();
}
