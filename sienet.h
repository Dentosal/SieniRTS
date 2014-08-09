#include <iostream>
#include "SFML/network.hpp"
#include "SieniRTS/SFML/Graphics/Texture.hpp"
#include "SieniRTS/SFML/Graphics/Sprite.hpp"
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
	int Health, State, Team, Type;
        double X, Y, targetX, targetY, dX, dY, speed;
        sf::Sprite sprite;
        
    public:
        Sieni(sf::Texture tex);
        Sieni(sf::Texture tex, double x, double y, double tx, double ty, int hp, int state, int team, int type, double dx, double dy, double speed);
	//void set_values (int,int,int,int,int,int,int,int);
	int area () {return X;}
	
	void setPos(double,double);
	double getX();
	double getY();
	
	void setTarget(double,double);
	double getTargetX();
	double getTargetY();
	
	void setHealth(int);
	void heal(int);
	int getHealth();
	
	void setState(int);
	int getState();
	
	void setTeam(int);
	int getTeam();
	
	void setType(int);
	int getType();
        
	double getdx();
	double getdy();
        
        void pathFind();
        
        void areWeThereYet();

        void setPacket(sf::Packet&);
        sf::Packet getPacket();
        
        sf::Sprite& getSprite() {
            return sprite;
        }

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
Sieni::Sieni(sf::Texture tex) {
    sprite.setTexture(tex);
}
Sieni::Sieni(sf::Texture tex, double x, double y, double tx, double ty, int hp, int state, int team, int type, double dx, double dy, double speed)
:speed(speed){
    sprite.setTexture(tex);
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

void Sieni::setPos(double x, double y) {
    X = x;
    Y = y;
}
double Sieni::getX() {
    return X;
}
double Sieni::getY() {
    return Y;
}
void Sieni::setTarget(double tx, double ty) {
    targetX = tx;
    targetY = ty;
}
double Sieni::getTargetX() {
    return targetX;
}
double Sieni::getTargetY()
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
double Sieni::getdx()
{
    return dX;
}
double Sieni::getdy()
{
    return dY;
}


void Sieni::pathFind()
{
    double kulma = atan2(targetY - Y, targetX - X);
    dY = sin(kulma)*speed;
    dX = cos(kulma)*speed;
}

void Sieni::areWeThereYet() {
    if (abs(X-targetX) < speed/2 && abs(Y-targetY) < speed/2) {
        dX = dY = 0;
    }
}








//===============================================================================





class House
{
	int sizeX, sizeY, Health, State, Team, Type;
        double X, Y;
        sf::Sprite sprite;
    public:
        House(sf::Texture tex);
        House(sf::Texture tex, double x, double y, int hp, int state, int team, int type);
        
	void setPos(double,double);
	double getX();
	double getY();
	
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
        
        void setPacket(sf::Packet&);
        sf::Packet getPacket();
        
        sf::Sprite& getSprite() {
            return sprite;
        }
};



House::House(sf::Texture tex){
    sprite.setTexture(tex);
}
House::House(sf::Texture tex, double x, double y, int hp, int state, int team, int type){
    sprite.setTexture(tex);
    X = x;
    Y = y;
    Health = hp;
    State = state;
    Team = team;
    Type = type;
}
        
void House::setPacket(sf::Packet& p) {
    int trash;
    p >> trash;
    p >> X >> Y >> Health >> State >> Team >> Type;
}
sf::Packet House::getPacket() {
    sf::Packet p;
    p << 10 << X << Y << Health << State << Team << Type;
    return p;
}
void House::setPos(double x, double y)
{
	X = x;
	Y = y;
}
double House::getX()
{
	return X;
}
double House::getY()
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
