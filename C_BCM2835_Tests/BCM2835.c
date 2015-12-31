#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include "BCM2835.h"

volatile uint8_t *bcmBase;

volatile uint8_t *registerToAddress(uint32_t base, uint32_t offset) {
  // Debug
  //printf("registerToAddress: bcmBase=0x%x, base=0x%x, offset=0x%x\n", bcmBase, base, offset);
  return (volatile uint8_t *)(bcmBase + base + offset);
}



void init() {
  int fd = open("/dev/mem", O_RDWR | O_SYNC);
  if (fd < 0) {
    perror("Error opening /dev/mem");
    assert(fd >= 0);
    return;
  }
  printf("BCM2835_BASE=0x%x\n", BCM2835_BASE);
  bcmBase = mmap(
    NULL, // Let the OS decide where to map into our virtual address space
    0x1000000, // Map in data
    PROT_READ | PROT_WRITE, // Ask for both read and write access to the memory
    MAP_SHARED, // Ask for shared access which will cause writes to be propagated to the real memory
    fd, // The file descriptor to the /dev/mem device
    BCM2835_BASE // The offset to the base of BCM memory
  );
  if (bcmBase == MAP_FAILED) {
    perror("mmap");
    assert(bcmBase != MAP_FAILED);
  }
  printf("gpioBase = 0x%x\n", bcmBase);
  close(fd);
}
