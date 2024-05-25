#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
#include<shared_mutex>

using namespace std;

shared_mutex s_m;
string book="EMPTY";

void read(int i){
	shared_lock<shared_mutex> lock(s_m);
	this_thread::sleep_for(chrono::seconds(2));
	cout<< book << i << endl;
	// 共享锁会在超出锁作用域的时候自动释放
}

void write(){
	unique_lock<shared_mutex> lock(s_m);
	book="WUJIAYUAN's BEAUTY";
	this_thread::sleep_for(chrono::seconds(4));
}

int main(){
	thread thw1(write);
	thread thr1(read,1);
	thread thr2(read,2);
	thread thr3(read,3);

	thw1.detach();
	thr1.detach();
	thr2.detach();
	thr3.detach();

	while(true);
	return 0;
}
