#include"comm.h"

int main()
{
	int sem_id = create_sem_set(1);
	init_sem_set(sem_id,0,1);

	pid_t id = fork();
	if(id == 0){
		int sems = get_sem_set();
		while(1){
			P_sem_set(sems);

			printf("A");
			fflush(stdout);
			sleep(1);
			printf("A");
			fflush(stdout);
			sleep(1);

			V_sem_set(sems);
		}
	}
	else{
		while(1){
			P_sem_set(sem_id);

			printf("B");
			fflush(stdout);
			sleep(2);
			printf("B");
			fflush(stdout);
			sleep(2);

			V_sem_set(sem_id);
		}
	}
	return 0;
}
