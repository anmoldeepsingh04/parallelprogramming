#include <iostream>
#include <omp.h>

int main(){
    // #pragma omp parallel
    // {
    //     std::cout<<"Hello World!"<<std::endl;
    // }

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // all threads compete for std::cout so we have jumbled output
        std::cout<<"Hello World from thread ! "<< thread_id<<" / "<<num_threads<<std::endl;

        // using this makes sure that this instruction is executed by one thread completely, only then the next thread begins
        // #pragma omp critical
        // {
        //     std::cout<<"Hello World from "<< thread_id<<" of "<<num_threads<<std::endl;
        // }
    }
}