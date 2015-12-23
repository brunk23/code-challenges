#ifndef SML_MATH_H
#define SML_MATH_H

int opcode_add(machineState *);
int opcode_subtract(machineState *);
int opcode_multiply(machineState *);
int opcode_divide(machineState *);
int opcode_mod(machineState *);
int opcode_inc(machineState *);
int opcode_dec(machineState *);

#endif
