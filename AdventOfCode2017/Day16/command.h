#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "programs.h"

using std::cerr;
using std::endl;

class Command {
private:
  struct Demand {
    char opt;
    int v1;
    int v2;
    char c1;
    char c2;
    Demand *next;
  };

  Demand *head;
  Demand *tail;
  int count;
  
  void attach(Demand *tmp) {
    count++;
    if( head == 0 ) {
      head = tmp;
      tail = tmp;
      return;
    }
    tail->next = tmp;
    tail = tmp;
  }
  
public:
  Command() {
    head = 0;
    tail = 0;
    count = 0;
  }

  void add(int n) {
    Demand *tmp = new Demand;

    tmp->opt = 's';

    tmp->v1 = n;
    tmp->v2 = -1;

    tmp->c1 = '#';
    tmp->c2 = '#';

    tmp->next = 0;
    attach(tmp);
  }

  void add(int n, int p) {
    Demand *tmp = new Demand;

    tmp->opt = 'x';

    tmp->v1 = n;
    tmp->v2 = p;

    tmp->c1 = '#';
    tmp->c2 = '#';

    tmp->next = 0;

    attach(tmp);
  }

  void add(char n, char p) {
    Demand *tmp = new Demand;

    tmp->opt = 'p';

    tmp->v1 = -1;
    tmp->v2 = -1;

    tmp->c1 = n;
    tmp->c2 = p;

    tmp->next = 0;

    attach(tmp);
  }

  void run(Programs &p) {
    Demand *curr = head;

    while(curr) {
      switch( curr->opt ) {
      case 'x':
	p.exchange(curr->v1, curr->v2);
	break;
      case 's':
	p.spin(curr->v1);
	break;
      case 'p':
	p.partner(curr->c1, curr->c2);
	break;
      default:
	cerr << "Command not found" << endl;
	return;
      }
      curr = curr->next;
    }
  }

  int commandLength() {
    return count;
  }

};

#endif
