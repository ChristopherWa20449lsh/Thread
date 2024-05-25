#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
#include<vector>
#include<shared_mutex>

using namespace std;

shared_mutex s_m; // 这里是初始化一个对象
string book="EMPTY";

void read(int i){
	shared_lock<shared_mutex> lock(s_m);
	// this_thread::sleep_for(chrono::seconds(2));
	cout<< book << i << endl;
	// 共享锁会在超出锁作用域的时候自动释放
}

void write(){
	unique_lock<shared_mutex> lock(s_m);
	book="WUJIAYUAN's BEAUTY";
	// this_thread::sleep_for(chrono::seconds(4));
}

int main(){
	vector<thread> threads;

	threads.emplace_back(write);

	for(int i=1;i<=3;i++){
		threads.emplace_back(read,i);
	}

	// join和detach的区别在于主线程是否需要阻塞
	// 之前理解错了，对于线程本身而言，join和detach都是并发调度
	for(auto &th:threads){
		th.join();
	}

	cout<< "如果这句话出现在输出末尾，证明主线程阻塞，是join调用子线程的方法" << endl;

	while(true);
	return 0;
}
