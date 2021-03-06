#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <inttypes.h>

#define CONTROL_START     0x44E10000
#define CONTROL_STATUS    0x40
#define DEVICE_ID         0x600
#define CONTROL_END       0x44E11444
#define CONTROL_SIZE      (CONTROL_END - CONTROL_START)

int main() {
  int fd = open("/dev/mem", O_RDWR);

  if(fd == -1) {
    printf("COULDN'T OPEN FILE\n");
    exit(1);
  }

  volatile void *const base = mmap(0, CONTROL_SIZE, PROT_READ | PROT_WRITE,
                                MAP_SHARED, fd, CONTROL_START); 
  if(mmap == MAP_FAILED) {
    printf("MAP FAILED\n");
    exit(1);
  }

  volatile uint32_t *const status = base + (CONTROL_STATUS);
  volatile uint32_t *const dev_info = base + (DEVICE_ID);
  printf("Hardware Info: %x\n", *(volatile uint32_t *)status);
  printf("Device Info: %x\n", *(volatile uint32_t *)dev_info);

  close(fd);
  return 0;
}
