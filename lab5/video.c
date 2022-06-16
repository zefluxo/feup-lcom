#include "video.h"
#include <lcom/lab5.h>
#include <lcom/lcf.h>
#include <machine/int86.h>

static vbe_mode_info_t vmi;
static void *base_addr;

int(read_mode)(vbe_mode_info_t *buffer, uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r)); /* zero the structure */

  r.intno = 0x10;
  r.ax = 0x4F01; // VBE call, function 01 -- VBE mode info
  r.es = PB2BASE((int) &buffer);
  r.di = PB2OFF((int) &buffer);
  r.cx = mode;

  if (sys_int86(&r) != CALL_SUCCESS) {
    printf("read_mode: sys_int86() failed \n");
    return 1;
  }

  return 0;
}

int(change_mode)(uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r)); /* zero the structure */

  r.intno = 0x10;
  r.ax = AH_DEFAULT << 8 | MODE_SET; // VBE call, function 02 -- set VBE mode
  r.bx = 1 << 14 | mode;

  if (sys_int86(&r) != CALL_SUCCESS) {
    printf("change_mode: sys_int86() failed \n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(map_vm)(uint16_t mode) {

  int r;
  struct minix_mem_range mr; /* physical memory range */

  if (vbe_get_mode_info(mode, &vmi) != 0)
    return EXIT_FAILURE;

  phys_bytes vram_base = vmi.PhysBasePtr; /* VRAM's physical addresss */
  unsigned int vram_size = 
    (vmi.XResolution * vmi.YResolution) * 
    (vmi.BytesPerScanLine / vmi.XResolution); 
    /* VRAM's size, but you can use frame the frame-buffer size, instead */

  /* Allow memory mapping */
  mr.mr_base = vram_base;
  mr.mr_limit = mr.mr_base + vram_size;
  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */
  base_addr = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
  if (base_addr == MAP_FAILED)
    panic("couldn't map video memory");

  return 0;
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
  void *addr = (void *)((char *) base_addr + offset);

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
        void *addr = (void *)((char *) base_addr + offset);

        uint8_t bpp = img.size / (img.height * img.width);

        memcpy(addr, img.bytes + (cnt*bpp), vmi.BytesPerScanLine / vmi.XResolution);
        x++;
        cnt++;
        
    }
    y++;
    x = ox;
  }
}
