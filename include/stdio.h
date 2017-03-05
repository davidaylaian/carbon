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
extern void println(string str);

// print to string
extern string sprint(string ret, string str);
extern string sprintf(string ret, string format, ...);
extern string sprintln(string ret, string str);

#endif
