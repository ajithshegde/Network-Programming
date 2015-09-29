#include "unp.h"

int main(){
char in_str[100];
for( ; ;){
scanf("%s",in_str);
printf("%s\n",in_str);
write(pfd[1], in_str,strlen(in_str)+1);
}
return 0;
}
