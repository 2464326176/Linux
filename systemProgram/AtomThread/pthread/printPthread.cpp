#include <iostream>
#include <thread>

int main() {
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " AtomicsAndThreading threads are supported.\n";
}
