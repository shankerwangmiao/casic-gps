#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "casic.h"

#define MAX_CMD_SIZE 256
#define MAX_MSG_SIZE 4096

int main(){
  char str_class[MAX_CMD_SIZE];
  uint8_t buf[MAX_MSG_SIZE];
  uint8_t *cur_buf = buf;
  uint8_t class, cmd;
  
  int token = scanf("%20s", str_class);
  char *str_cmd = strchr(str_class, '-');
  if(token != 1 || !str_cmd){
    fprintf(stderr, "Wrong Instruction\n");
    return 1;
  }
  *(str_cmd ++) = '\0';
  class = CASIC_NUM_CLASSES;
  for(int i=0; i < CASIC_NUM_CLASSES; i++){
    if(casic_classes[i] && strcasecmp(casic_classes[i], str_class) == 0){
      class = i;
      break;
    }
  }
  if(class == CASIC_NUM_CLASSES){
    fprintf(stderr, "Wrong Class\n");
    return 1;
  }
  cmd = casic_commands_nums[class];
  for(int i = 0; i < casic_commands_nums[class]; i++){
    if(casic_commands[class][i] && strcasecmp(casic_commands[class][i], str_cmd) == 0){
      cmd = i;
      break;
    }
  }
  if(cmd == casic_commands_nums[class]){
    fprintf(stderr, "Wrong Command\n");
    return 1;
  }
  
  const uint16_t header = CASIC_HEADER;
  fwrite(&header, sizeof(header), 1, stdout);
  cur_buf += 2;
  *(cur_buf++) = class;
  *(cur_buf++) = cmd;
  int size = 0;
  int high_half = 1;
  while(size < MAX_CMD_SIZE - 8){
    int ch = getchar();
    if(ch == EOF){
      break;
    }
    int num = 0;
    if('a' <= ch && ch <= 'f'){
      num = ch - 'a' + 10;
    }else if('A' <= ch && ch <= 'F'){
      num = ch - 'A' + 10;
    }else if('0' <= ch && ch <= '9'){
      num = ch - '0';
    }else{
      continue;
    }
    if(high_half){
      *cur_buf = (num << 4);
    }else{
      *cur_buf |= (num & 0x0f);
      cur_buf += 1;
      size += 1;
    }
    high_half = !high_half;
  }
  if(size % 4 != 0){
    cur_buf += 4 - size % 4;
    size += 4 - size % 4;
  }
  *(uint16_t *)(buf) = TO_LE16((uint16_t)size);
  fwrite(buf, size + 4, 1, stdout);
  uint32_t chksum = 0;
  for(int i=0; i < size + 4; i += 4){
    chksum += FROM_LE32(*(uint32_t *)(buf + i));
  }
  chksum = TO_LE32(chksum);
  fwrite(&chksum, sizeof(chksum), 1, stdout);
  fflush(stdout);
  return 0;
}