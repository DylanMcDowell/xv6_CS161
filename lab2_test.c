#include "types.h"
#include "user.h"

int PScheduler(void);
int test_donation(void);
int test_ticktock(void);
int main(int argc, char *argv[])
{
    if (atoi(argv[1]) == 1)
      PScheduler();
    else if (atoi(argv[1]) == 2)
      test_donation();
    //else if (atoi(argv[1]) == 3)
      //test_ticktock();
    exit(0);
}
/*
int test_ticktock(void){
    int i,j,k;
    int id, pid, ret_pid, exit_status, tik, tok; 
    printf(1, " - Test performance: tik represents running time, tok represents waiting time.\n");
    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid > 0) {
            continue;
        } else if ( pid == 0) {
            for (j = 0; j < 50000; j++) {
                for(k = 0; k < 10000; k++) {
                    asm("nop"); 
                }
            }
            id = gettiktok(&tik, &tok);
            printf(1, " - proc #%d ticks = %d, tocks = %d\n", id, tik, tok);
            exit(0);
        } else {
            printf(2," \n Error fork() \n");
            exit(-1);
        }
    }

    if(pid > 0) {
        for (i = 0; i < 3; i++) {
            ret_pid = wait(&exit_status);
            printf(1, " - This is the parent: child with PID# %d has finished with status %d \n", ret_pid, exit_status); 
        }
    }
	
    return 0;
}
*/

int test_donation(void){
 
    int pid, exit_status;
    
    printf(1, " - default priority is %d\n", getpriority(getpid()));
    pid = fork();
    if(pid == 0){
      /*for(j = 0;j < 50000; j++){
        for(k = 0; k < 10000; k++){
         asm("nop"); 
        }
      }*/
      printf(1, " - child #%d exit with priority %d\n", getpid(), getpriority(getpid()));
      exit(0);
    }
    if(pid > 0){
      setpriority(10);
      printf(1, "- this is parent #%d with priority%d\n", getpid(), getpriority(getpid()));
      waitpid(pid, &exit_status, 0);
    }
    return 0;
}    
      
int PScheduler(void){
		 
    // Use this part to test the priority scheduler. Assuming that the priorities range between 0 to 31
    // 0 is the highest priority. All processes have a default priority of 10
    // You can use your own priority range/value setup

    int pid, ret_pid, exit_status;
    int i,j,k;
  
    printf(1, "Testing the priority scheduler and setpriority system call:\n");
    printf(1, "Assuming that the priorities range between 0 to 31\n");
    printf(1, "0 is the highest priority. All processes have a default priority of 10\n");
    printf(1, " - The parent processes will switch to priority 0\n");
    setpriority(0); // Use your own setpriority interface
    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid > 0) {
            continue;
        } else if ( pid == 0) {
            printf(1, " - Hello! this is child# %d and I will change my priority to %d \n", getpid(), 31-5*i);
            setpriority(31-5*i); // Use your own setpriority interface
            for (j = 0; j < 50000; j++) {
                for(k = 0; k < 10000; k++) {
                    asm("nop"); 
                }
            }
            printf(1, " - Child #%d with priority %d has finished! \n", getpid(), 31-5*i);	
            printf(1, " - The process with pid %d has a priority of %d after aging.\n", getpid(), getpriority(getpid()));
            exit(0);
        } else {
            printf(2," \n Error fork() \n");
            exit(-1);
        }
    }

    if(pid > 0) {
        for (i = 0; i < 3; i++) {
            printf(1, " - The process with pid %d has a priority of %d right now.\n", 3, getpriority(3));
            printf(1, " - The process with pid %d has a priority of %d right now.\n", 4, getpriority(4));
            printf(1, " - The process with pid %d has a priority of %d right now.\n", 5, getpriority(5));
            ret_pid = wait(&exit_status);
            printf(1, " - This is the parent: child with PID# %d has finished with status %d \n", ret_pid, exit_status); 
        }
        printf(1, " - If processes with highest priority finished first then its correct. \n");
    }
			
    return 0;
}


