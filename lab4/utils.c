#include <lcom/utils.h>
#include <lcom/lcf.h>
#include <stdint.h>

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t value32 = 0x00;
  int ret_value = sys_inb(port, &value32);

  *value = value32;
  return ret_value;
}
