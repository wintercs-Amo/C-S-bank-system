#ifndef TOOLS_H
#define TOOLS_H
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getch.h>

void clear_stdin(void);
char* get_str(char* str,size_t len);
char get_sex(void);
int get_cmd(int start,int end);
char* get_pw(char* passwd,bool is_show,size_t size);
void any_key(void);

#endif//TOOLS_H
