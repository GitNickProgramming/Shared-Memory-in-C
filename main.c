/*Collatz Sequence using shared memory.*/

/*Ranjidha 02/11/2020 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h> /*  This header file is necessary for using shared
   memory constructs
*/

main()
{
int shmid,status;
int *a, *b;
int i,num;
     
shmid = shmget(IPC_PRIVATE, 1*sizeof(int), 0777|IPC_CREAT);
        /* Accept number here i parent*/
num=35;

if (fork() == 0) {

/* Create Child Process */

	b = (int *) shmat(shmid, 0, 0); //Shared memory reading value

  printf("\tChild reads: %d\n",b[0]);

  while(b[0]>1){
	  if(b[0]%2==0) {
      b[0]=b[0]/2;}
    else{
  	  b[0]=(b[0]*3)+1;
    }
    printf("\tChild reads: %d\n",b[0]);
  }
shmdt(b);
} else {
	a = (int *) shmat(shmid, 0, 0);

	a[0] = num;  //Assign number in Parent shared memory

	wait(&status);

	shmdt(a);

	shmctl(shmid, IPC_RMID, 0);
}
}