// Let's do this one with classes.

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

class Deer {
public:
	Deer();
	void setDeer(const char *, int, int, int);
	~Deer();
	void tick();		// 1 second goes by
	int getTotal();		// how far has the deer gone
	const char *getName();

private:
	const char *name;
	int speed;
	int run_time;
	int rest_time;
	int remaining;
	int total;
	bool running;
};

Deer::Deer()
{
	name = "";
	speed = 0;
	run_time = 0;
	rest_time = 0;
	remaining = 0;
	total = 0;
	running = false;
}

// This was constructor, but not sure how to handle this with
// arrays, so use it to set things
void Deer::setDeer(const char *n, int s, int run, int rest)
{
	name = n;
	speed = s;
	run_time = run;
	rest_time = rest;
	remaining = run;	// we have this much time before break
	total = 0;		// start at 0 distance run
	running = true;		// start running at zero
}

Deer::~Deer()
{
	// We don't need to do anything here
}

void Deer::tick()
{
	if( running ) {
		total += speed;
	}
	if( --remaining == 0 ) {
		if( running ) {
			running = false;
			remaining = rest_time;
		} else {
			running = true;
			remaining = run_time;
		}
	}
}

// return km travelled
int Deer::getTotal()
{
	return total;
}

const char *Deer::getName()
{
	return name;
}

// Input file and problem description
const int RDEER = 9;
const int TIME = 2503;

int main()
{
	Deer racers[RDEER];

	// test data
	// racers[0].setDeer("Comet",14,10,127);
	// racers[1].setDeer("Dancer",16,11,162);

	for(int x = 0; x < TIME; ++x) {
		for(int y = 0; y < RDEER; ++y) {
			racers[y].tick();
		}
	}

	// initial testing
	// cout << racers[0].getName() << " went "
	//	<< racers[0].getTotal() <<endl;
	// cout << racers[1].getName() << " went "
	//	<< racers[1].getTotal() <<endl;

	return 0;
}
