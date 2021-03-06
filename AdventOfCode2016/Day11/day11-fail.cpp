#include <iostream>
#include <string>

using namespace std;

enum kind {microchip, generator};
enum element {thu, plu, str, pro, rut};

class Component {
public:
  bool exists;
  int type;
  int isotope;

  Component() {
    exists = false;
    type = -1;
    isotope = -1;
  }

  Component(int t, int i) {
    exists = true;
    type = t;
    isotope = i;
  }
  
  Component operator=(Component &inp) {
    exists = inp.exists;
    type = inp.type;
    isotope = inp.isotope;
  }

  Component operator=(Component *inp) {
    exists = inp->exists;
    type = inp->type;
    isotope = inp->isotope;
  }

  bool operator==(Component &inp) {
    if( exists ) {
      if( (type == inp.type) && (isotope == inp.isotope) ) {
	return true;
      }
    }
    return false;
  }

  void remove() {
    exists = false;
  }
  
  bool existp() {
    return exists;
  }

  friend std::ostream& operator<<(std::ostream& out, Component c) {
    if( c.exists ) {
      out << "[" << c.type << "|" << c.isotope << "]";
    }
    return out;
  }
  
};

class Elevator {
public:
  Component has[2];
  int floor;

  Elevator() {
    floor = 0;
  }
  
  void add(Component *a) {
    int i;

    for( i = 0; i < 2; i++ ) {
      if( !has[i].existp() ) {
	has[i] = a;
	return;
      }
    }
  }

  void remove(Component a) {
    int i;

    for( i = 0; i < 2; i++ ) {
      if( has[i] == a ) {
	has[i].remove();
	return;
      }
    }
  }
  
  friend std::ostream& operator<<(std::ostream& out, Elevator e) {
    out << "Elevator at floor " << e.floor << " has: ";
    out << e.has[0] << " " << e.has[1];
    return out;
  }
    
};

class Floor {
public:
  Component has[10];
  
  void add(Component *a) {
    int i;

    for( i = 0; i < 10; i++ ) {
      if( !has[i].existp() ) {
	has[i] = a;
	return;
      }
    }
  }

  void remove(Component a) {
    int i;

    for( i = 0; i < 10; i++ ) {
      if( has[i] == a ) {
	has[i].remove();
	return;
      }
    }
  }

  friend std::ostream& operator<<(std::ostream &out, Floor f) {
    int i;
    out << "Floor: ";
    for( i=0; i<9  ; i++ ) {
      out << f.has[i] << " ";
    }
    out << f.has[i];
    return out;
  }
};

class Building {
public:
  Floor floor[4];
  Elevator elev;

  Building() {

  }

  
  
  /// This is NOT RIGHT. We need to check for floors
  /// That have a microchip and a non-matching generator
  bool safe() {
    bool generatorOnFloor = false;
    int i,j,k, g,m;
    
    for( i = 0; i < 4; i++ ) {
      generatorOnFloor = false;

      // check for generator
      for( j=0; j<10; j++ ) {
	if( !floor[i].has[j].exists ) {
	  break;
	}
	if( floor[i].has[j].type == generator ) {
	  generatorOnFloor == true;
	}
      }
      if( elev.floor == i ) {
	if( (elev.has[0].type == generator) ||
	    (elev.has[1].type == generator) ) {
	  generatorOnFloor = true;
	}
      }
      if( !generatorOnFloor ) {
	// No generator is always safe
	continue;
      }
      ///
      ///  Now we need to see if there is a microchip.
      ///  If so, it needs matching generator
      ///

      
    }
    return true;
  }

  friend std::ostream& operator<<(std::ostream &out, Building b) {
    int i;
    out << "Building\n" << b.elev << "\n";
    for( i = 0; i < 4; i++ ) {
      out << b.floor[i] << "\n";
    }
    return out;
  }
    
};

int main(int argc, char *argv[]) {
  Building a;

  a.floor[0].add(new Component(generator, thu));
  a.floor[0].add(new Component(microchip, thu));
  a.floor[0].add(new Component(generator, plu));
  a.floor[0].add(new Component(generator, str));

  a.floor[1].add(new Component(microchip, plu));
  a.floor[1].add(new Component(microchip, str));

  a.floor[2].add(new Component(generator, pro));
  a.floor[2].add(new Component(microchip, pro));
  a.floor[2].add(new Component(generator, rut));
  a.floor[2].add(new Component(microchip, rut));
  
  cout << a << endl;

  a.elev.add( &a.floor[0].has[0] );
  a.floor[0].remove( a.elev.has[0] );

  cout << a << endl;
  
  return 0;
}
