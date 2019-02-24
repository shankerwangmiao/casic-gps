#include "casic.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define MAX_MSG_SIZE 4096

const char * getCmd(uint8_t class, uint8_t cmd){
  static char buf[256];
  char *pos = buf;
  if(class < CASIC_NUM_CLASSES && casic_classes[class]){
    pos += sprintf(pos, "%s-", casic_classes[class]);
    if(cmd < casic_commands_nums[class] && casic_commands[class][cmd]){
      pos += sprintf(pos, "%s", casic_commands[class][cmd]);
    }else{
      pos += sprintf(pos, "0x%02x", cmd);
    }
  }else{
    pos += sprintf(pos, "0x%02x-0x%02x", class, cmd);
  }
  return buf;
}

int main(int argc, char *argv[]){
  
  if(argc != 2){
    printf("Usage: %s serial port\n", argv[0]);
    exit(1);
  }
  FILE *serial = fopen(argv[1], "rb");
  
  while(!feof(serial)){
    int ch = fgetc(serial);
    if(ch != 0xba){
      continue;
    }
    ch = fgetc(serial);
    if(ch != 0xce){
      continue;
    }
    uint8_t buf[MAX_MSG_SIZE];
    fread(buf, 2, 1, serial);
    uint16_t payload_len = FROM_LE16(*(uint16_t *)buf);
    if(payload_len > MAX_MSG_SIZE - 6){
      continue;
    }
    fread(buf + 2, 2 + payload_len + 4, 1, serial);
    printf("%s: %d bytes\n", getCmd(buf[2], buf[3]), payload_len);
    for(int i = 0; i < payload_len; i++){
      printf("%02x", buf[i + 4]);
      if(i % 2 == 1){
        printf(" ");
      }
      if(i % 16 == 15 || i == payload_len - 1){
        printf("\n");
      }
    }
    int cksum = 0;
    for(int i = 0; i < payload_len + 4; i += 4){
      cksum += FROM_LE32(*(uint32_t *)(buf + i));
    }
    if(cksum != FROM_LE32(*(uint32_t *)(buf + 4 + payload_len))){
      printf("cksum: should 0x%08x, get 0x%08x\n", cksum, FROM_LE32(*(uint32_t *)(buf + 4 + payload_len)));
    }
  }
  
  fclose(serial);
  
  return 0;
}