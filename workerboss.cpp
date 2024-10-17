#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;  // 2 is prime.
    if (num % 2 == 0) return false; // Exclude all even numbers greater than 2

    for (int i = 3; i < num; i += 2) { // Check all odd numbers up to num
        if (num % i == 0) {
            return false; // num is divisible by i, so it's not prime
        }
    }

    return true; // num is prime if no divisors were found
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <start> <end>\n";    //takes the variables from the cmd line
        return 1;
    }

    int start = std::atoi(argv[1]);         //translates to int
    int end   = std::atoi(argv[2]);         //translates to int

    
    std::string fileName = "primes_" + std::to_string(start) + "_" + std::to_string(end) + ".txt";

    std::ofstream outFile(fileName);

    if (!outFile) {
        std::cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    outFile << "Prime numbers between " << start << " and " << end << ":\n";
    for (int num = start; num <= end; ++num) {
        if (isPrime(num)) {
            outFile << num << " ";
        }
    }
    outFile << std::endl;

    outFile.close();
    std::cout << "Done!!!\n";

    return 0;
}


