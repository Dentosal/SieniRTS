#include <iostream>



using namespace std;

class Sieni {
    int X, Y, targetX, targetY, Health, State, Team, Type;
  public:
    void set_values (int,int,int,int,int,int,int,int);
    int area () {return X;}
    
    void setPos(int,int);
    int getX();
    int getY();
    
    void setTarget(int,int);
    int getTargetX();
    int getTargetY();
    
    void heal(int);
    int getHealth();
    
    void setState(int);
    int getState();
    
    void setTeam(int);
    int getTeam();
    
    void setType(int);
    int getType();
};
class House
    {
    int X, Y, targetX, targetY, Health, State, Team, Type;
public:
    void setPos(int,int);
    int getX();
    int getY();
    
    void setTarget(int,int);
    int getTargetX();
    int getTargetY();
    
    void heal(int);
    int getHealth();
    
    void setState(int);
    int getState();
    
    void setTeam(int);
    int getTeam();
    
    void setType(int);
    int getType();
    };

void Sieni::setPos(int x, int y)
    {
    X = x;
    Y = y;
    }
int Sieni::getX()
    {
    return X;
    }
int Sieni::getY()
    {
    return Y;
    }
void Sieni::setTarget(int tx, int ty)
    {
    targetX = tx;
    targetY = ty;
    }
int Sieni::getTargetX()
    {
    return targetX;
    }
int Sieni::getTargetY()
    {
    return Y;
    }
void Sieni::heal(int hp)
    {
    Health += hp;
    }
int Sieni::getHealth()
    {
    return Health;
    }
void Sieni::setState(int state)
    {
    State = state;
    }
int Sieni::getState()
    {
    return State;
    }
void Sieni::setTeam(int team)
    {
    Team = team;
    }
int Sieni::getTeam()
    {
    return Team;
    }
void Sieni::setType(int type)
    {
    Type = type;
    }
int Sieni::getType()
    {
    return Type;
    }


void House::setPos(int x, int y)
    {
    X = x;
    Y = y;
    }
int House::getX()
    {
    return X;
    }
int House::getY()
    {
    return Y;
    }
void House::setTarget(int tx, int ty)
    {
    targetX = tx;
    targetY = ty;
    }
int House::getTargetX()
    {
    return targetX;
    }
int House::getTargetY()
    {
    return Y;
    }
void House::heal(int hp)
    {
    Health += hp;
    }
int House::getHealth()
    {
    return Health;
    }
void House::setState(int state)
    {
    State = state;
    }
int House::getState()
    {
    return State;
    }
void House::setTeam(int team)
    {
    Team = team;
    }
int House::getTeam()
    {
    return Team;
    }
void House::setType(int type)
    {
    Type = type;
    }
int House::getType()
    {
    return Type;
    }
/*
void Sieni::set_values (int x, int y, int tx, int ty, int hp, int state, int team) {
  X = x;
  Y = y;
  targetX = tx;
  targetY = ty;
  Health = hp;
  State = state;
  Team = team;
}
*/
