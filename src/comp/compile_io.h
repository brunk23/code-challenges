#ifndef COMPILE_IO_H
#define COMPILE_IO_H

int output_core(char *, int[]);
int process_source(const char *, int[]);
int decode_line(char *,int[],struct Token [],struct Token[]);

#endif
