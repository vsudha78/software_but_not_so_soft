#include <stdio.h>
#include <stdlib.h>
#include <pth.h>

void *cb_Function();

int  counter = 0;

pth_mutex_t mutex = PTH_MUTEX_INIT;

main()
{
   int rc1, rc2;
   pth_attr_t attr1, attr2; 
   pth_t tid1,tid2;

   /* Initialize pth library */ 
   pth_init();	

   /* Create independent threads each of which will execute cb_function */

     attr1 = pth_attr_new();
     pth_attr_set(attr1, PTH_ATTR_NAME, "cb_function");
     pth_attr_set(attr1, PTH_ATTR_STACK_SIZE, 64*1024);
     tid1 = pth_spawn(attr1, cb_function, NULL);

     attr2 = pth_attr_new();
     pth_attr_set(attr2, PTH_ATTR_NAME, "cb_function");
     tid2 = pth_spawn(attr2, cb_function, NULL);

		
   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pth_join( tid1, NULL);
   pth_join( tid2, NULL); 

   printf("\nBoth threads are terminated\n");	

   exit(EXIT_SUCCESS);
}

void *cb_function()
{
   pth_mutex_acquire(&mutex, FALSE, NULL);
   counter++;
   printf("Counter value: %d\n",counter);
   pth_mutex_release(&mutex);
}
