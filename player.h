

#ifndef PLAYER_IS_INCLUDED
#define PLAYER_IS_INCLUDED

#include "button.h"
#include "fssimplewindow.h"
#include "boundary.h"
#include "hook.h"

class Player
{
	// Player class. 
	// Keeps track of the position, velocity, acceleration, angle, and angular velocity. 
	// Also limits the maximum velocities that it can go
	// Contains a button object, and takes in boundaries
	// Many functions that check for interactions between fish and hooks
	
public:
	int pt,idno;	//Player type and ID number

	int usedtobeinabound,inabound;	//Boundary Flags
	char boundid;					//Boundary Flag
	double Vbound,tbound,tboundtemp;//Boundary Velocities

	int bounceID;//Boundary Velocities
	
	int goal,finish;		//Flags for the gmae
	
	double x,z,x0,z0;		//x and z positions, initial positions
	double y;
	double Vp,Vmax,Vmin;	//Velocity, and limits
	double Ap,Apmax,Apmin;	//Acceleration and limits
	double t;				//Theta (relative to -> direction)
	double dt,dtmax;		//Angular velocity and limit
	double ddt, ddtmax;		//Angular acceleration and limit
	double dragc;			//Drag coefficient, Should not be used
	int switchtime;
	double cx, cz, ctheta;	//Camera Position
	int caught;
	double getT();	//Someone else added this...
	void CheckCollision(Hook h[], int numHooks);
	Player();				
    ~Player();				

	void drawmodel_fish_AI();
	void Erase();			//Fracks up a player

	void Reset();			//Reverts the player to its starting condition
	int camerano;
	void SetPlayerType(int ptt);	//Sets player type and player specific variables
	void Place(const Boundary &path,const Boundary &BL,const Boundary &BR);	//Gives the player a random position within the map according to its type
	
	//Function that is used by game 
	void Go(Player *P, int numplayers,const Boundary &Path,const Boundary &BLL,const Boundary &BL,const Boundary &BR,const Boundary &BRR, const Button &B, Hook h[],int numHooks);
	
	void Input(const Button &B) ;				//Button inputs
	void Race(const Boundary &Path) ;			//Racer types path following function
	void AI(Player *P, int numplayers);			//All other non user types behave based on this function
	void Finished();							//Action to take if the player has passed the finish line
	void Bounce(Player *P, int numplayers);		//Handles the interaction between two players
	void DetectBoundary(const Boundary &BL,const Boundary &BR) ;//Determines if the player has hit a boundary
	void DetectEndCond(const Boundary &Path);	//Determines if a player has passed the beginning or end boundary
	void MoveBound();							//Moving function if a boundary has been crossed
	void MoveDamp();							//Introduce damping if the player has not crossed a boundary
	void Move();								//Physically change the coordinates of the player according to the previous functions
	void Check(const Boundary &BLL,const Boundary &BL,const Boundary &Path,const Boundary &BR,const Boundary &BRR) ;//Check to see if the player hasexited the map
	void CheckFinished(const Boundary &Path) ;	//Check to see if the player has passed the end

	int ClosestPlayer(Player *P, int idno, int numplayers);	// Function that will return the closest player of interest to the actual player
	
	void Draw(int runtime);	//Draws the player
	void drawmodel_fish(void);
	void drawmodel_fish_mod();
	void drawmodel_fish_mod2();
	void drawfishes(int runtime);
	Hook* myHook;



};

#endif