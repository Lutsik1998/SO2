#include <iostream>  
#include <mutex>  
#include <thread>
#include <vector>
#include "Fork.h"
using namespace std;  


class Philosopher
{  
public:  
int food;
int id;
int numberOfPhilosophers;
string stan;
int progres;
void lifePhilosopher();  
void philosopherThink();  
void takeForks();  
void putForks();  
void philosopherEat(); 
void inProcess(int); 

mutex mtx;

Fork *leftFork;
Fork *rightFork; 
vector<Fork*> *forks;
volatile bool *isActive;

Philosopher(int,int,vector<Fork*> *,volatile bool*);


};