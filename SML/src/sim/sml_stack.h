#ifndef SML_STACK_H
#define SML_STACK_H

int opcode_push(machineState *);
int opcode_pop(machineState *);
int opcode_call(machineState *);
int opcode_ret(machineState *);

#endif
