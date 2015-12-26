#ifndef COMPILE_UTILITY_H
#define COMPILE_UTILITY_H

char *getNextToken(char *, struct Token *);
int iptr(int);
int stringtable(int);
int oplev(char);
int str2token(char *, struct Token *);
int insert_symbol(struct Token *, struct Token[]);
int test_symbol(struct Token *, struct Token[], struct Token[]);
int stringmemreq(int);

#endif
