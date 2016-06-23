#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
std::condition_variable cond_var;
std::mutex g_mutex, h_mutex, j_mutex;
template <class mutexType>
class uniqueLock{
private:
    mutexType& mtx;
public:
    uniqueLock(mutexType& _mtx){
        mtx = _mtx;
        mtx.lock();
    }
    uniqueLock(uniqueLock&& src): mtx(src.mtx&){}
    ~uniqueLock(void){
        mtx.unlock();
    } 
    void lock(void){
        mtx.lock();
    }
    void unlock(void){
        mtx.unlock();
    }
}
void f1(void){
    for (int i = 0; i < 100; i++) {
        std::cout << "aaaaa" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void f2(void) {
    for (int i = 0; i < 100; i++) {
        std::cout << "bbbbb" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void g1(void){
    int counter = 0;
    g_mutex.lock();
    for (int i = 0; i < 100; i++) {
        if(counter < 3) {
        	std::cout.flush();
            std::cout << i << "aaaaa" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            counter++;
        }
        else{
        	std::cout.flush();
            std::cout << i << "aaaaa" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            counter = 0;
            g_mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            g_mutex.lock();
        }
        if (i == 99){ 
            g_mutex.unlock(); 
        }
    }
}
void g2(void){
    int counter = 0;
    g_mutex.lock();
    for (int i = 0; i < 100; i++) {
        if(counter < 3) {
        	std::cout.flush();
            std::cout << i <<"bbbbb" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            counter++;
        }
        else{
        	std::cout.flush();
            std::cout << i << "bbbbb" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            counter = 0;
            g_mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            g_mutex.lock();

        }
        if (i == 99){
            g_mutex.unlock();
        }
    }
}
void h1(void) {
    uniqueLock<std::mutex> lk(h_mutex);
    cond_var.wait(lk);
    for (int i = 0; i < 100; i++) {
        std::cout << i << "aaaaa" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void h2(void) {
    for (int i = 0; i < 100; i++) {
        if (i == 50) {
            cond_var.notify_one();
        }
        std::cout << i << "bbbbb" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void j1(void) {

    for (int i = 0; i < 100; i++) {
        if (i >= 10) {
            j_mutex.lock();
        }
        std::cout << i << "aaaaa" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
void j2(void) {
    for (int i = 0; i < 100; i++) {
        if (i >= 10) {
            j_mutex.lock();
        }
        std::cout << i << "bbbbb" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
int main() {
    size_t key;
    std::cout << "Choose:\n0 - MT-NOSYNC\n1 - MT-SYNC\n2 - MT-WAIT\n3 - DEADLOCK-M" << std::endl;
    std::cin  >> key;
    std::cout << std::endl;
    switch (key){
    case 0:
        {
            std::cout << "MT-NOSYNC" << std::endl;
            std::thread thrf1(f1);
            std::thread thrf2(f2);
            thrf1.join();
            thrf2.join();
            break;
        }
    case 1:
        {
            std::cout << "MT-SYNC" << std::endl;
            std::thread thrg1(g1);
            std::thread thrg2(g2);
            thrg1.join();
            thrg2.join();
            break;
        }
    case 2:
        {
            std::cout << "MT-WAIT" << std::endl;
            std::thread thrh1(h1);
            std::thread thrh2(h2);
            thrh1.join();
            thrh2.join();
            break;       
        }
    case 3:    
        {
            std::cout << "DEADLOCK-M" << std::endl;
            std::thread thrj1(j1);
            std::thread thrj2(j2);
            thrj1.join();
            thrj2.join();
            break;       
        }
    }
    std::cout << "END OF PROGRAM";
    return 0;
}
