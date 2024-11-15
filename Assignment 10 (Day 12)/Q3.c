//Write a program to find the size of the pipe buffer.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int count = 0;

int main() {

    int ret, arr[2], s;
    char ch[1] = "X";
    ret = pipe(arr);
    
    if(ret < 0) {
        _exit(1);
        perror("pipe() failed");
    }
    
    ret = fork();
    if(ret == 0) { 
   	close(arr[0]); 
    	while(1){
        	write(arr[1], &ch, sizeof(ch));
        	count++;
        	printf("count : %d\n", count);
   	 }
    }
    wait(&s);

    return 0;
}
