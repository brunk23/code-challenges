#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
 private:
  int position[3];
  int velocity[3];
  int acceleration[3];
  int prevDist;
  int currDist;
  int abs(int);
  int strtoint(string, int);
  
 public:
  Particle();
  ~Particle();
  void setPos(int,int,int);
  void setVel(int,int,int);
  void setAcc(int,int,int);
  void update();
  int change();
  int distance();
  int distance(int,int,int);
};


#endif
