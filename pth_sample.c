#include <stdio.h>
#include <stdlib.h>
#include <pth.h>

void *cb_Function();


main()
{
   int rc1, rc2;
   pth_attr_t pthAttr1; 
   pth_t tid1;

   /* Initialize pth library */ 
   pth_init();	

   /* Create independent threads each of which will execute cb_function */

     pthAttr1 = pth_attr_new();
     pth_attr_set(pthAttr1, PTH_ATTR_NAME, "cb_function");
     pth_attr_set(pthAttr1, PTH_ATTR_STACK_SIZE, 64*1024);
     tid1 = pth_spawn(pthAttr1, cb_function, NULL);
		
   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pth_join( tid1, NULL);

   printf("\nThread is terminated\n");	

   exit(EXIT_SUCCESS);
}

void *cb_function()
{
   printf(" Pth has been created successfully \n");
}
