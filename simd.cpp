#include <iostream>
#include <vector>
#include <immintrin.h>

void saxpy(int a, std::vector<int> &b, std::vector<int> &c){
    for(int i = 0; i < c.size(); i++){
        c[i] = a * b[i] + c[i];
    }
}

void saxpy_intrinsics(int a, std::vector<float>& b, std::vector<float>& c, int n){
    int ub = n - n%8;
    __m256 b_regis, c_regis, temp;
    __m256 a_regis = _mm256_set1_ps(a);
    for(int i = 0; i < ub; i += 8){
        b_regis = _mm256_loadu_ps(&b[i]);
        c_regis = _mm256_loadu_ps(&c[i]);
        temp = _mm256_mul_ps(b_regis, a_regis);
        c_regis = _mm256_add_ps(c_regis, temp);
        _mm256_storeu_ps(&c[i], c_regis);
    }

    for(int i = ub; i < n; i++){
        c[i] = a*b[i] + c[i];
    }
    

}

int main(){
    std::vector<int> b = {1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4};
    std::vector<int> c = {1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1};
    int a = 2;
    saxpy(a, b, c);

    std::vector<float> b1 = {1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4, 1,2,3,4};
    std::vector<float> c1 = {1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1};
    int a1 = 2;

    saxpy_intrinsics(a1, b1, c1, c1.size());
    for(int i = 0; i < c.size(); i++){
        std::cout<<c[i]<<" ";
    }

    std::cout<<" "<<std::endl;

    for(int i = 0; i < c1.size(); i++){
        std::cout<<c1[i]<<" ";
    }

    std::cout<<" "<<std::endl;

    for(int i = 0; i < c1.size(); i++){
        std::cout<<c[i] - c1[i]<<" ";
    }

    
}