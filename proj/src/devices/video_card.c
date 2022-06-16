#include "./devices/video_card.h"

static vbe_mode_info_t vmi;
static void *base_addr;
static void *second_addr;
static uint16_t screen_center_x;
static uint16_t screen_center_y;

void *(vg_init)(uint16_t mode) {

  int r, a, b;

  if ((b = vbe_get_mode_info(mode, &vmi)) != 0) {
    return NULL;
  }

  if ((r = map_vm()) != 0) {
    return NULL; 
  }  

  if ((a = change_mode(mode)) != 0) {
    return NULL;
  }

  return base_addr;
}

int(change_mode)(uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r)); /* zbase_addrero the structure */

  r.intno = 0x10;
  r.ax = AH_DEFAULT << 8 | MODE_SET; // VBE call, function 02 -- set VBE mode
  r.bx = 1 << 14 | mode;

  if (sys_int86(&r) != CALL_SUCCESS) {
    printf("change_mode: sys_int86() failed \n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(map_vm)() {
  int r;
  struct minix_mem_range mr; /* physical memory range */
  phys_bytes vram_base = vmi.PhysBasePtr;                                                                  /* VRAM's physical addresss */
  unsigned int vram_size = (vmi.XResolution * vmi.YResolution) * (vmi.BytesPerScanLine / vmi.XResolution); /* VRAM's size, but you can use frame the frame-buffer size, instead */

  screen_center_x = vmi.XResolution/2;
  screen_center_y = vmi.YResolution/2;

  /* Allow memory mapping */
  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */
  base_addr = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
  second_addr = malloc(vram_size);
  if (base_addr == MAP_FAILED)
    panic("couldn't map video memory");

  return 0;
}

void swap_buffer() {
  memcpy(base_addr, second_addr, vmi.XResolution * vmi.YResolution * (vmi.BytesPerScanLine / vmi.XResolution));
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  if (y + height > vmi.YResolution)
    height = vmi.YResolution - y;
  if (x + width > vmi.XResolution)
    width = vmi.XResolution - x;

  for (int i = 0; i < height; i++) {
    vg_draw_hline(x, y, width, color);
    y++;
  }

  return EXIT_SUCCESS;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    draw_pixel(x, y, color);
    x++;
  }

  return EXIT_SUCCESS;
}

void(draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
  void *addr = (void *) ((char *) second_addr + offset);

  memcpy(addr, &color, vmi.BytesPerScanLine / vmi.XResolution);
}

void(draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y) {
  if (y + img.height > vmi.YResolution)
    y = vmi.YResolution - img.height;
  if (x + img.width > vmi.XResolution)
    x = vmi.XResolution - img.width;

  uint64_t cnt = 0;
  uint16_t ox = x;

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
      void *addr = (void *) ((char *) second_addr + offset);

      uint8_t bpp = img.size / (img.height * img.width);

      uint32_t color = 0;
      for (size_t off = 0; off < 3; off++)
        color |= *(img.bytes + (cnt * bpp) + off) << (off * 8);

      if (color == 0x00b140) {
        cnt++;
        x++;
        continue;
      }
      
      memcpy(addr, img.bytes + (cnt * bpp), vmi.BytesPerScanLine / vmi.XResolution);
      x++;
      cnt++;
    }
    y++;
    x = ox;
  }
}


int vg_draw_vline(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len; i++) {
    draw_pixel(x, y, color);
    y++;
  }

  return EXIT_SUCCESS;
}

int vg_draw_score_bg(xpm_image_t square) {
  uint16_t x = vmi.XResolution - square.width - 50;
  uint16_t y = 10;

  draw_xpm(square, x, y);

  return x;
}

int vg_draw_board(xpm_image_t board) {
  uint8_t tetromino_side = (vmi.YResolution - 30)/16;
  uint8_t x = screen_center_x - (tetromino_side * 5) - 10;

  draw_xpm(board, x, 10);

  return EXIT_SUCCESS;
}

void draw_board_block(xpm_image_t img, uint8_t x, uint8_t y) {
  draw_xpm(img, (img.width * x) + (screen_center_x - 5 * img.width), ((vmi.YResolution-55) - (y * img.height)));
}

void vg_draw_character(xpm_image_t font, uint16_t x, uint16_t y, uint8_t scale, uint8_t *pnt) {
  uint16_t ox = x;

  for (int i = 0; i < 7; i++) { // y
    for (int k = 0; k < scale; k++) {
      for (int j = 0; j < 6; j++) { // x
        for (int l = 0; l < scale; l++) {
          uint64_t offset = ((y * vmi.XResolution) + x) * (vmi.BytesPerScanLine / vmi.XResolution);
          void *addr = (void *) ((char *) second_addr + offset);

          uint8_t bpp = font.size / (font.height * font.width);

          uint32_t color = 0;
          for (size_t off = 0; off < 3; off++)
            color |= *(pnt + (j + i*font.width) * bpp + off) << (off * 8);

          if (color == 0x00b140) {
            x++;
            continue;
          }
        
          memcpy(addr, pnt + ((i * font.width) + j) * bpp, vmi.BytesPerScanLine / vmi.XResolution);
          x++;
        }
      }
    y++;
    x = ox;
    }
  }
}
