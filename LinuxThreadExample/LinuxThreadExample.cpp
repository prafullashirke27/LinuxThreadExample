//#include <cstdio>
//
//int main()
//{
//    printf("hello from %s!\n", "ConsoleApplication1");
//    return 0;
//}

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd()
{
    for (; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, []() { return (count % 2 == 1); });
        std::cout << "From Odd:    " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }

}

void PrintEven()
{
    for (; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, []() { return (count % 2 == 0); });
        std::cout << "From Even: " << count << std::endl;
        count++;
        locker.unlock();
        cond.notify_all();
    }
}

int main()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}