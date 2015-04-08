//Contains functions for maintaining the time throughout the game
//Can start, stop, pause, reset

#ifndef STOPWATCH_IS_INCLUDED
#define STOPWATCH_IS_INCLUDED

class Stopwatch
{
public:
    int timing;
    double runtime;
    double lasttime;
    int milli, sec,min;
    char tt[256];
    
    
    Stopwatch();
    ~Stopwatch();
    void initialize();
    void cleanup();
    void resettimer();
    void starttimer();
    void pausetimer();
    void updatetimer();
    void Draw();
    
    
};

#endif
