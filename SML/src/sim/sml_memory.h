#ifndef SML_MEMORY_H
#define SML_MEMORY_H

int opcode_load(machineState *sml);
int opcode_store(machineState *sml);
int opcode_read(machineState *sml);
int opcode_write(machineState *sml);

#endif
