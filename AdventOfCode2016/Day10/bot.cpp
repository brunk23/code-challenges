#include <iostream>
#include "bot.h"

Bot::Bot() {
  number = -1;
  givesLowTo = -1;
  givesHighTo = -1;
  chips[0] = -1;
  chips[1] = -1;
}

bool Bot::exists() {
  if( number > -1 ) {
    return true;
  }
  return false;
}

void Bot::setLow(int n, int low) {
  number = n;
  givesLowTo = low;
}

void Bot::setHigh(int n, int high) {
  number = n;
  givesHighTo = high;
}

void Bot::gets(int n) {
  // std::cerr << number << " got: " << n << std::endl;
  if( chips[0] == -1 ) {
    chips[0] = n;
  } else {
    chips[1] = n;
  }
}

bool Bot::winner() {
  if( (chips[1] == 61 && chips[0] == 17) ||
      (chips[1] == 17 && chips[0] == 61) ) {
    std::cerr << "I handle 61 and 17. My number is " << number << std::endl;
    return true;
  }
  return false;
}

bool Bot::hasBoth() {
  if( (chips[0] > 0) && (chips[1] > 0) ) {
    std::cerr << "Had both" << std::endl;
    return true;
  }
  return false;
}

int Bot::lowTo() {
  return givesLowTo;
}

int Bot::highTo() {
  return givesHighTo;
}

void Bot::reset() {
  chips[0] = -1;
  chips[1] = -1;
}

int Bot::has(int n) {
  if( n >=0 && n <=1 ) {
    return chips[n];
  }
  return -1;
}
