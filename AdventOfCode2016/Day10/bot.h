#ifndef BOT
#define BOT

#define MAXBOTS 300

class Bot {
 private:
  int number;
  int givesLowTo;
  int givesHighTo;
  int chips[2];

 public:
  Bot();

  void print();
  bool winner();
  bool exists();
  bool hasBoth();
  void setHigh(int, int);
  void setLow(int, int);
  void gets(int);
  void reset();
  int has(int);
  int lowTo();
  int highTo();
};

#endif
