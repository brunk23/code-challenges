#include <iostream>
#include <string>

#define WIDTH 50
#define HEIGHT 6

using namespace std;

void makeBox(char [HEIGHT][WIDTH], int, int);
void rotateRow(char [HEIGHT][WIDTH], int, int);
void rotateCol(char [HEIGHT][WIDTH], int, int);
void initDisplay(char [HEIGHT][WIDTH]);
void showDisplay(char [HEIGHT][WIDTH]);
int countPixels(char [HEIGHT][WIDTH]);

int countPixels(char disp[HEIGHT][WIDTH]) {
  int row, col, amount = 0;

  for(row = 0; row < HEIGHT; row++ ) {
    for( col = 0; col < WIDTH; col++ ) {
      if(disp[row][col] == '#' ) {
	amount++;
      }
    }
  }
  return amount;
}

void rotateCol(char disp[HEIGHT][WIDTH], int col, int amount) {
  char tmp = ' ';
  int curr, i;

  for( curr = 0; curr < amount; curr++ ) {
    tmp = disp[HEIGHT-1][col];
    for( i = HEIGHT-1; i > 0; i-- ) {
      disp[i][col]=disp[i-1][col];
    }
    disp[0][col] = tmp;
  }
}

void rotateRow(char disp[HEIGHT][WIDTH], int row, int amount) {
  char tmp = ' ';
  int curr, i;

  for( curr = 0; curr < amount; curr++ ) {
    tmp = disp[row][WIDTH-1];
    for( i = WIDTH-1; i > 0; i-- ) {
      disp[row][i]=disp[row][i-1];
    }
    disp[row][0] = tmp;
  }
}

void initDisplay(char disp[HEIGHT][WIDTH]) {
  int row, col;

  for( row = 0; row < HEIGHT; row++ ) {
    for( col = 0; col < WIDTH; col++ ) {
      disp[row][col] = ' ';
    }
  }
}

void showDisplay(char disp[HEIGHT][WIDTH]) {
  int row, col;

  for( row = 0; row < HEIGHT; row++ ) {
    for( col = 0; col < WIDTH; col++ ) {
      cout << disp[row][col];
    }
    cout << endl;
  }
}

void makeBox(char disp[HEIGHT][WIDTH], int cols, int rows) {
  int i, j;

  for( i = 0; i < rows; i++ ) {
    for( j = 0; j < cols; j++ ) {
      disp[i][j] = '#';
    }
  }
}

int main(int argc, char *argv[]) {
  char disp[HEIGHT][WIDTH];
  string input;
  int i, a, b;
  
  initDisplay(disp);

  while( cin >> input ) {
    // RECT
    if( input[1] == 'e' ) {
      cin >> input;
      a = 0;
      b = 0;
      for(i = 0; i < input.length(); i++) {
	if( input[i] == 'x' ) {
	  i++;
	  break;
	}
	a *= 10;
	a += input[i] - '0';
      }
      for( ; i < input.length(); i++ ) {
	b *= 10;
	b += input[i] - '0';
      }
      makeBox(disp, a, b);
      continue;
    }
    // END RECT
    cin >> input;

    // ROTATE ROW
    if( input[0] == 'r' ) {
      cin >> input;
      a = 0;
      b = 0;
      for( i = 2; i < input.length(); i++) {
	a *= 10;
	a += input[i] - '0';
      }
      cin >> input;
      cin >> input;
      for( i=0; i < input.length(); i++) {
	b *= 10;
	b += input[i] - '0';
      }
      rotateRow(disp, a, b);
      continue;
    }
    // END ROTATE ROW

    // ROTATE COL
    cin >> input;
    a = 0;
    b = 0;
    for( i = 2; i < input.length(); i++) {
      a *= 10;
      a += input[i] - '0';
    }
    cin >> input;
    cin >> input;
    for( i = 0 ; i < input.length(); i++) {
      b *= 10;
      b += input[i] - '0';
    }
    rotateCol(disp, a, b);
  }
  
  showDisplay(disp);
  cout << endl << "There were " << countPixels(disp) << " pixels lit." << endl;
  
  return 0;
}
