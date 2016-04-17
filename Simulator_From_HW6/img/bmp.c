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
      colors[i][j]=color;
      if(i<50 && j<50) {if(color>0x1000) printf("#");
	else printf(" ");}
    }if(i<50)
    printf("\n");
  }/*
  close(f);
  FILE* fw;
  fw=fopen("../wall.c","w");
  fprintf(fw,"#include\"wall.h\"\n#include<stdint.h>\n");
  fprintf(fw,"uint16_t wallimg[100][100] = {\n");
  for(i=0;i<100;i++) {
    fprintf(fw,"{0x%x",colors[i][0]);
    for(j=1;j<100;j++) {
      fprintf(fw,",0x%x",colors[i][j]);
    }
    if(i==99) fprintf(fw,"}\n");
    else fprintf(fw,"},\n");
  }
  fprintf(fw,"};\n");
  fclose(fw);*/
}
