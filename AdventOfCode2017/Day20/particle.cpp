#include "particle.h"
#include <string>

using std::string;

int Particle::abs(int n) {
  if( n < 0 ) {
    return -n;
  }
  return n;
}

int Particle::strtoint(string s, int off) {
  int i = off, val = 0;
  bool negative = false;

  if( s[i] == '-' ) {
    negative = true;
    i++;
  }
  
  while( s[i] >= '0' && s[i] <= '9' ) {
    val *= 10;
    val += s[i] - '0';
  }
  if( negative ) {
    return -val;
  }
  return val;
}

Particle::Particle() {
  setPos(0,0,0);
  setVel(0,0,0);
  setAcc(0,0,0);
  prevDist = -1;
  currDist = -1;
}

Particle::~Particle() {
}

int Particle::parseDef(string line) {
  int x, y, z;
  
  return 0;
}

void Particle::setPos(int x, int y, int z) {
  position[0] = x;
  position[1] = y;
  position[2] = z;
}

void Particle::setVel(int x, int y, int z) {
  velocity[0] = x;
  velocity[1] = y;
  velocity[2] = z;
}

void Particle::setAcc(int x, int y, int z) {
  acceleration[0] = x;
  acceleration[1] = y;
  acceleration[2] = z;
}

void Particle::update() {
  velocity[0] += acceleration[0];
  velocity[1] += acceleration[1];
  velocity[2] += acceleration[2];
  position[0] += velocity[0];
  position[1] += velocity[1];
  position[2] += velocity[2];
}

int Particle::distance() {
  return distance(0,0,0);
}

int Particle::distance(int x, int y, int z) {
  prevDist = currDist;
  currDist = abs(x - position[0]) + abs(y - position[1]) +
    abs(z - position[2]);
  return currDist;
}

int Particle::change() {
  if( prevDist >= 0 && currDist >= 0 ) {
    return abs(prevDist - currDist);
  }
  return -1;
}
