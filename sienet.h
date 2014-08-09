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
        double targetX, targetY, dX, dY, speed;
        sf::Sprite sprite;
        
    public:
        Sieni(sf::Texture* tex);
        Sieni(sf::Texture* tex, double x, double y, double tx, double ty, int hp, int state, int team, int type, double dx, double dy, double speed);
	//void set_values (int,int,int,int,int,int,int,int);
	
	void setPos(double,double);
	double getX();
	double getY();
	
    bool doesCollide(Sieni);

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

    void stop();
        
	double getdx();
	double getdy();
        
        void pathFind();
        
        void areWeThereYet();

        void setPacket(sf::Packet&);
        sf::Packet getPacket();
        
        sf::Sprite& getSprite();

};

sf::Sprite& Sieni::getSprite() {
    return sprite;
}

void Sieni::stop() {
    dX=0;
    dY=0;
}

void Sieni::setPacket(sf::Packet& p) {
    int trash;
    p >> trash;
    int X, Y;
    p >> X >> Y >> targetX >> targetY >> Health >> State >> Team >> Type >> dX >> dY >> speed;
    setPos(X, Y);
}
sf::Packet Sieni::getPacket() {
    sf::Packet p;
    p << 10 << getX() << getY() << targetX << targetY << Health << State << Team << Type << dX << dY << speed;
    return p;
}
Sieni::Sieni(sf::Texture* tex) {
    sprite.setTexture(*tex);
}
Sieni::Sieni(sf::Texture* tex, double x, double y, double tx, double ty, int hp, int state, int team, int type, double dx, double dy, double speed)
:speed(speed){
    sprite.setTexture(*tex);
    setPos(x, y);
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
    sprite.setPosition(x, y);
}
double Sieni::getX() {
    return sprite.getPosition().x;
}
double Sieni::getY() {
    return sprite.getPosition().y;
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
    return targetY;
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
bool Sieni::doesCollide(Sieni s) {
    sf::Sprite ss = s.getSprite();
    return false;
}

void Sieni::pathFind()
{
    double kulma = atan2(targetY - getY(), targetX - getX());
    dY = sin(kulma)*speed;
    dX = cos(kulma)*speed;
}

void Sieni::areWeThereYet() {
    if (abs(getX()-targetX) < speed/2 && abs(getY()-targetY) < speed/2) {
        dX = dY = 0;
    }
}








//===============================================================================





class House
{
	int Health, State, Team, Type;
        sf::Sprite sprite;
    public:
        House(sf::Texture* tex);
        House(sf::Texture* tex, double x, double y, int hp, int state, int team, int type);
        
	void setPos(double,double);
	double getX();
	double getY();
	
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
        
        sf::Sprite& getSprite();
};

sf::Sprite& House::getSprite() {
    return sprite;
}

House::House(sf::Texture* tex){
    sprite.setTexture(*tex);
    sprite.setScale(4,4);
}
House::House(sf::Texture* tex, double x, double y, int hp, int state, int team, int type){
    sprite.setTexture(*tex);
    sprite.setScale(4,4);
    setPos(x,y);
    Health = hp;
    State = state;
    Team = team;
    Type = type;
}
        
void House::setPacket(sf::Packet& p) {
    int trash;
    p >> trash;
    int X, Y;
    p >> X >> Y >> Health >> State >> Team >> Type;
    setPos(X,Y);
}
sf::Packet House::getPacket() {
    sf::Packet p;
    p << 10 << getX() << getY() << Health << State << Team << Type;
    return p;
}
void House::setPos(double x, double y)
{
    sprite.setPosition(x,y);
}
double House::getX()
{
    return sprite.getPosition().x;
}
double House::getY()
{
    return sprite.getPosition().y;
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
