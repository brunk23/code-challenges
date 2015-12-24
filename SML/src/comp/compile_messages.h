#ifndef COMPILE_MESSAGES_H
#define COMPILE_MESSAGES_H

int wmessg(char *);
int emessg(char *,int);
int help_menu(char *);
char *currline(const char *, size_t, int);
int lineno(int);

#endif
