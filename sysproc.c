#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
<<<<<<< HEAD
#include "record.h"


=======
#include "recordlist.c"
#define NULL (void*)0
>>>>>>> 3b2cb5cc4164eaf76bfe2c78ef3f917709156f97

int
sys_startrecording(){
  if(proc->logging == 1)
  {
     return -1;
  }

  else
  {
    proc->logging = 1;
    add_record(NULL, NULL);
    return 0;
  }
}

int
sys_stoprecording(){
  
  if(proc->logging == 0)
  {
     return -1;
  }
  
  else
  {
     proc->logging = 0;
     return 0;
  }
}

int
sys_fetchrecords(struct record *records, int num_records)
{
<<<<<<< HEAD


 // print_records(records, num_records);
  return 0;

}

typedef struct rnode recordnode;

struct rnode
{
	struct record *rec;
	struct rnode *next;
};

void add_record(struct rnode* rlist, struct record* re)
{
	struct rnode *cur = rlist;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	
	struct rnode *newnode = (struct rnode*)kalloc();
	newnode->rec = re;
	newnode->next = NULL;
	cur->next = newnode;
}

int print_records(struct record *records, int num_records)
{
	struct rnode *cur = proc->recordlist;
	int count = 0;
	
	if (records != NULL)
	{
		while(cur->next != NULL)
		{
			if (count < num_records)
			{
				records[count] = *(cur->rec);
				cur = cur->next;
				count++;
			}
			else
				break;
		}
	}
	else
	{
		while (cur->next != NULL)
		{
			count++;
		}
		count++;
	}
	return count;
=======
  return print_records(records, num_records);
  //return 0;
  //if first arg is null return total number of records (not num_records) 

>>>>>>> 3b2cb5cc4164eaf76bfe2c78ef3f917709156f97
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
