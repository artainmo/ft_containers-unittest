#ifndef _MAIN_HPP
#define _MAIN_HPP

//Paths to your containers
#include "../ft_containers/List/list.hpp"
#include "../ft_containers/Vector/vector.hpp"
#include "../ft_containers/Map/map.hpp"
#include "../ft_containers/Stack/stack.hpp"
#include "../ft_containers/Queue/queue.hpp"

//Real containers
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <queue>

//External libs
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <csignal>
#include <fcntl.h>
#include <pthread.h>
#include <sstream>
#include <iomanip>
#include <cstring>

#define LIST_TOTAL_TESTS 162535.000000
#define MAP_TOTAL_TESTS 157184.000000
#define QUEUE_TOTAL_TESTS 9609.000000
#define STACK_TOTAL_TESTS 6351.000000
#define VECTOR_TOTAL_TESTS 130434.000000

extern unsigned int G_ERROR_LIMIT;
extern unsigned int G_STOP_AT_TEST;
extern unsigned int G_ERROR_COUNT;
extern unsigned int G_LINE;

extern int G_LIST;
extern int G_MAP;
extern int G_QUEUE;
extern int G_STACK;
extern int G_VECTOR;

template<typename T>
struct s_functions_ptr
{
  void (*function_pointer)();
  int num;
};

template<typename T>
struct s_functions_ptr1
{
  void (*function_pointer)(T &ob);
  int num;
};

template<typename T>
struct s_functions_ptr2
{
  void (*function_pointer)(T &ob, T &ob2);
  int num;
};

template<typename T, typename R>
struct test_args
{
  unsigned int containers_number;
  T *my_elems;
  R *real_elems;
  struct s_functions_ptr1<T> *my_func1;
  struct s_functions_ptr2<T> *my_func2;
  struct s_functions_ptr1<R> *real_func1;
  struct s_functions_ptr2<R> *real_func2;
  unsigned int functions1_number;
  unsigned int functions2_number;
  int thread_num1;
  int thread_num2;
};

void check_answer(std::ifstream &fd_r, std::ifstream &fd_r_r, std::ofstream &output_my, std::ofstream &output_real);
void feedback();
void cont();

std::string itoa(int num);

void segfault( int signum );
void sigabort( int signum );
void sigquit(int sig);

//Unittest functions
#include "src/list_tests.hpp"
#include "src/map_tests.hpp"
#include "src/queue_tests.hpp"
#include "src/stack_tests.hpp"
#include "src/vector_tests.hpp"

#include "src/tests.hpp"

#endif
