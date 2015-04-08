


// The Button class manages all the button inputs for the game, all of the buttons are mapped to specific variables 
// This ensures that specific players, or the game itself only can use these buttons

#ifndef BUTTON_IS_INCLUDED
#define BUTTON_IS_INCLUDED

#include "yspng.h"

class Button
{ 
	// Button class objects allow us to quickly get the state of buttons
public:
	int U,D,L,R,F,B,E,S,SU,SD,SL,SR,SF,SB;
	int SU1,SD1,SL1,SR1,SF1,SB1;
	int SU2,SD2,SL2,SR2,SF2,SB2;
	int GP, GR, GC;
	int G1, G2;
	int pause, reset, cont, one, two;

	// Up, Down, Left, Right, Forward, Backward, Escape, Space
    Button();
    ~Button();
    
	YsRawPngDecoder png;
	int windowWid, windowHei;

	void DrawBackground (void);
	void DrawModeTitle1 (void);
	void DrawModeTitle2 (void);
	void DrawKeyboardSetting (void);
	void DrawLogo (double x, double y);
	int checkGameControl(int key);

	void Player1Button();
	void Player2Button();
    void Reset();
    void Update();
    void Remap();
    void Remap2();
    void Default();
    void Default2();

    void Initialize();
};
#endif