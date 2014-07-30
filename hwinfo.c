#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#define CONTROL   0x44E10000
#define DEVICE_ID 0x600
#define END       0x44E11444

int main() {
  volatile uint32_t *dev_info;
  int fd = open("/dev/mem", O_RDWR);

  if(fd == -1) {
    printf("COULDN'T OPEN FILE\n");
    exit(1);
  }
  volatile void *base = mmap(0, END-CONTROL, PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd, CONTROL); 
  if(mmap == MAP_FAILED) {
    printf("MAP FAILED\n");
    exit(1);
  }

  dev_info = base + (DEVICE_ID);
  printf("%x\n", *(volatile uint32_t *)dev_info);

  close(fd);
  return 0;
}
