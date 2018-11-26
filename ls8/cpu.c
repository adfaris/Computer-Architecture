#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DATA_LEN 12

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char MAR)
{
  return cpu->RAM[MAR];
}

void cpu_ram_write(struct cpu *cpu, unsigned char MAR, unsigned char MDR)
{
  cpu->RAM[MAR] = MDR;
}
/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      // 0b10000010, // LDI R0,8
      // 0b00000000,
      // 0b00001000,
      // 0b01000111, // PRN R0
      // 0b00000000,
      // 0b00000001 // HLT
      0b10000010,
      0b00000000,
      0b00001000,
      0b10000010,
      0b00000001,
      0b00001001,
      0b10100010,
      0b00000000,
      0b00000001,
      0b01000111,
      0b00000000,
      0b00000001,

  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->RAM[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    cpu->registers[regA] *= cpu->registers[regB];
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);
    // 2. switch() over it to decide on a course of action.
    switch (IR)
    {
    case LDI:
      cpu->registers[operandA] = operandB;
      break;

    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      break;

    case HLT:
      running = 0;
      break;

    case MUL:
      alu(cpu, ALU_MUL, operandA, operandB);
      break;
    }
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.
    cpu->PC += (IR >> 6) + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  memset(cpu->registers, 0, sizeof(cpu->registers));

  // TODO: Zero registers and RAM
  memset(cpu->RAM, 0, sizeof(cpu->RAM));
}
