#include "defines.h"
#include <stdint.h>
#include <lcom/lcf.h>

int (read_mode)(vbe_mode_info_t* buffer, uint16_t mode);
int (change_mode)(uint16_t mode);
int (map_vm)(uint16_t mode);
void (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
void (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y);
