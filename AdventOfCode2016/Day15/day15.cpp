#include <iostream>

using namespace std;

int checktime(int t, int d[6][2]) {
  int i;
  for( i = 0; i < 6; i++ ) {
    if( (d[i][1]+t+i+1)%d[i][0] ) {
      return false;
    }
  }
  return true;
}

int main() {
  int time;
  int disks[6][2];

  disks[0][0] = 13;
  disks[0][1] = 10;

  disks[1][0] = 17;
  disks[1][1] = 15;

  disks[2][0] = 19;
  disks[2][1] = 17;

  disks[3][0] = 7;
  disks[3][1] = 1;

  disks[4][0] = 5;
  disks[4][1] = 0;

  disks[5][0] = 3;
  disks[5][1] = 1;

  for( time = 1; time < 10000000; time++ ) {
    if( checktime(time, disks) ) {
      cout << "It works at time: " << time << endl;
      break;
    }
  }
  
  return 0;
}
