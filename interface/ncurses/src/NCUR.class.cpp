#include "NCUR.class.hpp"

key_callback handlel;
bool shoudl_close = false;

NCUR::NCUR(int x, int y, int b) : x(x), y(y), b(b){
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    nocbreak();
    
}

NCUR::NCUR(NCUR const & obj) : x(obj.x), y(obj.y), b(obj.b){}

NCUR::~NCUR(){
    endwin();
}


void NCUR::drawBlock(int x, int y, Color c){
    move(abs(this->y - y), x);
    if(!c.r)
        printw("O");
    else if(!c.g)
        printw("*");
    else
        printw("X");
}
void NCUR::drawText(int x, int y, std::string const txt){
    move(abs(this->y - y), x);
    printw(txt.c_str());
}

void NCUR::prerender(){
    clear();
}

void NCUR::bindKeyCallback(const key_callback q){
    handlel = q;
}

void NCUR::postrender(){
    refresh();
}

bool NCUR::closing(){
    return shoudl_close;
}

void NCUR::close(){
    endwin();
    shoudl_close = true;
}

void NCUR::pollEvents(){
    int ch;
    for(;;){
        if((ch = getch()) != ERR && handlel)
            if(ch == 27)
                close();
            else
            handlel(ch, 0, 0);
        else break;
    }
}

std::string NCUR::getName(){
    return std::string("NCURibbler");
}