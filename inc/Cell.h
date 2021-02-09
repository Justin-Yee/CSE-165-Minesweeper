#ifndef CELL
#define CELL

#include<server.h>

class Cell{

 public:
    
    bool bomb; 
    int count; 
    bool hidden;
    bool flagged;

    Cell(); //constuctor

    void addBomb();
    void addCount();
    bool checkBomb();
    int checkCount();

    void flagToggle();   
    void hideToggle(); 
    ucm::json show();

    void reset();

};

#endif