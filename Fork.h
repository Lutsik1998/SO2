#include <mutex>



using namespace std;

class Fork
{  
public:  

int nrOfFork;
int leftFork, rightFork;
volatile bool isBusy;
 


mutex mtx;

Fork();
Fork(int);


};