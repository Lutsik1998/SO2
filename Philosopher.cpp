#include "Philosopher.h"





 

Philosopher::Philosopher(int n,int sum, vector<Fork*> *f, volatile bool *isA)
{
    this->id = n;
    this->leftFork = NULL;
    this->rightFork = NULL;
    this->numberOfPhilosophers = sum;
    this->forks = f;
    this->food = 0;
    this->isActive = isA;
}
  
void Philosopher::takeForks()  
{  
    
    if(id < numberOfPhilosophers - 1){

        this->stan = "Czeka"; 
        while (forks->at(id)->isBusy==true){
        } 
        forks->at(id)->mtx.lock();
        leftFork = forks->at(id);
        leftFork->isBusy = true;
        forks->at(id)->mtx.unlock();  
        
        this->stan = "Czeka"; 
        while(forks->at(id+1)->isBusy ==true){
            
        }
        forks->at(id+1)->mtx.lock();
        rightFork = forks->at(id+1);
        rightFork->isBusy = true;
        forks->at(id+1)->mtx.unlock();
    }else{
        this->stan = "Czeka"; 
        
        while(forks->at(0)->isBusy == true){
        
        }
        forks->at(0)->mtx.lock();
        rightFork = forks->at(0);
        forks->at(0)->isBusy=true; 
        forks->at(0)->mtx.unlock();
        this->stan = "Czeka"; 
        
        while(forks->at(id)->isBusy == true){ 
        }
        forks->at(id)->mtx.lock();
        leftFork = forks->at(id);
        forks->at(id)->isBusy=true;
        forks->at(id)->mtx.unlock();
    }
}  
 
void Philosopher::putForks()  
{  
   if(id < numberOfPhilosophers - 1){
        rightFork->mtx.lock();
        rightFork->isBusy=false;
        rightFork->mtx.unlock();
        rightFork = NULL;
        leftFork->mtx.lock();
        leftFork->isBusy=false;
        leftFork->mtx.unlock();
        leftFork = NULL;
    }else{
        leftFork->mtx.lock();
        leftFork->isBusy=false;
        leftFork->mtx.unlock();
        leftFork = NULL;
        rightFork->mtx.lock();
        rightFork->isBusy=false;
        rightFork->mtx.unlock();
        rightFork = NULL;
    }
}  
 
void Philosopher::philosopherEat()  
{  
    this->mtx.lock();
    this->food = food+1;  
    this->mtx.unlock();
}  
 
void Philosopher::philosopherThink()  
{  

}  

void Philosopher::lifePhilosopher()  
{      
    do{
    this->mtx.lock();
    this->stan = "Rozmysla";
    this->mtx.unlock(); 
    if(*isActive==false){
        break;
    }
    inProcess(10);
    philosopherThink();
    this->mtx.lock();
    this->stan = "Bierze wid."; 
    this->mtx.unlock();
    if(*isActive==false){
        break;
    }
    inProcess(20);  
    takeForks();  
    this->mtx.lock();
    this->stan = "Je";
    this->mtx.unlock(); 
    if(*isActive==false){
        putForks();  
        break;
    }
    inProcess(20);
    philosopherEat();
    this->mtx.lock();
    this->stan = "Zwraca wid."; 
    this->mtx.unlock();
    if(*isActive==false){
        putForks();  
        break;
    }
    inProcess(15);  
    putForks();  
    }while(*isActive);
    
}
void Philosopher::inProcess(int time){
    for(int i = 0; i < time; i++){
        this->mtx.lock();
        progres = float(i*100)/time;
        this->mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(130));
    }
    this->mtx.lock();
    progres = 0;
    this->mtx.unlock();
} 