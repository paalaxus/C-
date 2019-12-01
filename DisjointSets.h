// DisjointSets.h
// class for disjoint sets of integers in a range
// Path compression and union by rank
// LOTS of public utilities to be able to watch things

#ifndef DISJOINTSETS_H
#define DISJOINTSETS_H
//#include "Percolation.h"
//#include "PercVisualizer.h"

// #include <iostream>
using namespace std;

class DisjointSets
   {
      public:
            DisjointSets();                              // default constructor
            DisjointSets(int);                           // start with n distinct sets
            ~DisjointSets();                             // destructor
            DisjointSets(const DisjointSets&);     // copy constructor

            DisjointSets & operator=(const DisjointSets&);   // operator=()

			void reset(int);
            int getarray(int);
            
            
            int Find(int);
            void Union(int,int);
			
            int getDistinctSetCount();  
            void set(int);                       // how many distinct sets in existance
            
            //--------------------------------------------------------------
            // Functions to make it easy to see what's going on...
            
            
            
            int ncFind(int);
           
            
            void dumpSets();
            void dumpSets(string);
            void showSet(int);
            void showSet(string,int);
            void showDistinctSets();
            void showDistinctSets(string);

            void showPath(int);
            void showAllPaths(string);
            
            void showRank(int);
            void showAllRanks(string);
            //----------------------------------------------------------


      private:
            int *a;                    // the data (ints)
            int arraysize;             // size of the array
            int *r;                    // array of ranks (intially all 0)
            int n;                     // items             (same as arraysize, for now)
            int distinctsets;          // distinct sets

   };
   

// default constructor..make an empty collection of sets
DisjointSets::DisjointSets()
   {
      n = 0;
      arraysize = 0;
      a = NULL;
      r = NULL;
      distinctsets = 0;
   } // default constructor

// make a collection of nn distinct sets
DisjointSets::DisjointSets(int nn)
   {
	   
      n = nn;
      arraysize = n;
      a = new int[arraysize];
      r = new int[arraysize];
      for (int i=0;i<n;i++)
         {
            a[i] = i;                        // each is its own leader
            r[i] = 0;                        // rank is 0
         }
      distinctsets = n;
   }  // 1-param constructor

// destructor
DisjointSets::~DisjointSets()
   {
      if (a!=NULL)
         {
            delete [] a;
            delete [] r;
         }
   }  // destructor

// copy constructor

DisjointSets::DisjointSets(const DisjointSets &other)
   {
      arraysize = other.arraysize;
      n = other.n;
      a = new int[arraysize];
      r = new int[arraysize];
      for (int i=0;i<n;i++)
         {
            a[i] = other.a[i];
            r[i] = other.r[i];
         }
      distinctsets = other.distinctsets;
   } // copy constructor

// operator=  .. so can do assignment easily
DisjointSets & DisjointSets::operator=(const DisjointSets &rhs)
   {
      if (this == &rhs)      // watch for self-asst
         return *this;

// std::cout<<"Starting to build"<<std::endl;
      if (a!=NULL)
         {
            delete [] a;
            delete [] r;
         }
      arraysize = rhs.arraysize;
      n = rhs.n;
      a = new int[arraysize];
      r = new int[arraysize];
// std::cout<<"Built new int[] of size "<<arraysize<<std::endl;
      for (int i=0;i<n;i++)
         {
            a[i] = rhs.a[i];
            r[i] = rhs.r[i];
            // std::cout<<"Copied "<<a[i]<<std::endl;
         }
      distinctsets = rhs.distinctsets;

      return *this;
   }  // operator=()
   
   
// how many distinct sets are there?
int DisjointSets::getDistinctSetCount()
   {
      return distinctsets;
   }  //getDistinctSetCount()


void DisjointSets::set(int nn) //created for percolation
{
	 n = nn;
      arraysize = n;
      a = new int[arraysize];
      r = new int[arraysize];
      for (int i=0;i<n;i++)
         {
            a[i] = i;                        // each is its own leader
            r[i] = 0;                        // rank is 0
         }
      distinctsets = n;
}
//======================================================================
// You have to implement Find() and Union()
// Find() does path compression 
// Union() does union-by-rank


// Find the set leader for x, compress paths
int DisjointSets::Find(int x)
   {
	   if(x==a[x])
	   return x;
	   else
	   return Find(a[x]);
	   
      
   }



// Merge the sets containing x and y, if they're different
// Set with smaller rank is attached to the set with larger rank
//   Adjust rank of the result if they're of the same rank.
void DisjointSets::Union(int x, int y)
   {
      int b=0;
	   int c=0;
	   b= Find(x);
	   c= Find (y);
	   
	   if(b!=c)
	   {
		if(r[b]>r[c])
			{
				a[c]=b;
			}
			else
			{
			  a[b]=c;
			}
		}
		
		if(r[b]==r[c])
		r[c]++;
		
   }




//=======================================================================
// The following stuff is present only for watching what's going on!

// non-compressing Find() to support the following w/o altering the parent structure
int DisjointSets::ncFind(int x)
   {
      if (x == a[x])
         return x;
      return ncFind(a[x]);
   }

// show the set leader for each item, 
void DisjointSets::dumpSets()
   {
      int j=0;
      for (int i=0;i<n;i++)
         {
            std::cout<<i<<": ";
            j=i;
            while (a[j]!=j)
               j = a[j];
            std::cout<<j<<std::endl;
         }
   }

// dumpSets() with an accompanying message
void DisjointSets::dumpSets(string msg)
   {
      std::cout<<msg<<std::endl;
      dumpSets();
   }

// show the set containing X
void DisjointSets::showSet(int x)
   {
      int leader;
      leader = ncFind(x);
      std::cout<<"Set for "<<x<<" has leader: "<<leader<<" - contains: ";
      for (int i=0;i<n;i++)
         {
            if (ncFind(i)==leader)
               std::cout<<i<<" ";
         }
      std::cout<<std::endl;
   }

// showSet() with a message
void DisjointSets::showSet(string msg,int x)
   {
      std::cout<<msg<<std::endl;
      showSet(x);
   }

// show the distinct sets in the collection
void DisjointSets::showDistinctSets()
   {
      bool *got;
      got = new bool[n];
      for (int i=0;i<n;i++)
         got[i] = false;

      int leader = -1;
      // std::cout<<"{ ";
      for (int i=0;i<n;i++)
         {
            leader = ncFind(i);

            if (!got[leader])
               {
                  std::cout<<"{ ";
                  for (int j=0;j<n;j++)
                     {
                        if (ncFind(j)==leader)
                           {
                              got[j] = true;
                              std::cout<<j<<" ";
                           }
                     }
                  std::cout<<"}"<<std::endl;
               }
         }
   }

// showDistinctSeets() with a message
void DisjointSets::showDistinctSets(string msg)
   {
      std::cout<<msg<<std::endl;
      showDistinctSets();
   }


// show the path from i to the set leader
void DisjointSets::showPath(int i)
   {
      std::cout<<i<<": ";
      if (a[i]==i)
         std::cout<<"root"<<std::endl;
      else
         {
            while (i!=a[i])
               {
                  std::cout<<a[i]<<" ";
                  i = a[i];
               }
            std::cout<<std::endl;
         }
   } // showPath()

// show all the paths with a message
void DisjointSets::showAllPaths(string msg)
   {
      if (msg.length()>0)
         std::cout<<msg<<std::endl;
      for (int i=0;i<n;i++)
         showPath(i);
   }
   
   
// show rank of individual item
void DisjointSets::showRank(int i)
   {
      std::cout<<"Rank of "<<i<<": "<<r[i]<<std::endl;
   }
   
// show ranks of all items with message
void DisjointSets::showAllRanks(std::string msg)
   {
      if (msg.length() > 0)
         std::cout<<msg<<std::endl;
      for (int i=0;i<n;i++)
         showRank(i);
   }

//reset the ranks and leaders
void DisjointSets::reset(int k)
{
for (int i = 0; i < k; i++)
	{	 
		 a[i] = i;          // each is its own leader
         r[i] = 0; 			// rank is 0
    }                       
	
}
int DisjointSets::getarray(int i)
{
	
	return a[i];
}



#endif
