//This brings up the end menu for the game

#ifndef ENDING_DEFINED
#define ENDING_DEFINED

class Ending
{
public:
	YsRawPngDecoder png;
	int windowWid, windowHei;

	void Initialize (void);
	void DrawHighScore (void);
	void DrawLogo (double x, double y); //bottom-left point
	void DrawCreditList (void);
};

#endif