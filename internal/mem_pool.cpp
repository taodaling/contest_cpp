#pragma once
#include <iostream>
char MEM[230 << 20];
char *MEM_HEAD = MEM;
void *operator new(size_t sz) {
  char *ans = MEM_HEAD;
  MEM_HEAD += sz;
  return ans;
}
void operator delete(void *m) {
}
