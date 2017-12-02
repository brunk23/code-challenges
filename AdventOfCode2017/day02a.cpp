#include <iostream>

int main() {
  int sheet[16][16];
  int x = 0, y = 0, min, max, chksum = 0, input;

  
  while( std::cin >> input ) {
    if( y%16 == 0 ) {
      y = 0;
      min = input;
      max = input;
    }
    sheet[x][y] = input;
    if( input < min ) {
      min = input;
    }
    if( input > max ) {
      max = input;
    }
    y++;
    if( y == 16 ) {
      x++;
      y = 0;
      chksum += (max - min);
    }
  }

  std::cout << "Part a checksum: " << chksum << std::endl;

  chksum = 0;
  for( x = 0; x < 16; x++ ) {
    for( y = 0; y < 15; y++ ) {
      for( min = y+1; min < 16; min++ ) {
	if( (sheet[x][y] % sheet[x][min]) == 0 ) {
	  chksum += sheet[x][y]/sheet[x][min];
	}
	if( (sheet[x][min] % sheet[x][y]) == 0 ) {
	  chksum += sheet[x][min]/sheet[x][y];
	}
      }
    }
  }

  std::cout << "Evenly divisible checksum " << chksum << std::endl;

  return 0;
}
