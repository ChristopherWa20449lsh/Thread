#include<iostream>
#include<mutex>
#include<cmath>
#include<thread>
#include<chrono>
#include<future> // async库

using namespace std;

double cal(double a,double b){
	cout<< "Calculating......" << endl;
	double c=a*b;
	this_thread::sleep_for(chrono::seconds(3));
	cout<< "Success!!!!" << endl;
	while(true){
		// 明白了，top的TIME统计的是线程、进程使用CPU的时间，无法查看存在时间
		double temp=pow(sin(rand()),cos(rand()));
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	return c;
}

int main(){
	double a=1.2131;
	double b=21.12313;

	future<double> res=async(cal,a,b);

	this_thread::sleep_for(chrono::seconds(1));

	cout<< "Wait in line....."<< endl;
	cout<< "Try to get the cal result"<<endl;
	cout<< res.get() << endl; // get()方法只允许调用一次
	cout << "finished" << endl;
	return 0;
}
