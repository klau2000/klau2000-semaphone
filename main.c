#include "control.h"

int main() {
  int semd;
  int shmd;
  semd = semget(KEY, 1, 0);
  shmd = shmget(KEY, 1, 0);
  //waiting
  printf("trying to get in\n");
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  //getting the last addition
  char * mem;
  mem = shmat(shmd, 0, 0);
  printf("Last addition: %s\n", mem);
  //writing code
  printf("Your addition: ");
  char input[SEG_SIZE];
  fgets(mem, SEG_SIZE, stdin);
  *strchr(mem, '\n') = 0;
  strcpy(input, mem);
  int fd;
  fd = open(filename, O_WRONLY | O_APPEND);
  write(fd, input, strlen(input));
  write(fd, "\n", 1);
  close(fd);
  //end of waiting
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  shmdt(mem);

  return 0;
}
