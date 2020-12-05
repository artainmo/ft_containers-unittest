#include "main.hpp"

unsigned int G_ERROR_LIMIT = 1;
//MAX 200 or potential computer crash risk

unsigned int G_STOP_AT_TEST = 0;
//Set to zero to deactivate
//Set to desired number to go until a certain test, independent of error limit

int G_LIST = 0;
int G_MAP = 0;
int G_QUEUE = 0;
int G_STACK = 0;
int G_VECTOR = 0;

template<typename T, typename R, typename T1, typename T2>
void call_tests(std::string type, std::string cont, T* (*function_pointer)(unsigned int &lenght), R* (*function_pointer2)(unsigned int &lenght),
      struct s_functions_ptr1<T> *(function_pointer3)(unsigned int &lenght), struct s_functions_ptr2<T> *(function_pointer4)(unsigned int &lenght),
          struct s_functions_ptr1<R> *(function_pointer5)(unsigned int &lenght), struct s_functions_ptr2<R> *(function_pointer6)(unsigned int &lenght))
{
  struct test_args<T, R> *args = new struct test_args<T, R>;

  std::cout << "\033[1m\033[33m" << "!!Starting tests for " << cont << "<" << type << "> container...!!" << std::endl;
  std::cout << "\033[1m\033[30m" << "\nContainer object creation you:" << std::endl;
  args->my_elems = function_pointer(args->containers_number);
  std::cout << "\033[1m\033[30m" << "End of container object creation\n" << std::endl;
  std::cout << "\033[1m\033[30m" << "Container object creation real:" << std::endl;
  args->real_elems = function_pointer2(args->containers_number);
  std::cout << "\033[1m\033[30m" << "End of container object creation\n" << std::endl;
  args->my_func1 = function_pointer3(args->functions1_number);
  args->my_func2 = function_pointer4(args->functions2_number);
  args->real_func1 = function_pointer5(args->functions1_number);
  args->real_func2 = function_pointer6(args->functions2_number);
  test<T, R, T1, T2>(args);
  std::cout << "\033[1m\033[33m" << "!!End " << cont << "<"<< type << "> container tests!!" << std::endl;
  delete args;
}

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 3)
  {
    std::cerr << "Choose between list, map, queue, stack and vector as first argument" << std::endl;
    return 0;
  }
  else if (G_ERROR_LIMIT == 0)
  {
    std::cerr << "ERROR: error limit cannot be zero" << std::endl;
    return 1;
  }

  std::remove("output/my");
  std::remove("output/real");
  std::remove("output/tmp_my");
  std::remove("output/tmp_real");


  signal(SIGQUIT, sigquit);
  signal(SIGSEGV, segfault);
  signal(SIGABRT, sigabort);
  if (std::strcmp("list", argv[1]) == 0)
  {
    G_LIST = 1;
    std::cout << "\033[1m\033[33m" << "~~~~!!Starting tests for list container...!!~~~~" << std::endl;
    basis_tests<ft::list<int>, std::list<int>, int>(list_basic_func<ft::list<int>, int>, list_basic_func<std::list<int>, int>);

    call_tests<ft::list<int>, std::list<int>, int, int>("int", "list", list_container_object_creation1<ft::list<int> >, list_container_object_creation1<std::list<int> >,
          list_func1<ft::list<int>, int>, list_func2<ft::list<int>, int>, list_func1<std::list<int>, int>, list_func2<std::list<int>, int>);
    cont();
    call_tests<ft::list<char>, std::list<char>, char, char>("char", "list", list_container_object_creation1<ft::list<char> >, list_container_object_creation1<std::list<char> >,
          list_func1<ft::list<char>, char>, list_func2<ft::list<char>, char>, list_func1<std::list<char>, char>, list_func2<std::list<char>, char>);
    feedback();
    std::cout << "\033[1m\033[33m" << "~~~~!!End tests for list container!!~~~~" << std::endl;
  }
  if (std::strcmp("map", argv[1]) == 0)
  {
    G_MAP = 1;
    std::cout << "\033[1m\033[33m" << "~~~~!!Starting tests for map container...!!~~~~" << std::endl;
    basis_tests<ft::map<int, int>, std::map<int, int>, int>(map_basic_func<ft::map<int, int>, int, int>, map_basic_func<std::map<int, int>, int, int>);

    call_tests<ft::map<int, int>, std::map<int, int>, int, int>("int", "map", map_container_object_creation1<ft::map<int, int> >, map_container_object_creation1<std::map<int, int> >,
          map_func1<ft::map<int, int>, int, int>, map_func2<ft::map<int, int>, int, int>, map_func1<std::map<int, int>, int, int>, map_func2<std::map<int, int>, int, int>);
    cont();
    call_tests<ft::map<char, char>, std::map<char, char>, char, char>("char", "map", map_container_object_creation1<ft::map<char, char> >, map_container_object_creation1<std::map<char, char> >,
          map_func1<ft::map<char, char>, char, char>, map_func2<ft::map<char, char>, char, char>, map_func1<std::map<char, char>, char, char>, map_func2<std::map<char, char>, char, char>);
    feedback();
    std::cout << "\033[1m\033[33m" << "~~~~!!End tests for map container!!~~~~" << std::endl;
  }
  if (std::strcmp("queue", argv[1]) == 0)
  {
    G_QUEUE = 1;
    std::cout << "\033[1m\033[33m" << "~~~~!!Starting tests for queue container...!!~~~~" << std::endl;
    basis_tests<ft::queue<int>, std::queue<int>, int>(queue_basic_func<ft::queue<int> >, queue_basic_func<std::queue<int> >);

    call_tests<ft::queue<int>, std::queue<int>, int, int>("int", "queue", queue_container_object_creation1<ft::queue<int>, std::deque<int> >, queue_container_object_creation1<std::queue<int>, std::deque<int> >,
          queue_func1<ft::queue<int> >, queue_func2<ft::queue<int> >, queue_func1<std::queue<int> >, queue_func2<std::queue<int> >);
    cont();
    call_tests<ft::queue<char, std::list<char> >, std::queue<char, std::list<char> >, char, char>("char", "queue", queue_container_object_creation1<ft::queue<char, std::list<char> >, std::list<char> >,
          queue_container_object_creation1<std::queue<char, std::list<char> >, std::list<char> >, queue_func1<ft::queue<char, std::list<char> > >, queue_func2<ft::queue<char, std::list<char> > >,
                queue_func1<std::queue<char, std::list<char> > >, queue_func2<std::queue<char, std::list<char> > >);
    feedback();
    std::cout << "\033[1m\033[33m" << "~~~~!!End tests for queue container!!~~~~" << std::endl;
  }
  if (std::strcmp("stack", argv[1]) == 0)
  {
    G_STACK = 1;
    std::cout << "\033[1m\033[33m" << "~~~~!!Starting tests for stack container...!!~~~~" << std::endl;
    basis_tests<ft::stack<int>, std::stack<int>, int>(stack_basic_func<ft::stack<int> >, stack_basic_func<std::stack<int> >);

    call_tests<ft::stack<int>, std::stack<int>, int, int>("int", "stack", stack_container_object_creation1<ft::stack<int>, std::deque<int> >, stack_container_object_creation1<std::stack<int>, std::deque<int> >,
          stack_func1<ft::stack<int> >, stack_func2<ft::stack<int> >, stack_func1<std::stack<int> >, stack_func2<std::stack<int> >);
    cont();
    call_tests<ft::stack<char, std::list<char> >, std::stack<char, std::list<char> >, char, char>("char", "stack", stack_container_object_creation1<ft::stack<char, std::list<char> >, std::list<char> >,
          stack_container_object_creation1<std::stack<char, std::list<char> >, std::list<char> >, stack_func1<ft::stack<char, std::list<char> > >, stack_func2<ft::stack<char, std::list<char> > >,
                stack_func1<std::stack<char, std::list<char> > >, stack_func2<std::stack<char, std::list<char> > >);
    feedback();
    std::cout << "\033[1m\033[33m" << "~~~~!!End tests for stack container!!~~~~" << std::endl;
  }
  if (std::strcmp("vector", argv[1]) == 0)
  {
    G_VECTOR = 1;
    std::cout << "\033[1m\033[33m" << "~~~~!!Starting tests for vector container...!!~~~~" << std::endl;
    basis_tests<ft::vector<int>, std::vector<int>, int>(vector_basic_func<ft::vector<int>, int>, vector_basic_func<std::vector<int>, int>);

    call_tests<ft::vector<int>, std::vector<int>, int, int>("int", "vector", vector_container_object_creation1<ft::vector<int> >, vector_container_object_creation1<std::vector<int> >,
          vector_func1<ft::vector<int>, int>, vector_func2<ft::vector<int>, int>, vector_func1<std::vector<int>, int>, vector_func2<std::vector<int>, int>);
    cont();
    call_tests<ft::vector<char>, std::vector<char>, char, char>("char", "vector", vector_container_object_creation1<ft::vector<char> >, vector_container_object_creation1<std::vector<char> >,
          vector_func1<ft::vector<char>, char>, vector_func2<ft::vector<char>, char>, vector_func1<std::vector<char>, char>, vector_func2<std::vector<char>, char>);
    feedback();
    std::cout << "\033[1m\033[33m" << "~~~~!!End tests for vector container!!~~~~" << std::endl;
  }


  std::remove("output/tmp_my");
  std::remove("output/tmp_real");
}
