#include"comm.h"

static int comm(int num,int flag)
{
	key_t key = ftok(_PATH_NAME_,_PROJ_ID_);
	if(key < 0){
		printf("comm:%s\n",strerror(errno));
		return -1;
	}
	int sems_id = semget(key,num,flag);
}
int create_sem_set(int num)
{
	int flag = IPC_CREAT | IPC_EXCL;
	return comm(num,flag);
}

int get_sem_set(int num)
{
	int flag = IPC_CREAT;
	return comm(num,flag);
}
int destroy_sem_set(int sem_id)
{
	if(semctl(sem_id,0,IPC_RMID) < 0){
		printf("%s\n",strerror(errno));
		return -1;
	}
	return 0;
}
int init_sem_set(int sem_id,int which,int val)
{
	union semnu _un;
	_un.val = val;
	if(semctl(sem_id,which,SETVAL,_un) < 0){
		printf("init:%s\n",strerror(errno));
		return -1;
	}
	return 0;
}
static int com_sem_op(int sem_id,int op)
{
	struct sembuf _sembuf;
	memset(&_sembuf, '\0', sizeof(_sembuf));
	_sembuf.sem_num = 0;
	_sembuf.sem_op = op;
	_sembuf.sem_flg = 0;
	if(semop(sem_id,&_sembuf,1) < 0){
		printf("op:%s\n",strerror(errno));
		return -1;
	}
	return 0;
}
int P_sem_set(int sem_id)
{
	printf("P:");
	return com_sem_op(sem_id,-1);
}
int V_sem_set(int sem_id)
{
	printf("V:");
	return com_sem_op(sem_id,1);
}


