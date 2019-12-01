//visualizer Class
/** PAA KOFI BOAFO*/

#ifndef PERCVISUALIZER_H
#define PERCVISUALIZER_H

//#include <math.h>
#include <iostream>
#include <iomanip> 
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Percolation.h"
#include "CImg.h"
#include "DisjointSets.h"


using namespace std;
using namespace cimg_library;

class PercVisualizer 
{
	public:
	
		 
		 PercVisualizer();  //default constructor
		 PercVisualizer(int,int,string); //parametrized constructor
		 // ~PercVisualizer(); //destructor
		
		 void paintCell(int,int,int,int,int,int); //paint cell with a color
		 void displayVisualization(); //show the window till its closed
		 
		 void cellcalc();
		 //int colorchoice();
		 void save();
		 
		 CImgDisplay disp;
		 int col;
		 int offsetx;
		 int offsety;
		 int cwidth;
		 int cheight;
		 int xx;
		 int yy;
		
		 int windowheight;
		 int windowwidth; 
		 int mheight;
		 int mwidth;
		 CImg <unsigned char> canvas; 
	
	//private :
	

		
		
		
};

PercVisualizer::PercVisualizer() //default constructor
{

		
		 col=0;
		 offsetx=0;
		 offsety=0;
		 cwidth=0;
		 cheight=0;
		 xx=0;
		 yy=0;
		
		 windowheight=0;
		 windowwidth=0; 
		
		 mheight=0;
		 mwidth=0;
		 
	
}



PercVisualizer::PercVisualizer(int dimensionx, int dimensiony, string title)
{
	/** create cells based off user dimension information */
	/** draw cell boundaries with CImg which will be displayed later*/
	/** "canvas" is instantiated here with the pointer being declared in public*/
	
	unsigned char gold[]={255,165,0};
	
	
	 xx=dimensionx;
	 yy=dimensiony;
     
     
	 offsetx =10;
	 offsety=10;
	
	 //calculate cell dimesions
	 cellcalc(); 
	 
	 
	 mheight =xx*cheight;
	 mwidth=xx*cwidth;
	
	 //determine window dimensions
	
	// windowheight = (2*offsety)+xx * (cheight);
	 //windowwidth = (2*offsetx)+(mwidth)+xx * (cwidth);
	 
	 windowheight = (2*offsety)+(mheight)+xx+1;
	 windowwidth = (2*offsetx)+(mwidth) + xx+1;
	 
	 CImg <unsigned char> testcan (windowwidth,windowheight,1,3,0); //instantiation of pointer
	 canvas = testcan;
	
	//setting row and column boundaries 
	//based off determined cellwidth
	 for(int i=0;i<=xx;i++)//row
	{
		canvas.draw_line (offsetx,(i*cheight)+offsety,offsetx+(cwidth*xx),(i*cheight)+offsety,gold); //vertical lines. number of lines == xx+1
	}
	
	for(int j=0;j<=xx;j++) //col
	{
		canvas.draw_line (offsetx+(j*cwidth),offsety,(j*cwidth)+offsetx,offsety+(xx*cheight),gold);
	}
	
}
	/*
    canvas(windowwidth,windowheight,1,3,0);
	CImgDisplay disp(canvas,"test");
	
	
	
	while (!disp.is_closed())
	{
		disp.wait();
		 
	 
	 
	 //draw grid
	 int count =0;
	 for(int row=1;row<=xx;row++)
	 {
		for(int col=1;col<=yy;col++)
		{
			int index =  ((row + col) + (row *(xx -1)));
			
			int cellX = (row - offsetx) / width;
			int cellY = (col - offsetx) / height; 	
			int topX = offsetx + (width * cellX) + + cellX + 1;
			int topY = offsety + (height * cellY) + cellY + 1;
			int bottomX = topX + width - 1;
			int bottomY = topY + height- 1;
			
			if(testing.pathToTop(index))
			{
				canvas.draw_line (offsetx,col,offsetx+(mwidth)+xx,row,purple);
			}
			else if(testing.isOpen(index))
			{
				canvas.draw_line (offsetx,col,offsetx+(mwidth)+xx,row,white);
			}
			else
			canvas.draw_line (offsetx,col,offsetx+(mwidth)+xx,row,black);
			
			canvas.draw_rectangle(topX, topY, bottomX, bottomY, green);
		}
	}
		
		disp.display(canvas);
           
     } 
     */  	
				
	
	//title= "test";
	
	
	/*
	 CImg <unsigned char> canvas(windowwidth,windowheight,1,3,0);
	CImgDisplay disp(canvas,"test");
	
	
	
	
	
	while (!disp.is_closed())
	{
		disp.wait();
		
		
		
		
		
	
		//paintCell();
		
		disp.display(canvas);
           
     }  
     */    
     
	
	
	
		 
	//drawGrid(int dimensionx, int dimensiony, CImg<unsigned char> &canvas);
	
	
	
//cell size calculations

void PercVisualizer::cellcalc()
{
	if(xx<=70)
	{
		cwidth=10;
		cheight=10;
	}
	 if(xx>70 and xx<=120)
	{
		cwidth=5;
		cheight=5;
	}
	if(xx>=121 and xx<=200)
	{
		cwidth=3;
		cheight=3;
	}
}





void PercVisualizer::paintCell(int tx,int ty,int bx,int by,int colour,int c)
{
	
	// int colorchoice1=0;
	 //colorchoice1 = colorchoice(int c);
	
 	
	 unsigned char colors[11][3] = {
     {0,0,0}, // black 0
     {128,128,128}, // mdgrey2 1
     {255,255,255}, // white 2
     {255,69,0}, // orangered 3
     {144,238,144}, // green 4
     {255,165,0}, // gold 5
     {165,42,42}, // rust? 6
     {128,0,128}, // purple 7
     {77,77,77}, // darkgray 8
     {139,105,20}, // brown 9 
     {40,40,40} // slategray 10 
     };
    

	
	
	 unsigned char color[3] = { 0, 0, 0 };

	if (colour == 1) //white
	{
		for(int i=0;i<3;i++)
		{
			color[i]=colors[2][i];
		}
		
	}

	else //green
	{

		for(int i=0;i<3;i++)
		{
			color[i]=colors[c][i];
		}
		
	}
	
	//coloured rectangle
	canvas.draw_rectangle(tx+1,ty+1,bx-1,by-1,color);
	 
}

void PercVisualizer::displayVisualization()
{
	 CImgDisplay disp(canvas,"test");
		
	 while (!disp.is_closed())
	{
		disp.wait();
		
	}
	
}
void PercVisualizer::save()
{
	string savefile="";
	int save =cimg::dialog("Save","Do you want to save?","Yes","No");
	cout<<"Save: "<<save<<endl<<endl;
	if (save==0)
		{
			cout<<"Enter save name: "<<endl;
			cin>>savefile;
			canvas.save(savefile.c_str());
		}
		else
		exit(0);
}
 
#endif

			
