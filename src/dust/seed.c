#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define str_length 16
#define password_length 32

char password[password_length + 1];

void seed(void){
    /*
    * 変数宣言
    */
    char str[str_length + 1];
    
    int i, j, k, rnd;
    char confirm[2];
    
    /*
    * 乱数の初期化
    */
    srand(clock());
  i=0;
  while(i<10000)
    i++;
    /*
    * 乱数生成とパスワードの生成
    */
    for(i = 0; i < str_length; i++) {
        for(j = 0; j < 2; j++) {
            k = i * 2 + j;
            do {
                rnd = rand();
                password[k] = str[i] + rnd;
            }while(!isalnum(password[k]));
        }
    }
    
    /*
    * NULL文字の挿入
    */
    password[password_length] = '\0';
    
    /*
    * パスワードの出力
    */
    printf("生成パスワード：%s",password);
    
return;
  
}
