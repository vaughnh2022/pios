#include "rprintf.h"
#include "mmu.h"
extern struct table_descriptor_stage1 L1table[512];
unsigned long get_timer_count(){
   unsigned long *time_count_register =(unsigned long *)0x3f003004;
   return *time_count_register;
}
void wait_msec(int plus){
   unsigned long first = get_timer_count()+plus;
   unsigned long second;
   while(second<first){
      second=get_timer_count();
   }
}
void clearBSS(){
   extern int __bss_start,__bss_end;
   char *begin_bss = &__bss_start;
   char *end_bss = &__bss_end;
   for (char *ptr=begin_bss;ptr<=end_bss;ptr++){
      *ptr=0;
   }
}
unsigned int getEL(){
   unsigned int el;
   asm("mrs %0,CurrentEL"
       : "=r"(el)
       :
       :);
   return el;
}
void printInTerminal(){
   esp_printf(putc,"current execution level is %d\r\n",getEL());
}
void mapPager(){
   mapPages((void*)0,(void*)0);
  loadPageTable(&L1table[0]);
}
int kernel_main() {
   return 0;
}

