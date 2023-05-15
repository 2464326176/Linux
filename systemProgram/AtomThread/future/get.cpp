/*
 * @Author: yuhang.liu
 * @Date: 2021-07-08 08:40:50
 * @LastEditors: yuhang.liu
 * @LastEditTime: 2021-07-08 09:19:28
 * @Description: file content
 */
#include <exception>
#include <future>
#include <iostream>

int get_int() {
  std::cin.exceptions(std::ios::failbit);
  int x;
  std::cin >> x;
  return x;
}

int get_value() { return 120; }
int main() {
  /*std::future<int> fut0;
  fut0 = std::async(get_value); //move assigned

  std::future<int> fut = std::async(get_int);

  std::future<int> fut1 = std::async (get_value);
  std::shared_future<int> shfut = fut1.share();

  // shared futures can be accessed multiple times:
  std::cout << "value: " << shfut.get() << '\n';
  std::cout << "its double: " << shfut.get()*2 << '\n';


  std::cout << "please enter a integer value: ";
  try
  {
      int x = fut.get();
      std::cout << "you entered: " << x << "\n";
      std::cout << "value: " << fut0.get() << "\n";
  }
  catch (std::exception &)
  {
      std::cout << "[exception caught] \n";
  }*/

  std::future<int> bar, foo;
  foo = std::async(get_value);
  bar = std::move(foo);

  if (foo.valid()) {
    std::cout << "foo's value: " << foo.get() << "\n";
  } else {
    std::cout << "foo is not valid\n";
  }

  if (bar.valid()) {
    std::cout << "bar's value: " << bar.get() << "\n";
  } else {
    std::cout << "bar is not valid\n";
  }

  return 0;
}