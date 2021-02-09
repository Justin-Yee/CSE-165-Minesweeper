#include <Cell.h>

Cell::Cell(){//default constructer
    bomb = false;
    count = 0;
    hidden = true;
    flagged = false;
}
/*-------------Assign Values--------------*/
void Cell::addBomb(){
    bomb = true;
}

void Cell::addCount(){
    count++;
}

bool Cell::checkBomb(){
    return bomb;
}

int Cell::checkCount(){
    return count;
}

/*----------Active Game-------------*/
void Cell::flagToggle(){
 if(flagged == false && hidden == true)
    flagged = true;//Is flagged
else
    flagged = false;//Is free to click
}

void Cell::hideToggle(){
    if(flagged != true)//Unable to change if flagged
        hidden = false;
}

ucm::json Cell::show(){
    ucm::json result;
    if(hidden == true && flagged == false)//unclicked
        result["type"] = "hidden";
    else  if(flagged == true && hidden == true) //flagged,must be hidden to be flagged
        result["type"] = "flag";
    else if(bomb == true && hidden == false)//shows bomb
        result["type"] = "bomb"; 
    else{//is shown
        result["type"] = "shown";
        result["count"] = " ";
        if(count > 0)
        result["count"] = std::to_string(count);
    }
    return result;
}

void Cell::reset(){
    bomb = false;
    count = 0;
    hidden = true;
    flagged = false;
}