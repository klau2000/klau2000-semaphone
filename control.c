#include "control.h"

FILE *f;
char *filename = "file.txt";

int control(char * option){ //command string
  if (!strcmp(option, "-c")) create();
  else if (!strcmp(option, "-v")) view();
  else if (!strcmp(option, "-r")) removes();
}

int create(){
  //semaphore creation
  int semd;
  int v, r;
  char input[3];
  semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    printf("error %d: %s\n", errno, strerror(errno));
    semd = semget(KEY, 1, 0);
    v = semctl(semd, 0, GETVAL, 0);
    printf("semaphore created\n");
  }
  else {
    union semun us;
    us.val = 1;
    r = semctl(semd, 0, SETVAL, us);
    printf("semaphore created\n");
  }
  //shared memory creation
  int shmd;
  char * data;
  shmd = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  data = shmat(shmd, 0, 0);
  printf("shared memory created\n");
  //file creation
  f = fopen(filename, "w");
  printf("file created\n");
}

int removes(){
  int semd;
  int shmd;
  shmctl(shmd, IPC_RMID, 0);
  printf("shared memory removed\n");
  remove(filename);
  printf("file removed\n");
  semctl(semd, IPC_RMID, 0);
  printf("semaphore removed\n");
}

int view(){
  printf("The story so far: \n");
  f = fopen(filename, "r");
  while(filename){
    char * temp;
    fgets(temp, sizeof temp, f);
  }
  fclose(f);
}

char ** parse_args(char *line, char * sep){
  char ** ans = calloc(1024, sizeof(char));
  char *curr = line;
  int count = 0;
  while (curr){
    if (!strcmp(sep, " ")){
      char *temp = strsep(&curr, sep);
      if(strcmp(temp , "")){
        ans[count]= temp;
        count++;
      }
    }
    else{
      ans[count] = strsep(&curr, sep);
      count++;
    }
  }
  return ans;
}

int main(int argc, char *argv[]) {
    char input[1024];
    fgets(input, sizeof input, stdin);
    control(input);
    return 0;
  }
