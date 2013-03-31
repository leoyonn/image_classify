#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

// FUNCTION PROTOTYPES

// DEFINES
#define         SUCCESS         1
#define         FAILURE         0
#define         TRUE            1
#define         FALSE           0
#define         MAXVECTDIM      600
//#define         MAXPATTERN      400000
#define         MAXCLUSTER      1000
//#define			MAXMEMBER		40000
// ***** Defined structures & classes *****
struct aCluster {
	double    *  Center;
	int		  *	 Member;  //Index of Vectors belonging to this cluster
	int          NumMembers;
};

struct aVector {
	double       Center[MAXVECTDIM];
	int          Size;
};



class System {
private:
   double    ** Pattern;
   aCluster     Cluster[MAXCLUSTER];
   int          NumPatterns;          // Number of patterns
   int          SizeVector;           // Number of dimensions in vector
   int          NumClusters;          // Number of clusters
   void         DistributeSamples();  // Step 2 of K-means algorithm
   int          CalcNewClustCenters();// Step 3 of K-means algorithm
   double       EucNorm(int, int);   // Calc Euclidean norm vector
   int          FindClosestCluster(int); //ret indx of clust closest to pattern
   //whose index is arg
   double System::fEucNorm(double * Center, double * Features);
public:
	system();
	int LoadPatterns(char *fname);      // Get pattern data to be clustered
	void InitClusters();                // Step 1 of K-means algorithm
	void RunKMeans();                   // Overall control K-means process
	void ShowClusters();                // Show results on screen
	void SaveClusters(char *fname);     // Save results to file
	void ShowCenters();
	void Load(double ** sample, int total_num, int dimension, int Num_class);
	int Classify(double * Features, int dimension);
	void destroy(void);
	
};