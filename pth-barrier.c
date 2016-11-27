
#include <stdio.h>
#include <pth.h>
 
int use_barrier;
pth_barrier_t barrier;
 
void *slave(void *arg)
{
    int id = (int * )arg;
 
    printf("T%d\n", id);
 
   
    if (use_barrier)
        pth_barrier_reach(&barrier);
 
    printf("  T%d\n", id);
    return NULL;
}
 
#define NUMBER 3
void test()
{
    int i;
    pth_t tid[NUMBER];

    pth_attr_t attr[NUMBER];

   printf("pth_init = %d\n", pth_init());
   pth_barrier_init(&barrier, NUMBER);

	

  
	 for (i = 0; i < NUMBER; i++)
	{

     		attr[i] = pth_attr_new();
     		pth_attr_set(attr[i], PTH_ATTR_NAME, "slave");
     		pth_attr_set(attr[i], PTH_ATTR_STACK_SIZE, 64*1024);
   
   		tid[i]= pth_spawn(attr[i], slave, (void *)i);
 
   	}
 
    	for (i = 0; i < NUMBER; i++)
        	pth_join(tid[i], NULL);
    
}
 
int main()
{
    use_barrier = 0;
    test();
    
 
    use_barrier = 1;
    test();
    return 0;
}

















