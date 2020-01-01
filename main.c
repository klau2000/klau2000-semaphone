#include "control.h"

int main() {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  semop(sem, &sb, 1);
  <more code>
  sb.sem_op = 1;
  semop(sem, &sb, 1);
}
