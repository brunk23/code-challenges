#include <iostream>

using std::cout;
using std::endl;

#define DEAD INT_MAX
#define VERBOSE false
#define HARDMODE true
#define BOSSHP 55
#define BOSSDM 8

class Turn {
public:
  Turn();
  Turn(const Turn &);
  ~Turn();
  Turn &operator=(const Turn &);
  Turn &cast(int);
  bool isAlive() { return alive; }
  bool bossDead() { return ( bossHP <= 0); }
  int getUsed() { return usedMana; }

private:
  void die();
  void startTurn(const char *);
  void shield();
  void poison();
  void recharge();
  void tick();			// will do boss turn
  static int gameCount;
  int ourHP;
  int ourMana;
  int usedMana;
  int shieldRemain;
  int poisonRemain;
  int rechargeRemain;
  int bossHP;
  bool alive;
  const int bossDamage;
};

Turn::Turn()
  : ourHP(50), ourMana(500), usedMana(0), shieldRemain(0),
    poisonRemain(0), rechargeRemain(0), bossHP(BOSSHP),
    bossDamage(BOSSDM), alive(true)
{
  gameCount++;
  if(VERBOSE) {
    cout << "New game (" << gameCount << ") started." << endl;
  }
}

Turn::Turn(const Turn &old)
  : ourHP(old.ourHP), ourMana(old.ourMana), usedMana(old.usedMana),
    shieldRemain(old.shieldRemain), poisonRemain(old.poisonRemain),
    rechargeRemain(old.rechargeRemain), bossHP(old.bossHP),
    bossDamage(old.bossDamage), alive(old.alive)
{
  gameCount++;
  if(VERBOSE) {
    cout << "New instance of game (" << gameCount
	 << ") started." << endl;
  }
}

Turn::~Turn()
{
  if(VERBOSE) {
    cout << "Game (" << gameCount << ") ended." << endl;
  }
  gameCount--;
}
  
Turn &Turn::operator=(const Turn &old)
{
  ourHP = old.ourHP;
  ourMana = old.ourMana;
  usedMana = old.usedMana;
  shieldRemain = old.shieldRemain;
  poisonRemain = old.poisonRemain;
  rechargeRemain = old.rechargeRemain;
  bossHP = old.bossHP;
  alive = old.alive;
}

void Turn::shield()
{
  shieldRemain--;
  if(VERBOSE) {
    cout << "Shield's timer now: " << shieldRemain << endl;
  }
}

void Turn::poison()
{
  bossHP -= 3;
  poisonRemain--;
  if(VERBOSE) {
    cout << "Poison deals 3 damage; its timer is now " << poisonRemain
	 << "." << endl;
  }
}

void Turn::recharge()
{
  rechargeRemain--;
  ourMana += 101;
  if(VERBOSE) {
    cout << "Recharge provides 101 mana; its timer is now "
	 << rechargeRemain << "." << endl;
  }
}
  
/*
 * Will perform each spell
 */
Turn &Turn::cast(int spell)
{
  // Our turn
  startTurn("Player");

  if( HARDMODE ) {
    /*
     * Hard Mode
     */
    ourHP--;
    if( ourHP <= 0 ) {
      die();
      return *this;
    }
  }
  
  switch( spell ) {
  case 0:
    // Magic Missile
    if( ourMana < 53 ) {
      die();
      return *this;
    }
    ourMana -= 53;
    usedMana += 53;
    bossHP -= 4;
    if(VERBOSE) {
      cout << "Player casts Magic Missile, dealing 4 damage." << endl;
    }
    break;
    
  case 1:
    // Drain
    if( ourMana < 73 ) {
      die();
      return *this;
    }
    ourMana -= 73;
    usedMana += 73;
    bossHP -= 2;
    ourHP += 2;
    if(VERBOSE) {
      cout << "Player casts Drain, dealing 2 damage, and healing"
	   << " 2 hit points." << endl;
    }
    break;
    
  case 2:
    // Shield
    if( ourMana < 113 || shieldRemain > 0) {
      die();
      return *this;
    }
    ourMana -= 113;
    usedMana += 113;
    shieldRemain = 6;
    if(VERBOSE) {
      cout << "Player casts Shield" << endl;
    }
    break;
    
  case 3:
    // Poison
    if( ourMana < 173 || poisonRemain > 0) {
      die();
      return *this;
    }
    ourMana -= 173;
    usedMana += 173;
    poisonRemain = 6;
    if(VERBOSE) {
      cout << "Player casts Poison" << endl;
    }
    break;
    
  case 4:
    // recharge
    if( ourMana < 229 || rechargeRemain > 0) {
      die();
      return *this;
    }
    ourMana -= 229;
    usedMana += 229;
    rechargeRemain = 5;
    if(VERBOSE) {
      cout << "Player casts Recharge" << endl;
    }
    break;
    
  default:
    // Not a valid spell, die
    if(VERBOSE) {
      cout << "You try something completely unexpected.\nIt doesn't work\n";
    }
    die();
    return *this;
  }

  if(VERBOSE) {
    cout << endl;
  }
  
  if( bossHP > 0 ) {
    // Run the actual battle
    tick();
  }
  if( bossHP <= 0 ) {
    if(VERBOSE) {
      cout << "This kills the boss, and the player wins." << endl;
    }
  }

  return *this;
}

void Turn::die()
{
  if(VERBOSE) {
    cout << "You died." << endl;
  }
  alive = false;
}

void Turn::startTurn(const char *name)
{
  if(VERBOSE) {
    cout << "-- " << name << " Turn --\n-Player has " << ourHP
	 << " hit points, 0 armor, " << ourMana
	 << " mana" << endl;
    cout << "- Boss has " << bossHP << " hit points" << endl;
  }
  if(shieldRemain) {
    shield();
  }
  if(poisonRemain) {
    poison();
  }
  if(rechargeRemain) {
    recharge();
  }
}
  
/*
 * Will actually do both turns
 */
void Turn::tick()
{
  int damage = bossDamage;
  startTurn("Boss");

  if( bossHP <= 0 ) {
    return;
  }
  
  if(shieldRemain) {
    damage -= 7;
  }
  
  if(damage < 1) {
    damage = 1;
  }
  
  if(VERBOSE) {
    cout << "Boss attacks for " << bossDamage;
    if(shieldRemain) {
      cout << " - " << (bossDamage - damage) << " = " << damage;
    }
    cout << " damage!" << endl << endl;
  }

  ourHP -= damage;
  if ( ourHP <= 0 ) {
    die();
  }
}

int Turn::gameCount = 0;
int run_games(Turn &curr, int level);

int main()
{
  Turn start;
  int min = INT_MAX;
  
  min = run_games(start, min);

  cout << "The minimum mana needed is: " << min << endl;
  
  return 0;
}

int run_games(Turn &curr, int min)
{
  if( curr.getUsed() >= min ) {
    return min;
  }
  if( !curr.isAlive() ) {
    return min;
  }
  if( curr.bossDead() ) {
    return curr.getUsed();
  }

  int temp, x;
  Turn next;
  
  for( x = 0; x < 5; ++x ) {
    next = curr;
    temp = run_games(next.cast(x), min);
    if( temp < min ) {
      min = temp;
    }
  }

  return min;
}
