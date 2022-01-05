#include "L0/sym_lib_hacks.h"

#ifdef CONFIG_X86_64
// TODO turn this into a header?
asm(".include \"../arch/x86/arch_x86.S\"");
#endif

extern char __executable_start;
extern char __etext;

void sym_touch_every_page_text(){
  unsigned char *p;
  p = (unsigned char *) &__executable_start;

  unsigned char c;
  for(; p < (unsigned char *)&__etext; p+= (1<<12))
    c = *p;
}

void sym_touch_stack(){
  // Num times to push
  int count = 1<<16;

  int i;
  // Touch a bunch of stack pages
  for(i=0; i < count; i++){
    __asm__("PUSH_JUNK":::"memory");
    /* __asm__("pushq $42":::"memory"); */
  }

  // Pop them all off
  for(i=0; i < count; i++){
    // Find a way to make clobber rax arch agnostic
    __asm__("POP_JUNK": /*no*/: /*no*/ : "rax");
  }
}
