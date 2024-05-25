#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

int main(){
	pid_t pid=fork();
	if(pid<0){
		printf("Error\n");
	}
	else if(pid==0){
		this_thread::sleep_for(chrono::seconds(20));
		printf("This is the child process,pid=%d\n",getpid());
	}
	else{
		this_thread::sleep_for(chrono::seconds(3));
		printf("This is the father process,pid=%d\n",getpid());
	}
}
