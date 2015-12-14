// Let's do this one with classes.

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

#define MAXNAME 20

class Deer {
public:
	Deer();
	void setDeer(const char *, int, int, int);
	~Deer();
	void tick();		// 1 second goes by
	void awardPoint();
	int getPoints();
	int getTotal();		// how far has the deer gone
	const char *getName();

private:
	char name[MAXNAME];
	int speed;
	int run_time;
	int rest_time;
	int remaining;
	int total;
	int points;
	bool running;
};

Deer::Deer()
{
	name[0] = '\0';
	speed = 0;
	run_time = 0;
	rest_time = 0;
	remaining = 0;
	total = 0;
	points = 0;
	running = false;
}

// This was constructor, but not sure how to handle this with
// arrays, so use it to set things
void Deer::setDeer(const char *n, int s, int run, int rest)
{
	for(int x = 0; x < MAXNAME; x++) {
		name[x] = n[x];
		if( name[x] == '\0' )
			break;
	}
	speed = s;
	run_time = run;
	rest_time = rest;
	remaining = run;	// we have this much time before break
	total = 0;		// start at 0 distance run
	points = 0;
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

void Deer::awardPoint()
{
	points++;
}

int Deer::getPoints()
{
	return points;
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

void getinput(Deer []);

// Input file and problem description
const int RDEER = 9;
const int TIME = 2503;

int main()
{
	Deer racers[RDEER];

	int farthest = INT_MIN;

	getinput(racers);

	// test data
	// racers[0].setDeer("Comet",14,10,127);
	// racers[1].setDeer("Dancer",16,11,162);

	for(int x = 0; x < TIME; ++x) {
		for(int y = 0; y < RDEER; ++y) {
			racers[y].tick();
		}
		farthest = racers[0].getTotal();		
		for(int y = 1; y < RDEER; ++y) {
			if(racers[y].getTotal() > farthest) {
				farthest = racers[y].getTotal();
			}
		}
		for(int y = 0; y < RDEER; ++y) {
			if(racers[y].getTotal() == farthest) {
				racers[y].awardPoint();
			}
		}
	}

	for(int x = 0; x < RDEER; ++x) {
		cout << racers[x].getName() << " got points "
			<< racers[x].getPoints() <<endl;
	}
	return 0;
}

void getinput(Deer racers[RDEER])
{
	string input;
	int speed, runt, restt, found, count;
	char name[MAXNAME];

	count = 0;

	while( getline(cin, input) ) {
		speed = runt = restt = found = 0;
		for(unsigned int x = 0; x < input.size(); ++x) {
			switch (found) {
			case 0:
				name[x] = input[x];
				if( name[x] == ' ' ) {
					name[x] = '\0';
					found++;
				}
				break;
			case 1:
				if( input[x] >= '0' && input[x] <= '9' ) {
					speed *= 10;
					speed += input[x] - '0';
				} else {
					if ( speed > 0 ) {
						found++;
					}
				}
				break;
			case 2:	
				if( input[x] >= '0' && input[x] <= '9' ) {
					runt *= 10;
					runt += input[x] - '0';
				} else {
					if ( runt > 0 ) {
						found++;
					}
				}
				break;
			case 3:
				if( input[x] >= '0' && input[x] <= '9' ) {
					restt *= 10;
					restt += input[x] - '0';
				} else {
					if ( restt > 0 ) {
						found++;
					}
				}
				break;
			case 4:
			default:
				// we're done, do nothing
				break;
			}
		}
		racers[count].setDeer(name,speed,runt,restt);
		count++;
	}
}
