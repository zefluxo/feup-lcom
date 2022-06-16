 #pragma once
  
 #include <stdint.h>
 #include <stdio.h>
  
 // a line containing XPM information (both the data and the pointer are constant)
 typedef char const *const xpm_row_t;
  
 // ensure that neither the pointer nor the content of an XPM pixmap can be changed
 typedef xpm_row_t * const xpm_map_t;
  
 #define TRANSPARENCY_COLOR_1_5_5_5 0x8000
 #define TRANSPARENCY_COLOR_8_8_8_8 0xFF000000
 #define CHROMA_KEY_GREEN_888 0x00b140
 #define CHROMA_KEY_GREEN_565 0x0588
  
 enum xpm_image_type {
   XPM_INDEXED,
   XPM_1_5_5_5,
   XPM_5_6_5,
   XPM_8_8_8,
   XPM_8_8_8_8,
   INVALID_XPM
 };
  
 typedef struct {
   enum xpm_image_type type;
   uint16_t width;
   uint16_t height;
   size_t size;
   uint8_t *bytes;
 } xpm_image_t;
  
 uint8_t *(xpm_load)(xpm_map_t map, enum xpm_image_type type, xpm_image_t *img);
  
 uint32_t(xpm_transparency_color)(enum xpm_image_type type);
  