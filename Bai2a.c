#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    char buf[1024];
    printf("Nhap vao Chuoi ki tu\n");
    fgets(buf, sizeof(buf), stdin);
    unsigned int len=strlen(buf)-1;
    
    if(len<1024) 
    buf[len]=0;
    
    for(int i = 0; buf[i]; i++){
    buf[i] = tolower(buf[i]);
}

}
    

