#include <iostream>
#include <iomanip>

using std::setw;
using std::cout;
using std::endl;

struct Item {
  char *name;
  int cost;
  int damage;
  int armor;
};

void create_item(Item *, const char *, int, int, int);
void print_item(Item *);
bool survive_fight(Item *weapon, Item *armor, Item *ring1, Item *ring2);

int main()
{
  int total = INT_MAX;
  int cost;
  Item weapons[6];
  Item armor[6];
  Item rings[8];
  
  // Populate the arrays with the problem data
  create_item(&weapons[0], "Dagger", 8, 4, 0);
  create_item(&weapons[1], "Shortsword", 10, 5, 0);
  create_item(&weapons[2], "Warhammer", 25, 6, 0);
  create_item(&weapons[3], "Longsword", 40, 7, 0);
  create_item(&weapons[4], "Greataxe", 74, 8, 0);
  create_item(&weapons[5], "Unarmed", 0, 0, 0);
  
  create_item(&armor[0], "Leather", 13, 0, 1);
  create_item(&armor[1], "Chainmail", 31, 0, 2);
  create_item(&armor[2], "Splintmail", 53, 0, 3);
  create_item(&armor[3], "Bandedmail", 75, 0, 4);
  create_item(&armor[4], "Platemail", 102, 0, 5);
  create_item(&armor[5], "T-Shirt", 0, 0, 0);

  create_item(&rings[0], "Damage +1", 25, 1, 0);
  create_item(&rings[1], "Damage +2", 50, 2, 0);
  create_item(&rings[2], "Damage +3", 100, 3, 0);
  create_item(&rings[3], "Defense +1", 20, 0, 1);
  create_item(&rings[4], "Defense +2", 40, 0, 2);
  create_item(&rings[5], "Defense +3", 80, 0, 3);
  create_item(&rings[6], "Damage +0", 0, 0, 0);
  create_item(&rings[7], "Defense +0", 0, 0, 0);

  for(int w = 0; w < 6; ++w) {	// cycle through each weapon
    for(int a = 0; a < 6; ++a) { // cycle though each armor
      for(int r1 = 0; r1 < 7; ++r1) {
	for(int r2 = r1+1; r2 < 8; ++r2) {
	  if( survive_fight( &weapons[w],
			     &armor[a],
			     &rings[r1],
			     &rings[r2]) ) {
	    cost = weapons[w].cost + armor[a].cost
	      + rings[r1].cost + rings[r2].cost;
	    if ( cost < total ) {
	      total = cost;
	    }
	  }
	}
      }
    }
  }

  cout << "The cheapest amount to survive is: " << total << endl;
  
  return 0;
}

bool survive_fight(Item *weapon, Item *armor, Item *ring1, Item *ring2)
{
  int hit = 0;
  int health = 100;
  int damage = weapon->damage + ring1->damage + ring2->damage;
  int defense = armor->armor + ring1->armor + ring2->armor;

  // from input file
  int e_health = 103;
  int e_damage = 9;
  int e_armor = 2;

  while( true ) {
    // we hit boss
    if( (hit = damage - e_armor) < 1 ) {
      hit = 1;
    }
    if( (e_health -= hit ) <= 0 ) {
      return true;		// we won!
    }
    
    // boss hits us
    if( (hit = e_damage - defense) < 1 ) {
      hit = 1;
    }
    if( (health -= hit ) <= 0 ) {
      return false;		// we lost
    }
  }
  // this will never be reached
  return true;
}

void print_item(Item *item)
{
  cout << setw(13) << item->name << ":"
       << setw(5) << item->cost << "g"
       << setw(5) << item->damage
       << setw(5) << item->armor << endl;
}

void create_item(Item *item, const char *n,
		 int ncost, int ndamage, int narmor)
{
  int x = 0;
  item->name = new char[ strlen(n) ];
  while( ( true ) ) {
    item->name[x] = n[x];
    if( n[x] == 0 ) {
      break;
    }
    ++x;
  }
  item->cost = ncost;
  item->damage = ndamage;
  item->armor = narmor;
}
