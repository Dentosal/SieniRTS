#include <iostream>
#include "SFML/network.hpp"
#include <cmath>

//               ________________
//          ____/ (  (    )   )  \___
//         /( (  (  )   _    ))  )   )\
//       ((     (   )(    )  )   (   )  )
//     ((/  ( _(   )   (   _) ) (  () )  )
//    ( (  ( (_)   ((    (   )  .((_ ) .  )_
//   ( (  )    (      (  )    )   ) . ) (   )
//  (  (   (  (   ) (  _  ( _) ).  ) . ) ) ( )
//  ( (  (   ) (  )   (  ))     ) _)(   )  )  )
// ( (  ( \ ) (    (_  ( ) ( )  )   ) )  )) ( )
//  (  (   (  (   (_ ( ) ( _    )  ) (  )  )   )
// ( (  ( (  (  )     (_  )  ) )  _)   ) _( ( )
//  ((  (   )(    (     _    )   _) _(_ (  (_ )
//   (_((__(_(__(( ( ( |  ) ) ) )_))__))_)___)
//   ((__)        \\||lll|l||///          \_))
//            (   /(/ (  )  ) )\   )
//          (    ( ( ( | | ) ) )\   )
//           (   /(| / ( )) ) ) )) )
//         (     ( ((((_(|)_)))))     )
//          (      ||\(|(|)|/||     )
//        (        |(||(||)||||        )
//          (     //|/l|||)|\\ \     )
//        (/ / //  /|//||||\\  \ \  \ _)

using namespace std;

class Sieni {
	int X, Y, targetX, targetY, Health, State, Team, Type, dX, dY, speed;
        
    public:
        Sieni();
        Sieni(int x, int y, int tx, int ty, int hp, int state, int team, int type, int dx, int dy, int speed);
	//void set_values (int,int,int,int,int,int,int,int);
	int area () {return X;}
	
	void setPos(int,int);
	int getX();
	int getY();
	
	void setTarget(int,int);
	int getTargetX();
	int getTargetY();
	
	void setHealth(int);
	void heal(int);
	int getHealth();
	
	void setState(int);
	int getState();
	
	void setTeam(int);
	int getTeam();
	
	void setType(int);
	int getType();
        
	int getdx();
	int getdy();
        
        void pathFind();
        
        void areWeThereYet();

        void setPacket(sf::Packet&);
        sf::Packet getPacket();
};

void Sieni::setPacket(sf::Packet& p) {
    int trash;
    p >> trash;
    p >> X >> Y >> targetX >> targetY >> Health >> State >> Team >> Type >> dX >> dY >> speed;
}
sf::Packet Sieni::getPacket() {
    sf::Packet p;
    p << 10 << X << Y << targetX << targetY << Health << State << Team << Type << dX << dY << speed;
    return p;
}
Sieni::Sieni() {
    
}
Sieni::Sieni(int x, int y, int tx, int ty, int hp, int state, int team, int type, int dx, int dy, int speed)
:speed(speed){
    X = x;
    Y = y;
    targetX = tx;
    targetY = ty;
    Health = hp;
    State = state;
    Team = team;
    Type = type;
    dX = dx;
    dY = dy;
}

void Sieni::setPos(int x, int y) {
    X = x;
    Y = y;
}
int Sieni::getX() {
    return X;
}
int Sieni::getY() {
    return Y;
}
void Sieni::setTarget(int tx, int ty) {
    targetX = tx;
    targetY = ty;
}
int Sieni::getTargetX() {
    return targetX;
}
int Sieni::getTargetY()
{
    return Y;
}
void Sieni::setHealth(int hp) {
    Health = hp;
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
int Sieni::getdx()
{
    return dX;
}
int Sieni::getdy()
{
    return dY;
}


void Sieni::pathFind()
{
    double kulma = atan2(1.0*(targetY - Y), 1.0*(targetX - X));
    dY = sin(kulma)*speed;
    dX = cos(kulma)*speed;
}

void Sieni::areWeThereYet() {
    if (abs(X-targetX) < speed && abs(Y-targetY) < speed) {
        dX = dY = 0;
    }
}


class House
{
	int X, Y, targetX, targetY, sizeX, sizeY, Health, State, Team, Type;
public:
	void setPos(int,int);
	int getX();
	int getY();
	
	void setTarget(int,int);
	int getTargetX();
	int getTargetY();
	
	void setSize(int,int);
	int getSizeX();
	int getSizeY();
	
	void heal(int);
	int getHealth();
	
	void setState(int);
	int getState();
	
	void setTeam(int);
	int getTeam();
	
	void setType(int);
	int getType();
	};

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
void House::setSize(int sX, int sY) {
	sizeX = sX;
	sizeY = sX;
}
int House::getSizeX() {
	return sizeX;
}
int House::getSizeY() {
	return sizeY;
}
void House::heal(int hp) {
	Health += hp;
}
int House::getHealth() {
	return Health;
}
void House::setState(int state) {
	State = state;
}
int House::getState() {
	return State;
}
void House::setTeam(int team) {
	Team = team;
}
int House::getTeam() {
	return Team;
}
void House::setType(int type) {
	Type = type;
}
int House::getType() {
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
