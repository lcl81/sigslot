#include <stdio.h>
//#include <conio.h>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "sigslot.h"
using namespace sigslot;

#define pause_wait()    {std::cout << "\nPlease press any key to continue.\n"; getchar();}

// class
enum    ObjState{Normal = 0, Hidden = 1};
class ObjectBase : public has_slots<> 
{
public:
    ObjectBase(){ px = 0; py = 0; state = Normal; }
    ObjectBase(const int &x, const int &y):px(x), py(y){ state = Normal; }
    ~ObjectBase(){};
 
    void    onMoveBy(const int &x, const int &y){px += x; py += y;}
    void    onResize(const int &x, const int &y){px = x; py = y;}
    void    onSetState(ObjState s){this->state = s;}
    void    onPrintState()
    {
        if(state == Normal)
            std::cout << "Normal" << std::endl;
        else if(state == Hidden)
            std::cout << "Hidden" << std::endl;
        else
            std::cout << "Error: error state value" << std::endl;
    }
 
    const int&  getX(){return px;}      
    const int&  getY(){return py;}
    const char* getState()
    {
        if(state == Normal)
            return "Normal";
        else if(state == Hidden)
            return "Hidden";
        else
            return nullptr;
    }
 
private:
    ObjState    state;
    int     px;
    int     py;
};
 
class Control
{
public:
    signal2<const int &, const int &> moveBy;
    signal2<const int &, const int &> resize;
    signal1<ObjState> setState;
    signal0<>       printState;
};

int main(int argc, char* argv[])
{
    ObjectBase obj(10,10);
    Control ctrl;
 
#if(1)
    ctrl.moveBy.connect(&obj, &ObjectBase::onMoveBy);
    ctrl.resize.connect(&obj, &ObjectBase::onResize);
    ctrl.setState.connect(&obj, &ObjectBase::onSetState);
    ctrl.printState.connect(&obj, &ObjectBase::onPrintState);
 
    //ctrl.moveBy.disconnect(&obj);
    //ctrl.moveBy.disconnect_all();
 
    // start pro loop
PRO_Start:
    while(true)
    {
        system("cls");
        cout << "Object Information" << endl;
        cout << "\t Position_x: " << obj.getX() << endl;
        cout << "\t Position_y: " << obj.getY() << endl;
        cout << "\t State: " << obj.getState() << endl;
        cout << "\n";
        cout << "\t m: move object \n"
                "\t r: resize object \n"
                "\t s: set object state \n"
                "\t p: print object state \n"  
                << endl;
        cout << "Input:";
 
        char ch = getchar();
        switch(ch)
        {
            case 'm':       // move
                ctrl.moveBy(10,10);
                break;
            case 'M':
                ctrl.moveBy.emit(-20,-20);
                break;
 
            case 'R':
            case 'r':       // resize
                ctrl.resize.emit(0, 0);
                break;
 
            case 'P':
            case 'p':       // printState
                goto PRO_PrintState;
                break;
 
            case 's':       // setState
                ctrl.setState(Normal);
                break;
            case 'S':
                ctrl.setState.emit(Hidden);
                break;
 
            case 'Q':
            case 'q':       // exit
                goto PRO_Exit;
                break;
            default: 
                break;
        }
    }
 
PRO_PrintState:
    ctrl.printState.emit();
    pause_wait();
    goto PRO_Start;
 
#endif
    pause_wait();
 
PRO_Exit:
    return 0;
}

