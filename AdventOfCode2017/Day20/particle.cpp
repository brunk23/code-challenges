#include "particle.h"
#include <string>

using std::string;

bool Particle::operator==(const Particle &o) {
  if( o.exists() ) {
    if(position[0] == o.position[0] &&
       position[1] == o.position[1] &&
       position[2] == o.position[2] ) {
      return true;
    }
  }
  return false;
}

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
    i++;
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
  alive = true;
}

Particle::~Particle() {
}

int Particle::parseDef(string line) {
  unsigned int count = 0, i, state = 0;
  int val[3];
  bool numb = false;
  
  for(i = 0; i < line.length(); i++ ) {
    if( numb ) {
      if(line[i] == '-' || (line[i] >= '0' &&
			    line[i] <= '9') ) {
	continue;
      }
      numb = false;
    } else {
      if( line[i] == '-' || (line[i] >= '0' &&
			     line[i] <= '9') ) {
	val[count] = strtoint(line, i);
	numb = true;
	count++;
	if(count == 3 ) {
	  count = 0;
	  switch( state ) {
	  case 0:
	    setPos(val[0], val[1], val[2]);
	    break;
	  case 1:
	    setVel(val[0], val[1], val[2]);
	    break;
	  default:
	    setAcc(val[0], val[1], val[2]);
	    break;
	  }
	  state++;
	}
      }
    }
  }
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
  int currDist;
  currDist = abs(x - position[0]) + abs(y - position[1]) +
    abs(z - position[2]);
  return currDist;
}

int Particle::changeA() {
  return abs(acceleration[0]) + abs(acceleration[1]) +
    abs(acceleration[2]);
}

int Particle::changeV() {
  return abs(velocity[0]) + abs(velocity[1]) +
    abs(velocity[2]);
}

void Particle::die() {
  alive = false;
}

bool Particle::exists() const {
  return alive;
}
