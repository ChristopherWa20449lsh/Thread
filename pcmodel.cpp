#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>

using namespace std;

// 缓冲区数据类型
struct CacheData
{
    int id;
    string data;
}
// 缓冲区队列
queue<CacheData> Q;

const int Max_CacheData_Length=10;

mutex m;

condition_variable condConsumer;
condition_variable condProducer;

int ID=1;

// 消费者动作
void ConsumerActor()
{
    // 加锁
    unique_lock<mutex> lockerConsumer(m);
    cout << "线程 [" << this_thread::get_id() << "] 获得了锁" << endl;

    while(Q.empty())
    {
        cout << "Q empty, so consumer sleep" << endl;
        cout << "[" << this_thread::get_id() << "] no longer hold the lock" << endl;
        condConsumer.wait(lockerConsume);
        cout << "[" << this_thread::get_id() << "] regain the lock" << endl;
    }

    CacheData temp=Q.front();
    cout << "ID: " << temp.id << ", Data: " << temp.data << endl;
    Q.pop();
    condProducer.notify_one();
    cout<< "[" << this_thread::get_id() << "] release the lock" << endl;

}

void ProducerActor()
{
    unique_lock<mutex> lockerProducer(m);
    cout << "[" << this_thread::get_id() << "] obtain the lock" << endl;
    while(Q.size()>Max_CacheData_Length)
    {
        cout << "Q full, so producer sleep" << endl;
        cout << "[" << this_thread::get_id() << "] no longer hold the lock" << endl;
        condProducer.wait(lockerProducer);
        cout << "[" << this_thread::get_id() << "] regain the lock" << endl;
    }
    CacheData temp;
    temp.id=ID++;
    temp.data="******";
    Q.push(temp);
    condConsumer.notify_one();
    cout << "[" << this_thread::get_id() << "] release the lock" << endl;
}

void ConsumerTask()
{
    while(1)
    {
        ConsumerActor();
    }
}

void ProducerTask()
{
    while(1)
    {
        ProducerActor();
    }
}

void Dispatch(int ConsumerNum,int ProducerNum)
{
    int i=0;
    vector<thread> thsC;
    vector<thread> thsP;
    for(i=0;i<ConsumerNum;i++)
        thsC.push_back(thread(ConsumerTask));
    for(i=0;i<ProducerNum;i++)
        thsP.push_back(thread(ProducerTask));
    for(i=0;i<ConsumerNum;i++)
        if(thsC[i].joinable())
            thsC[i].join();
    for(i=0;i<ProducerNum;i++)
        if(thsP[i].joinable())
            thsP[j].join();
}

int main()
{
    Dispatch(1,5);
    return 0;
}
