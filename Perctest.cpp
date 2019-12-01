/** PAA KOFI BOAFO*/

#include <math.h>
#include <iostream>
#include <iomanip> 
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Percolation.h"
#include "DisjointSets.h"
#include "PercVisualizer.h"
#include "CImg.h"


using namespace std;
using namespace cimg_library;

//functions for mean and standard deviation
double mean(int tri, double *trials)
{
	double mean_var=0;
	double total=0;
	for (int i=0;i<tri;i++)
	{
		
		total+=trials[i];
	}
	mean_var= total/tri;
    return mean_var;  
}

double standard_deviation(int tri, double *trials,double mean_var)
{
  double z=0;
  double x=0;
  double standard_dev=0;
  for (int i=0; i<tri; i++)
  {
	  z=trials[i]-mean_var;
      x+=pow(z,2);
  }
    standard_dev= x/(tri-1);
    return standard_dev;
 }

int colorchoice()
{
			int choice;
			cout<<"What color should the grid be?"<<endl;
			cout<<"0 -> Black"<<endl;
			cout<<"1 -> MdGrey2"<<endl;
			cout<<"2 -> White"<<endl;
			cout<<"3 -> OrangeRed"<<endl;
			cout<<"4 -> Green"<<endl;
			cout<<"5 -> Gold"<<endl;
			cout<<"6 -> Rust"<<endl;
			cout<<"7 -> Purple"<<endl;
			cout<<"8 -> Darkgrey"<<endl;
			cout<<"9 -> Brown"<<endl;
			cout<<"10 -> Slategrey"<<endl;
			cout<<"Enter number: ";
			cin>>choice;
			
			return choice;
			
}
int main()
 {
    int dimensionx=0;
    
    int tri=0;
    string response1="";
    string response2="";
    int trialcount=0;
    double prob=0;
    int opencounter=0;
	double CIL=0;
	double CIH=0;
	
    cout<<"Grid's single dimension: "<<endl;
    cin>>dimensionx;
 
    cout<<"Number of trials"<<endl;
    cin>>tri;
    
    srand(time(NULL)); //seed
    Percolation visual(dimensionx);
    PercVisualizer saveimage;
    
    int choice=colorchoice();
    cout<<"Show final percolation grids? Enter y/n"<<endl;
    cout<<"Close the window if you dont want to see the cell by cell process"<<endl;
    cin>>response1;
    
    
    cout<<endl;
    
    if(response1=="n")
    {
		cout<<"Show Open cells instead?"<<endl;
		cin>>response2;
	}
	
	int p=0;
	int q=0;
		
	double *trials = new double[tri];
		
	while(trialcount<tri)
	{
		p=rand() % dimensionx; //random row.. 
			
		q=rand() % dimensionx; //random col..
			
		visual.Open(p,q);
		
		if(visual.percolates()==true)
		{
				//get the count of opencells 
				opencounter=visual.opencellcount();
				prob = (double)opencounter/(double)(dimensionx *dimensionx);
				trials[trialcount]=prob;
				
				cout << "Trial: " << trialcount << " ";
				cout << "N: " << dimensionx << " ";
				cout << "open count: " << opencounter<< " " << "ratio: ";
				cout << trials[trialcount] << endl;
				cout << endl;
				
				if(response1=="y")
				{ 	
					
					visual.showFinalVisualization("final",choice);
					//exit(0);
				}
				else
				{

					if(response2=="y")
					visual.showPercolationVisualization("current");
					
				
				}
				
				trialcount++; //go to next one
				
				if(trialcount==tri)
				break;
				
				else 
					visual.reset();
					//opencounter=0;
			}
					
		}
		
		double mean1  = mean(tri,trials);
		double stand1 = standard_deviation(tri,trials,mean1);
    
    
		CIL= ((mean1)-((1.96*stand1)/sqrt(tri)));
		CIH= ((mean1)+((1.96*stand1)/sqrt(tri)));
		
   
	    cout << "Here is the confidence interval: " << '(' << CIL << ", " << CIH << ')' << endl;
	    cout<<endl;
		
		
		saveimage.save();//save last image
		
		delete [] trials;
		
 
}

