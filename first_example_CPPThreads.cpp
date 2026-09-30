#include <iostream>
#include <thread>

void kernel(int* arg){
    ++(++(*arg));
}

int main(){
    int arg = 1;
    std::thread t1(kernel, &arg);
    t1.join();
    std::cout<<arg<<std::endl;
    return 0;
}