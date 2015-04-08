//Responsible for reading in the track coordinates from text file
//Retrieves them and then outputs them to the Boundary class


#ifndef TRACK_IS_INCLUDED
#define TRACK_IS_INCLUDED


class StringParser
{
protected:
	char *str;
	int nWord;
	int *wordTop, *wordLength;
    
	int ParseString (int &nWord, int wordTop[], int wordLength[], char str[], int maxNumWords);
	void SafeStrCpy (char dst[], char src[], int nLetters, int nLimit) const; //const member functions
    
public:
	StringParser();
	~StringParser();
    
	void CleanUp (void);
	int SetStringAndParse (const char str[]);
	int GetNumWords (void) const;
	void GetWord (char word[], int maxLength, int nthWord) const;
};


class Map
{
public:
	void DrawGround (void);
    void DrawRotateWall(double x1, double x2, double x3, double x4, double z1, double z2,double z3, double z4, double y1,double h);
};


class Vec//essentially coordinates
{
public:
	int x, y, z;
};

class Polyg//a list of coordinates
{
public:
	Polyg();
	~Polyg();
    
	int nVertex;
	Vec *vertex;//Centerline
	int ReadFromFile (char fn[]);
	void Clear();
};

class Point//Each point keeps track of x,y,or z at a specific node for all 5 boundaries
{
public:
	double center, leftIn, leftOut, rightIn, rightOut;
};


// input 2 points(one line) + road width + wall height + wall width, output a track
class PathPlanning : public Map, public Polyg
{
public:
	Map map;
	Polyg plg;
	Point x[256], y[256], z[256]; //will be read from txt file 
    
	int *centerx, *centerz, *leftx, *leftz, *lleftx, *lleftz, *rightx, *rightz, *rrightx, *rrightz;//permanent track coordinates
	double roadWid, wallWid, wallHei;
	void SetTrackProperty (void);
	void DrawTrackCenterLine (void);
	void DrawTrackWall (void);
	void DrawTrackGround (void);
	void Draw(void);
	void fillUpBArray();
	PathPlanning();
};
#endif