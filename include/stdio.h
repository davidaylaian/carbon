#ifndef STDIO_H
#define STDIO_H

#include <drivers/terminal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define EOF -1

// print to stdout
extern void print(string str);
extern void printf(string format, ...);

#endif
