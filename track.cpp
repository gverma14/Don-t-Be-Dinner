//Responsible for reading in the track coordinates from text file
//Retrieves them and then outputs them to the Boundary class


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "track.h"

const double YsPi=3.1415927;

StringParser::StringParser()
{
	str=NULL;
	nWord=0;
	wordTop=NULL;
	wordLength=NULL;
}

StringParser::~StringParser()
{
	CleanUp();
}

int StringParser::ParseString (int &nWord, int wordTop[], int wordLength[], char str[], int maxNumWords)
{
	int i, state;
	state=0;
	nWord=0;
    
	for (i=0; str[i]!=0; i++)
	{
		switch (state)
		{
            case 0:
                if (str[i]!=' ' && str[i]!='\t' && str[i]!=',' && str[i]!='\n')
                {
                    state=1;
                    wordTop[nWord]=i;
                    wordLength[nWord]=1;
                    nWord++;
                }
                break;
            case 1:
                if (str[i]!=' ' && str[i]!='\t' && str[i]!=',' && str[i]!='\n')
                {
                    wordLength[nWord-1]++;
                }
                else
                {
                    state=0;
                    if (nWord==maxNumWords)
                    {
                        goto LOOPOUT;
                    }
                }
                break;
		}
	}
LOOPOUT:
	return nWord;
}

void StringParser::SafeStrCpy (char dst[], char src[], int nLetters, int nLimit) const
{
	int i, stopper;
	if (nLetters<nLimit)
	{
		stopper=nLetters;
	}
	else
	{
		stopper=nLimit;
	}
    
	for (i=0; i<stopper; i++)
	{
		dst[i]=src[i];
	}
	dst[stopper]=0;
}

void StringParser::CleanUp (void)
{
	if (NULL!=str)
	{
		delete [] str;
		str=NULL;
	}
	if (NULL!=wordTop)
	{
		delete [] wordTop;
		wordTop=NULL;
	}
	if (NULL!=wordLength)
	{
		delete [] wordLength;
		wordLength=NULL;
	}
	nWord=0;
}

int StringParser::SetStringAndParse (const char inputStr[])
{
	if (NULL!=inputStr)
	{
		CleanUp();
        
		int n=strlen (inputStr);
		str=new char [n+1];
		wordTop=new int [n/2];
		wordLength=new int [n/2];
        
		if (NULL!=str && NULL!=wordTop && NULL!=wordLength)
		{
			strcpy (str, inputStr);
			ParseString (nWord, wordTop, wordLength, str, n);
			return nWord;
		}
		else
		{
			CleanUp();
		}
	}
	return 0;
}

int StringParser::GetNumWords (void) const
{
	return nWord;
}

void StringParser::GetWord (char word[], int maxLength, int nthWord) const
{
	if (NULL!=word)
	{
		if (0<=nthWord && nthWord<nWord)
		{
			SafeStrCpy (word, str+wordTop[nthWord], wordLength[nthWord], maxLength);
		}
		else
		{
			word[0]=0;
		}
	}
}



void Map::DrawGround (void)//Draws lines across the ground
{
	glBegin (GL_LINES);
	int x;
	int spacing = 20;
	for (x=-1000; x<=1000; x+=spacing)//1000x1000 grid
	{
		glVertex3i (   x , 0, -1000);//z lines
		glVertex3i (   x , 0,  1000);
		glVertex3i (-1000, 0,  x   );//x lines
		glVertex3i ( 1000, 0,  x   );
	}
	glEnd();
}

void Map::DrawRotateWall (double x1, double z1, double x2, double z2, 
                          double x3, double z3, double x4, double z4, double y1, double h)
{
	//Draws a rectangular prism with based on four (x,z) coordinates, an initial y and a height

	glBegin (GL_QUADS);

	glVertex3d (x1, y1+h, z1);
	glVertex3d (x4, y1+h, z4);
	glVertex3d (x3, y1+h, z3);
	glVertex3d (x2, y1+h, z2);
    
    glVertex3d (x1, y1, z1);
	glVertex3d (x2, y1, z2);
	glVertex3d (x2, y1+h, z2);
	glVertex3d (x1, y1+h, z1);
    
    glVertex3d (x1, y1, z1);
	glVertex3d (x4, y1, z4);
	glVertex3d (x4, y1+h, z4);
	glVertex3d (x1, y1+h, z1);
    
    glVertex3d (x4, y1, z4);
	glVertex3d (x3, y1, z3);
	glVertex3d (x3, y1+h, z3);
	glVertex3d (x4, y1+h, z4);
    
    glVertex3d (x3, y1, z3);
	glVertex3d (x2, y1, z2);
	glVertex3d (x2, y1+h, z2);
	glVertex3d (x3, y1+h, z3);
    
	glEnd();
}



Polyg::Polyg()
{
	nVertex=0;
	vertex=NULL;
}

Polyg::~Polyg()
{
	Clear();
}

int Polyg::ReadFromFile (char fn[])
{
	//Given a filename, this builds an array of the centerline of the track
	if (vertex!=NULL)
	{
		Clear();
	}
    
	FILE *fp;
	char str[256];
	fp=fopen(fn, "r");//Open file

	if (fp!=NULL && fgets(str, 255, fp)!=NULL)//if the file has stuff and exists
	{
		int nRead;
        
		nVertex=atoi(str); //get the number of vertices
		//atoi: convert string to integer
		vertex=new Vec[nVertex];
        
		if (vertex!=NULL)
		{
			nRead=0;
			while (fgets(str, 255, fp)!=0 && nRead<nVertex)//While there is text in the file to be read, and more vertices to be recorded
			{
				StringParser parser;
				parser.SetStringAndParse(str);
                
				if (2<=parser.GetNumWords())//if reading more than 2 words
				{
					char word[256];
                    
					vertex[nRead].y=0.0;//Save y
					parser.GetWord (word, 255, 0);
					vertex[nRead].x=atoi(word);//Save x
					parser.GetWord (word, 255, 1);
					vertex[nRead].z=atoi(word);//Save z
                    
					nRead++;//move to next vertex
				}
			}
			fclose (fp);
			return 1;
		}
	}
	if (fp!=NULL)//while the file exists
	{
		fclose(fp);
	}
	return 0;
}

PathPlanning::PathPlanning()
{
	SetTrackProperty();	
}
void Polyg::Clear()
{
	if (vertex!=NULL)
	{
		delete [] vertex;
		vertex=NULL;
		nVertex=0;
	}
}

void PathPlanning::fillUpBArray()//Takes the values from the x,z "points" and puts them into the boundary arrays
{
	for(int i = 0; i<plg.nVertex;i++)
	{
		centerx[i] = x[i].center;
		centerz[i] = z[i].center;
		leftx[i] = x[i].leftIn;
		leftz[i] = z[i].leftIn;
		lleftx[i] = x[i].leftOut;
		lleftz[i] = z[i].leftOut;
		rightx[i] = x[i].rightIn;
		rightz[i] = z[i].rightIn;
		rrightx[i] = x[i].rightOut;
		rrightz[i] = z[i].rightOut;
	}
}

void PathPlanning::SetTrackProperty (void)
{	
	plg.ReadFromFile ("testTrack3.txt");
	//Save centerline coordinates into Pathplanning's polygon "plg"
    
	int i;
	for (i=0; i<plg.nVertex; i++)
	{
		//Move centerline coordinates into Pathplannings "points" 
		//Basically x,y,z are arrays the x coordinates of each wall. 
		// x[1] has the x coordinate of the second node of all 5 boundaries (not at this point, but later)
		x[i].center=(double)plg.vertex[i].x;
		y[i].center=(double)plg.vertex[i].y;
		z[i].center=(double)plg.vertex[i].z;
	}
    
	roadWid=30.0;
	wallWid=2.0;
	wallHei=0.50;

	double r=roadWid/2.0;
	double slopeAngle; //radius angle (with horizontle)
	
	for (i=0; i<plg.nVertex-1; i++)//Fil in the other 4 boundaries
	{
		slopeAngle=atan(abs((z[i+1].center-z[i].center)/(x[i+1].center-x[i].center))); 

		if ((z[i+1].center-z[i].center)<=0.0 && (x[i+1].center-x[i].center)>=0.0)
		{
			slopeAngle=slopeAngle;
		}
		else if ((z[i+1].center-z[i].center)<=0.0 && (x[i+1].center-x[i].center)<=0.0)
		{
			slopeAngle=YsPi-slopeAngle;
		}
		else if ((z[i+1].center-z[i].center)>=0.0 && (x[i+1].center-x[i].center)<=0.0)
		{
			slopeAngle=YsPi+slopeAngle;
		}
		else if ((z[i+1].center-z[i].center)>=0.0 && (x[i+1].center-x[i].center)>=0.0)
		{
			slopeAngle=2.0*YsPi-slopeAngle;
		}	

		x[i].leftIn=x[i].center-r*sin(slopeAngle);
		z[i].leftIn=z[i].center-r*cos(slopeAngle);
		x[i+1].leftIn=x[i+1].center-r*sin(slopeAngle);
		z[i+1].leftIn=z[i+1].center-r*cos(slopeAngle);
		x[i+1].leftOut=x[i+1].center-(r+wallWid)*sin(slopeAngle);
		z[i+1].leftOut=z[i+1].center-(r+wallWid)*cos(slopeAngle);
		x[i].leftOut=x[i].center-(r+wallWid)*sin(slopeAngle);
		z[i].leftOut=z[i].center-(r+wallWid)*cos(slopeAngle);

		x[i].rightIn=x[i].center+r*sin(slopeAngle);
		z[i].rightIn=z[i].center+r*cos(slopeAngle);
		x[i+1].rightIn=x[i+1].center+r*sin(slopeAngle);
		z[i+1].rightIn=z[i+1].center+r*cos(slopeAngle);
		x[i+1].rightOut=x[i+1].center+(r+wallWid)*sin(slopeAngle);
		z[i+1].rightOut=z[i+1].center+(r+wallWid)*cos(slopeAngle);
		x[i].rightOut=x[i].center+(r+wallWid)*sin(slopeAngle);
		z[i].rightOut=z[i].center+(r+wallWid)*cos(slopeAngle);
	}

	centerx = new int[plg.nVertex];
	centerz = new int[plg.nVertex];
	leftx = new int[plg.nVertex];
	leftz = new int[plg.nVertex];
	rightx = new int[plg.nVertex];
	rightz = new int[plg.nVertex];
	rrightx = new int[plg.nVertex];
	rrightz = new int[plg.nVertex];
	lleftx = new int[plg.nVertex];
	lleftz = new int[plg.nVertex];

	fillUpBArray();//save them in boundary arrays



}

void PathPlanning::DrawTrackCenterLine (void)
{
	int i;
	for (i=0; i<plg.nVertex-1; i++)
	{
        glBegin (GL_LINES);

		glVertex3d (x[i].center, y[i].center, -z[i].center);
		glVertex3d (x[i+1].center, y[i+1].center, -z[i+1].center);
        
		glVertex3d(x[i].leftIn, y[i].center, -z[i].leftIn);
		glVertex3d(x[i].rightIn, y[i].center, -z[i].rightIn);

        glEnd();
	}
}

void PathPlanning::DrawTrackWall (void)
{
	int i;
	
   // glColor4ub(0,0,255,70);

	for (i=0; i<plg.nVertex-1; i++)
	{
		if(i%2==0)
		{
			glColor3ub(255,0,0);
		}
		else
		{
			glColor3ub(255,255,255);
		}
		map.DrawRotateWall (x[i].leftIn, -z[i].leftIn, x[i+1].leftIn, -z[i+1].leftIn, 
			x[i+1].leftOut, -z[i+1].leftOut, x[i].leftOut, -z[i].leftOut, 0.0, wallHei);

		map.DrawRotateWall (x[i].rightIn, -z[i].rightIn, x[i+1].rightIn, -z[i+1].rightIn, 
			x[i+1].rightOut, -z[i+1].rightOut, x[i].rightOut, -z[i].rightOut, 0.0, wallHei);
	}

	
}

void PathPlanning::DrawTrackGround (void)
{
	int i;
	
	for (i=0; i<plg.nVertex-1; i++)
	{
		/*if (i%2 == 0)
		{
			glColor3ub(130,200,250);
		}
		else
		{
			glColor3ub(255,255,255);
		}*/

		glColor3ub(130,200,250);
		glBegin (GL_QUADS);

		glVertex3d(x[i].leftIn, y[i].center, -z[i].leftIn);
		glVertex3d(x[i].rightIn, y[i].center, -z[i].rightIn);
		glVertex3d(x[i+1].rightIn, y[i+1].center, -z[i+1].rightIn);
		glVertex3d(x[i+1].leftIn, y[i+1].center, -z[i+1].leftIn);

		glEnd();
	}
	
}

void PathPlanning::Draw(void)
{
	glColor3ub (255, 0, 0);
	DrawTrackCenterLine();
	DrawTrackWall();
		
	glColor3ub (255, 255, 0);
	DrawTrackGround();

}
