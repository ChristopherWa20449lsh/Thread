#include<thread>
#include<iostream>
#include<chrono>

using namespace std;

void func(){
	int i=0;
	while(true);
}
void func2(){
	cout << "等待三秒" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "等待结束" << endl;
}

int main(){
	cout << "create threads" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	thread th(func);
	thread th2(func2);
	// 线程在上面就已经创建好了，下面只是调用
	cout << "threads created" << endl;
	th2.join();
	th.detach();
	while(true);
	return 0;
}
