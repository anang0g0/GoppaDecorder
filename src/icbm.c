#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "sha3.h"

static void byte_to_hex(uint8_t b, char s[23]) {
    unsigned i=1;
    s[0] = s[1] = '0';
    s[2] = '\0';
    while(b) {
        unsigned t = b & 0x0f;
        if( t < 10 ) {
            s[i] = '0' + t;
        } else {
            s[i] = 'a' + t - 10;
        }
        i--;
        b >>= 4;
    }
}


int main(){
  const uint8_t *hash;
  sha3_context c;
  int image_size=512,i;
  char buf[8192];

  scanf("%s",buf);
  sha3_Init256(&c);
  sha3_Update(&c, buf, strlen(buf));
  hash = sha3_Finalize(&c);
  for(i=0; i<image_size/8; i++) {
    char s[3];
    byte_to_hex(hash[i],s);
    printf("%s", s);
  }
    printf("\n");

    return 0;
}
