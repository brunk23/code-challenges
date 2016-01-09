#include <iostream>
#include <climits>

/*
 * We use Dijkstra's algorithm here. Basically, just
 * take the unvisited node with the shortest possible
 * path and find the shortest paths to the surrounding
 * nodes from there (ignoring ones we have already
 * visited). The distance we get at the end node will be
 * the shortest possible distance.
 */

using std::cout;
using std::endl;
using std::cin;

#define size 80

int main()
{
  int arr[size][size], visited[size][size];
  int mindist[size][size], row, col, possible;
  int nrow, ncol, mxloops;
  
  for(row = 0; row < size; ++row) {
    for(col = 0; col < size; ++col) {
      cin >> arr[row][col];
      visited[row][col] = 0;
      mindist[row][col] = INT_MAX;
    }
  }
  visited[0][0] = 1;
  mindist[0][0] = arr[0][0];

  /* starting at 0,0 go to each */

  row = 0;
  col = 0;

  for( mxloops = 0; mxloops < size*size; ++mxloops ) {

    /* This will check the surrounding nodes, if we have
     * not visited it already, we check to see if the current
     * distance to it is shorter than the old distance to it
     */
    if( row > 0 && !visited[row-1][col] ) {
      possible = mindist[row][col] + arr[row-1][col];
      if( possible < mindist[row-1][col] ) {
	mindist[row-1][col] = possible;
      }
    }
    if( (row < size - 1) && !visited[row+1][col] ) {
      possible = mindist[row][col] + arr[row+1][col];
      if( possible < mindist[row+1][col] ) {
	mindist[row+1][col] = possible;
      }
    }
    if( col > 0 && !visited[row][col-1] ) {
      possible = mindist[row][col] + arr[row][col-1];
      if( possible < mindist[row][col-1] ) {
	mindist[row][col-1] = possible;
      }
    }
    if( col < size -1 && !visited[row][col+1] ) {
      possible = mindist[row][col] + arr[row][col+1];
      if( possible < mindist[row][col+1] ) {
	mindist[row][col+1] = possible;
      }
    }
    visited[row][col] = 1;
    /* THIS ENDS THE CHECK PORTION */

    /* Next Node will be the unvisited node with the 
     * smallest possible distance to it.
     */
    possible = INT_MAX;
    for( row = 0; row < size; ++row) {
      for( col = 0; col < size; ++col ) {
	if( !visited[row][col] ) {
	  if( mindist[row][col] < possible ) {
	    nrow = row;
	    ncol = col;
	    possible = mindist[row][col];
	  }
	}
      }
    }
    row = nrow;
    col = ncol;
    if( (row == size-1) && (col == size-1) ) {
      break;
    }
  }

  /******* Print test output, to see it working
  for( row = 0; row < size; ++row ) {
    for( col = 0; col < size; ++col ) {
      cout << mindist[row][col] << " ";
    }
    cout << endl;
  }
  ********/

  cout << "The minimum path was: " << mindist[size-1][size-1] << endl;

  return 0;
}
