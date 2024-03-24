#include "main.h"
#include "restaurant.cpp"

int main(int argc, char* argv[]) {
    string fileName = "test.txt";
    simulate(fileName);

    return 0;
}
//g++ -std=c++11 main.cpp -o main