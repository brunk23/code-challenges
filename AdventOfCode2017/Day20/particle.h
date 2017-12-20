#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>

class Particle {
 private:
  int position[3];
  int velocity[3];
  int acceleration[3];
  int abs(int);
  int strtoint(std::string, int);
  bool alive;
  
 public:
  Particle();
  ~Particle();
  int parseDef(std::string);
  void setPos(int,int,int);
  void setVel(int,int,int);
  void setAcc(int,int,int);
  void update();
  int changeA();
  int changeV();
  void die();
  bool exists() const;
  int distance();
  int distance(int,int,int);
  bool operator==(const Particle &);
};


#endif
