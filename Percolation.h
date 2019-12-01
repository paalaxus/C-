//percolation class
/** PAA KOFI BOAFO*/

#ifndef PERCOLATION_H
#define PERCOLATION_H

//#include <math.h>
#include <iostream>
#include <iomanip> 
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "DisjointSets.h"
#include "CImg.h"
#include "PercVisualizer.h"


using namespace std;
using namespace cimg_library;

class Percolation
{
	public:
		Percolation();  //default constructor
		Percolation(int);
		~Percolation(); //destructor
		
		
		void Open(int,int); // open cells if they arent open already
		bool isOpen(int,int);
		bool percolates();
		bool pathToTop(int,int);
		
		//stats
		//double probability(); //*p
		//double mean(); 
       // double standard_deviation();
       // double confidence_interval_low();
       // double confidence_interval_high();
		
		//display current state of percolation system
		/**black cells for blocked and white for unblocked*/
		void showPercolationVisualization(string);
		//display final state of the percolation system
		/** color all open cells that percolate with a special color*/
		void showFinalVisualization(string,int);
		CImg <unsigned char> canv2; //help show progress
		
		//double total;
		//double mean_var;
		//double standard_dev;
		//double CIL; //confidence interval
		//double CIH;  // confidence interval
		//void Show();
		int opencellcount();
		
		
		void reset();
		
		int dimension;
		bool** grid;
		int up;
		int down;
		int left;
		int right;
			
		private:
		
			
			//declarations
			int gridsize;
			
			DisjointSets setsobject;
			
			int row;
			int col;
			
			int Opencount;
			int totalcount;
			string title;
			int opencounter;
			int topc;	
			int topr;
			int botc;
			int botr;
			
			int top1;
			int top2;
			int top3;
			int top4;
			
			int bot1;
			int bot2;
			int bot3;
			int bot4;
			
			int colorc;
			int root;
			int positionindex;
			
			int x;
			int y;
			
			
	};
	


Percolation::Percolation()
{
  
     
	 gridsize = 0;
	 dimension = 0;
	 up = 0;
	 down = 0;
	 left = 0;
	 right = 0;
	
   //  cells = nullptr;
     //trials = nullptr;
     grid =nullptr;
	 row = 0;
	 col = 0;	 
//	 numberOfTrials=0;
	 Opencount=0;
	// mean_var=0;
     //standard_dev=0;
    // CIL=0;
    // CIH=0;
     //total=trials[0];
     opencounter = 0;
	 
	//trialcount=0;
	
	
}	//default constructor


Percolation::Percolation(int w) //creating grid and initialize as false
{
	
	
	string title="";
    totalcount=0;
	Opencount=0;
	row=w;
	col=w;
	
	dimension=w;
	gridsize= dimension*dimension;
	
	//PercVisualizer* pv;
	//pv = new PercVisualizer(dimension,dimension,title); //object instantiation
		
	setsobject.set(gridsize); /** taking array from disjoint sets class*/ //you can only call the constructor when youre making something new
	
	//numberOfTrials = y;
	//mean_var=0;
    //standard_dev=0;
    //CIL=0; 
    //CIH=0;
    
	//trials= new double[numberOfTrials];
	//trials[0]=probability();
    
    opencounter=0;
   // trialcount=0;
	
		
	
	//creating new nxn grid
	
			grid = new bool *[row];

		for (int i = 0; i < row; i++)
		{
			grid[i] = new bool[col];

			for (int j = 0; j <col; j++)
			{
				grid[i][j] = false;
			}
		}	
		
		
		
		
		//int index=0;
		//if(percolates())
		//{
		//opencounter=opencount;
			//while (!percolates())
		//{	
			
			 
			 //PLS LOOK HERE
			 //PLS LOOK HERE
			// pv->paintCell();
	 
		//} 
			
			
			//trials[pop]=probability();
			//total+= trials[pop];
			
		
	}
	
	//mean(); 
    //standard_deviation();
    //confidence_interval_low();
    //confidence_interval_high();
	//Show();
	
	


Percolation::~Percolation()
{
  
  //delete [] trials; 
  
  for(int i=0; i<row;i++)
	{
	  delete grid;           
	}
		delete [] grid;   
}//destructor 

 
void Percolation::Open(int x,int y)
{
	
	/**  unblock a cell if it's not already unblocked. */


	int index =  (x * row) + y;
	
	if(grid[x][y]==false)
	{	
		grid[x][y]= true; //open cells
		Opencount++; 	//increase counter
	
	/** check neighbors to see if they are open. x represents the row and y represents the column */
	
		//check cell above the current
		if (isOpen((x - 1), y) and (x - 1) >= 0)
		{
			setsobject.Union(index, (index - row));
		}

		
		//check cell to the right of the current
		if (isOpen(x, (y + 1)) and (y + 1) <= col)
		{
			setsobject.Union(index, (index + 1));
		}

		//check cell below the current
		if (isOpen(x + 1, y) and (x + 1) <= row)
		{
			setsobject.Union(index, (index + row));
		}

		
		//check cell to the left of the current
		if (isOpen(x, (y - 1)) and  (y - 1) >= 0)
		{
			setsobject.Union(index, (index - 1));
		} 
	
	}
	
        return;    
        
		 
}

//value of Opencount that would be used in main file
int Percolation::opencellcount() 
{
	return Opencount;
}

bool Percolation::isOpen(int x,int y)
{
	/** is the cell at this position unblocked?*/
	int roww=x;
	int coll=y;

	//boundary check
	if (x + 1 <= row and y + 1 <= col and x >= 0 and y >= 0 and grid[roww][coll] ==true)
	{
		return true;
	}
	else 
	return false;

}


bool Percolation::pathToTop(int x,int y) 
{	
/**is there a path from this cell to a cell on the top row? */

int index =  (x * row) + y;
for(int j=0;j<col;j++)
{
	if(setsobject.Find(index)==setsobject.Find(j))
	 return true;
}
	
	 return false;
}

bool Percolation::percolates()
{
	 /** does this system percolate. That is, is there a path from an open cell on the bottom row to an open cell on the top row? */
	 
	for(int i=0;i<col;i++) //bottom row
	{
		if(pathToTop(row-1,i))
		return true;
	}
	return false;

}

void Percolation::reset()
{
	//make all cells false again
	//restart counter
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			grid[i][j] = false;

	setsobject.reset(gridsize);

	Opencount = 0;
}

void Percolation::showPercolationVisualization(string finalshow)
{
	 //creating a pointer to an object type
	 PercVisualizer* pv;
	 pv = new PercVisualizer(dimension,dimension,"Here is the final visual"); //object instantiation
	 
	 CImgDisplay display(canv2,"Ok");
	
	 topc=0;	
	 topr=0;
	 botc=0;
	 botr=0;
	 colorc=0;
	 
	 
	 //int colorselection=0;
	 //colorselection=pv-> colorchoice();
	 
	//checking random open or closed cells
	//if they are open, then we paint
	
	
	//loop through the grid to find open cells
	for(int i=0;i<dimension;i++)
		{
			for(int j=0;j<dimension;j++)
			{
				//cout<<i<<" "<<j<<endl;
				
				if(isOpen(i,j))
				{
					/** if cells are open, get dimensions of each particular open cell
					 * and paint it*/
				
					
					//get cell values
					
					topc = (pv->cwidth * j) + pv->offsetx;
					botc = (pv->cwidth * j) + pv->offsetx + pv->cwidth;
					topr = (pv->cheight * i)+ pv->offsety;
					botr = (pv->cheight * i)+ pv->offsety + pv->cheight;
					
					colorc=1; /**paint it white if open */
					
					//display.display(pv->canvas);
					//2 is the white color
					pv->paintCell(topc,topr,botc,botr,colorc,2);
					
					
				}
				
				//this is here to show progression
				display.display(pv->canvas);
				
			}
		}
			
			
				/*if (pathToTop(row - 1, j))
				{
					//working with 1D index to find its parent
					in = ((row - 1) * row) + j;
					root = setsobject.Find(in);
					
				}
				
				
			}
		}
		*/ 
			
			/*
			//find the root for each cell
			//find roots of all cells that percolate
			int item = 0;
		    //bool* cells = new bool[gridsize];
		 
			for (int i = 0; i <gridsize; i++)
			{
					setsobject.Find(i);
			}
				
				for (int i = 0; i <gridsize; i++)
				{
					item = setsobject.set(i);
					
				
						if (item == root)
						{
							x = i % col;
							y = i / col;
							top1 = pv->topX(x);
							bot1 = pv->bottomX(x);
							top2 = pv->topY(y);
							bot2 = pv->bottomY(y);
							colorc = 2;

							pv->paintCell(top1, top2, bot1, bot2, colorc);
						}
				}
				*/ 	
			
			 	
	pv->displayVisualization();
	
	
	//save image
	
}


void Percolation::showFinalVisualization(string currentshow,int colll)
{
	
	 //creating a pointer to an object type
	 PercVisualizer* pv;
	 pv = new PercVisualizer(dimension,dimension,"Here is the final visual"); //object instantiation
	
	
	
	 CImgDisplay display(canv2,"Ok");
	
	 top1=0;
	 top2=0;
	 top3=0;
	 top4=0;
	
	 bot1=0;
	 bot2=0;
	 bot3=0;
	 bot4=0;
	
	
	 colorc=0;
	 root =0;
	 positionindex=0;
	 x=0;
	 y=0;
	 
	 //int colorselection=0;
	// colorselection=pv-> colorchoice();
	 
	//loop through the grid to find open cells
	for(int r=0;r<dimension;r++)
		{
			for(int c=0;c<dimension;c++)
			{
				if(isOpen(r,c))
				{
					/** if cells are open, get dimensions of each particular open cell
					 * and paint it*/
				
					//get cell values
					topc = (pv->cwidth * c) + pv->offsetx;
					botc = (pv->cwidth * c) + pv->offsetx + pv->cwidth;
					topr = (pv->cheight * r)+ pv->offsety;
					botr = (pv->cheight * r)+ pv->offsety + pv->cheight;
					
					colorc=1; /**paint it white if open */
					
					pv->paintCell(topc,topr,botc,botr,colorc,colll);
				}
			}
		}
		int tried = 0;
		//loop through bottom row and find if cells have a path from the bottom row
		for(int r=0;r<dimension;r++)
		{
				if (pathToTop(dimension - 1, r))
				{
					
					//if they do, find the parent and store
					positionindex = ((dimension - 1) * dimension) + r;
					root = setsobject.Find(positionindex);
				}
			}
					//then loop through entire gridsize to find all parents
						
							
						for(int c=0;c<gridsize;c++)
						{
							tried = setsobject.Find(c);
							//if  parents are shared, paint another color
							if(tried ==root)
							 {
									
									//to find cell coordinates from gridsize
									//the remainder is the x and the quotient is the y
									
									//number of cells that percolate are different from cells that are open
									
									top3 = (pv->cwidth * (c%dimension)) + pv->offsetx; //col
									bot3 = (pv->cwidth * (c%dimension)) + pv->offsetx + pv->cwidth;//col
									top4 = (pv->cheight * (c/dimension))+ pv->offsety; //row
									bot4 = (pv->cheight * (c/dimension))+ pv->offsety + pv->cheight; //row
										
									colorc=2;
									pv->paintCell(top3,top4,bot3,bot4,colorc,colll);
							  }
							//this is here to show progression
							display.display(pv->canvas);	
						}
			
		pv->displayVisualization();
}

#endif
