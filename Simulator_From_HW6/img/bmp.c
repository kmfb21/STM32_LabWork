#include <fcntl.h> 
#include <stdio.h> 
#include "bmp.h"
struct bmpfile_magic magic; 
struct bmpfile_header header; 
BITMAPINFOHEADER info;
main(int argc, char *argv[]) {
  int f;
  if ((f = open(argv[1], O_RDONLY)) == -1) {
    perror("problem opening file");
    return 1; 
  }
  read(f, (void *) &magic, 2);
  printf("Magic %c%c\n", magic.magic[0], magic.magic[1]); 
  read(f, (void *) &header, sizeof(header));
  printf("file size %d offset %d\n", header.filesz, header.bmp_offset);
  read(f, (void *) &info, sizeof(info));
  printf("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp); 
  struct bmppixel pix;
  uint16_t color;
  int i,j;
  uint16_t colors[info.height][info.width];
  for(i=0;i<info.height;i++) {
    for(j=0;j<info.width;j++) {
      read(f, (void *) &pix, sizeof(pix));
      //printf("%d %d %d", pix.b, pix.g, pix.r);
      color=((pix.r>>3)<<11)|((pix.g>>2)<<5)|(pix.b>>3);
      if(color>0x1000) printf("#");
      else printf(" ");
      colors[i][j]=color;
    }
    printf("\n");
  }
  close(f);
  FILE* fw;
  fw=fopen("../tank.c","w");
  fprintf(fw,"#include\"tank.h\"\n#include<stdint.h>\n");
  fprintf(fw,"uint16_t tankimg[32][32] = {\n");
  for(i=0;i<info.height;i++) {
    fprintf(fw,"{0x%x",colors[i][0]);
    for(j=1;j<info.width;j++) {
      fprintf(fw,",0x%x",colors[i][j]);
    }
    if(i==info.height-1) fprintf(fw,"}\n");
    else fprintf(fw,"},\n");
  }
  fprintf(fw,"};\n");
  fclose(fw);
}
