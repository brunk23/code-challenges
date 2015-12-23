#ifndef COMPILE_UTILITY_H
#define COMPILE_UTILITY_H

char *getNextToken(char *, struct Token *);
int iptr(int);
int oplev(char);
int str2token(const char *, struct Token *);
int insert_symbol(struct Token *, struct Token[]);
int test_symbol(struct Token *, struct Token[], struct Token[]);

#endif
