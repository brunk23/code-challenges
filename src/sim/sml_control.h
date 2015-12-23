#ifndef SML_CONTROL_H
#define SML_CONTROL_H

int opcode_branch(machineState *);
int opcode_branch_neg(machineState *);
int opcode_branch_zero(machineState *);
int opcode_nop(machineState *);
int opcode_halt(machineState *);
int opcode_invalid(machineState *);

#endif
