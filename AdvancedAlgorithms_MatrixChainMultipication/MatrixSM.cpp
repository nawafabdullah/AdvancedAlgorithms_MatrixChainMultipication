// Nawaf Alharbi
// CSCI 422
// Lab 1

#include <iostream>

bool VALIDATOR (int x, char* y[]);
int CATALAN(int n);
bool DISPLAY_DEMINSIONS (int x, char* y[]); 
int SIMPLE_SCALAR_MULTIPICATION (int x, char* y[]);
void INITIAL_SCALAR_CALCULATION (int x, char* y[]);
int MATRIX_CHAIN_MULTIPCATION (int x, char* y[]);
std::string PRENTHESIS (int x, int y);

using namespace std;
int operations [1000][1000];



int main (int argc, char* argv[])
{
  // error checking test
  // if passed, then we know that appropriate/suffecient arguments were injected 
  if (!(VALIDATOR (argc, argv)))
  {
    cout <<" exiting the program "<<endl <<endl;
    return 0;
  }
  //checks if more than one matrix can be constructed
  //displays deminsions for matrices
  if (!(DISPLAY_DEMINSIONS(argc, argv)))
  {
    cout <<" exiting the program "<<endl <<endl;
    return 0;
  }
  //simple scalar calculation based on matrices constructed  
  INITIAL_SCALAR_CALCULATION (argc, argv);

  //  int n = entered_argc - 1;

  cout <<" minimum cost multipication  = " << MATRIX_CHAIN_MULTIPCATION (argc, argv) <<endl <<endl;


  
  cout <<" optimal prenthesis are " << PRENTHESIS (0, argc) <<endl \
 <<endl;
  
}

//function to validate if arguments satisfy conditions 
bool VALIDATOR (int x, char* y[])
{
  //if no arguments are passed after program call, EXIT
  if (x <= 1)
  {
    cout <<"\n no argument was passed " <<endl <<endl;
    return false;
  }
  
  int entered_argc = atol(y[1]);
  if (entered_argc != (x-2))
  {
    cout <<"\n number of arguments expected does NOT equal number of argument passed! "<<endl <<endl;
    return false;
  }

  int n = entered_argc - 1;

  cout << "\n there are " << CATALAN(n) << " possible multipications " <<endl <<endl;
  return true;

}

/* function -logic- inspired by explainaton of Catalan numbers  in geeksgorgeeks.com 
   recursive function to calculate Catalan number to determine possible multipications based on args */
int CATALAN(int n) 
{ 
    // Base case 
    if (n <= 1) return 1; 
  
    unsigned long int cat_poss = 0; 
    for (int i=0; i<n; i++) 
        cat_poss += CATALAN(i)*CATALAN(n-i-1); 
  
    return cat_poss; 
} 


// function to check and  display deminsions of matrices as per args 
bool DISPLAY_DEMINSIONS (int x, char* y[])
{

  int number_of_metrices = x-3; // or y[2] since it passed all previous tests then we can be assured that argv[2] contains the rightn

  //if no or 1 possible matrix only can be constructed, we can not do anything. So exit
  if (x <= 3)
  { 
    cout << " there are " << number_of_metrices << " possible matrices " <<endl <<endl;
    return false;
  }

  int j = 1; //for printing to STDOUT
  cout << " there are " << number_of_metrices << " possible matrices " <<endl <<endl
       << " deminsions of these matrices are : " <<endl <<endl;

  //loop through displaing demensions 
  for (int i = 0; i <  number_of_metrices; i++) 
  {
    cout << " matrix " << j << " has deminssions " << y[i+2] << " X " << y[i+3] <<endl <<endl;
    j++;
  }
  return true;
}

//function to Display simple scalar multipication preformed on demensions passed at the start 
void INITIAL_SCALAR_CALCULATION (int x, char* y[])
{
  cout << " preforming simple Scalar Multipication " <<endl <<endl
       << " NOTE: this answer could be not optimal " <<endl <<endl
       << " non-optimal result is: " << SIMPLE_SCALAR_MULTIPICATION (x,y)<<endl <<endl;

}

int SIMPLE_SCALAR_MULTIPICATION (int x, char* y[])
{
  int result = 1; //since multiplying by 1 does nothing 
  int number_of_metrices = x - 3; // numbers of matrices that could be constructed  

  //loop through preform multipications
  for (int i = 0; i < number_of_metrices; i++)
  {
    result *=  atol(y[i+2]) * atol(y[i+3]);
    
    if (i + 1 < number_of_metrices)
   {  
     result = result / atol(y[i+3]);
   }
  }
  return result; 
}

int MATRIX_CHAIN_MULTIPCATION (int x, char* y[])
{
 
  int diagonal_diffrence; // to keep track or diagonals
  //  int result; // to keep track of multipications results
  int min; //to keep track of minimum result; initilaized to max int
  int n = x - 2; // setting n as per argc
  int number_of_metrices = x - 3; // numbers of matrices that could be constructed
  // int limiter = x -4;
  int demensions [n]; // to keep track of demensions
  //initialaizing matrices with 0s
  int matrix [number_of_metrices][number_of_metrices] ;
  //  int operations [1000][1000];

  cout << "NUMBER IOF MATRICES = " <<  number_of_metrices <<endl;

  cout << " filling array with demensions " <<endl;

  for (int i = 0; i <  number_of_metrices; i++)
  {
    demensions[i] = atol(y[i+2]); 
    cout <<" in the deminsions array, position: "<< i << " in array has: " <<  demensions[i] <<endl <<endl;   
    matrix [i][i] = 0; // set diagonal [0][0],[1][1], ....  to zero so we use the space on the right of it only 
  }

  cout << " ========= MATRIX MULTIPCATION CHAIN OPERATION STARTS NOW ========= " <<endl <<endl;
  cout << " building tables... " <<endl <<endl;


 for (int z = 1; z <  number_of_metrices; z++)
  {
    for (int r = 0; r <  number_of_metrices- z; r++)
    {
      diagonal_diffrence  = r + z;
      matrix[r][diagonal_diffrence] = 1000000000;
      for (int f = r; f <  diagonal_diffrence; f++)
      {
        int result = matrix[r][f] + matrix[f + 1][ diagonal_diffrence] + demensions[r] * demensions[f + 1] * demensio\
ns[ diagonal_diffrence + 1];
        if (result < matrix[r][diagonal_diffrence])
        {
          matrix[r][diagonal_diffrence] = result;
          operations[r][diagonal_diffrence] = f;
        }
      }

    }
  }  
  return matrix[0][ number_of_metrices - 1];
  // return min;
}

// got some help from ALI in this function 
std::string PRENTHESIS(int x, int y)
{
  // return the multiplication sequence for Ai..j.
  std::string left;
  std::string right;

  // k is the optimal splitting
  int k = operations[x][y];
  int y = atol(y [2]) -1;
  
  // compute the sequence on the left
  if (k == x)
  {
    // single element
    left = "x";
  }
  else
  {
    // recursive call to compute for Ai..k.
    left = PRENTHESIS(x, k);
  }

  // compute the sequence on the right
  if (k + 1 == y)
  {
    // single element
    right = "x";
  }
  else
  {
    // recursive call to compute for Ak+1..j.
    right = PRENTHESIS(k + 1, y);
  }

  // combine left and right sequence
  return "(" + left + right + ")";
}
