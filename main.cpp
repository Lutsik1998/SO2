#include "stdarg.h"
#include "stddef.h"
#include "ncurses.h"
#include <cstring>
#include "Philosopher.h"


using namespace std;

mutex mtx;

volatile bool isActive = true;

vector<Fork *> forks;



int main(int argc, char **argv)
{
    system("export TERM=xterm-256color");
    int numberOfPhilosophers = 5;
    
    for(int i = 0; i < numberOfPhilosophers; i++){
        forks.push_back(new Fork(i));
    }
    vector<thread *> threads;
    vector<Philosopher *> philosophers;

    for(int i = 0; i < numberOfPhilosophers; i++){
        mtx.lock();
        philosophers.push_back(new Philosopher(i,numberOfPhilosophers, &forks, &isActive));
        
        threads.push_back(new thread([&philosophers, i]() {
            
            philosophers.at(i)->lifePhilosopher();
            
        }));
    
        mtx.unlock();
    }
    int row, col; 
    initscr();
    noecho();
    raw();
    halfdelay(1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int hOffset = 2;
    int vOffset = 1;


    while (isActive)
    {
        getmaxyx(stdscr, row, col); 
        clear();
        attron(COLOR_PAIR(1));
       
        
        mvwaddstr(stdscr, 4, hOffset, "Filozof");
        mvwaddstr(stdscr, 5, hOffset, "Stan");
        mvwaddstr(stdscr, 6, hOffset, "Zjadl");
        mvwaddstr(stdscr, 7, hOffset, "Postep");
        mvwaddstr(stdscr, 10, hOffset, "Nr Widelca");
        mvwaddstr(stdscr, 11, hOffset, "Zajety");            
       
        
        for (int i = 0; i < numberOfPhilosophers; i++)
        {
            attron(COLOR_PAIR(1));
            philosophers.at(i)->mtx.lock();
            mvwaddstr(stdscr, 4, hOffset+12 + 12*i, to_string(philosophers.at(i)->id).c_str());
            mvwaddstr(stdscr, 5, hOffset+12 + 12*i, philosophers.at(i)->stan.c_str());
            mvwaddstr(stdscr, 6, hOffset+12 + 12*i, to_string(philosophers.at(i)->food).c_str());
            mvwaddstr(stdscr, 7, hOffset+12 + 12*i, (to_string(philosophers.at(i)->progres)+"%").c_str());
            philosophers.at(i)->mtx.unlock();
            forks.at(i)->mtx.lock();
            mvwaddstr(stdscr, 10, hOffset+12 + 12*i, to_string(forks.at(i)->nrOfFork).c_str());
            string tmp = (forks.at(i)->isBusy)? "true" : "false";
            mvwaddstr(stdscr, 11, hOffset+12 + 12*i, tmp.c_str());
            forks.at(i)->mtx.unlock();

        }
        
        refresh();
        if(getch()==27){
            isActive = false;
        }
    }
     
    



    for(int i = 0; i < numberOfPhilosophers;i++){
        threads.at(i)->join();
    }
    for(int i = 0; i < numberOfPhilosophers;i++){
        delete threads.at(i);
        delete philosophers.at(i);
        delete forks.at(i);
    }
    endwin();
    system("clear");
}

