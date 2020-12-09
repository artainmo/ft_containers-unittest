#ifndef STACK_TESTS_HPP
#define STACK_TESTS_HPP

#include "../main.hpp"

template<typename T, typename T2>
T *stack_container_object_creation1(unsigned int &lenght)
{
  T *my_elems = new T[6];
  lenght = 6;

  T l1; //Empty
  std::cout << "\033[30m" << "1 ";

  T2 li(10, 10);
  T l2(li); //Long same values
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  l2.push(1);
  std::cout << "\033[30m" << "2 ";

  T l3; // 4 values, same front and end
  l3.push(1);
  l3.push(4);
  l3.push(3);
  l3.push(1);
  std::cout << "\033[30m" << "3 ";

  T l4; //3 values
  l4.push(0);
  l4.push(3);
  l4.push(7);
  std::cout << "\033[30m" << "4 ";

  T l5; //2 values
  l5.push(5);
  l5.push(6);
  std::cout << "\033[30m" << "5 ";

  T l6; //1 value
  l6.push(7);
  std::cout << "\033[30m" << "6 ";

  my_elems[0] = l2;
  my_elems[1] = l3;
  my_elems[2] = l1;
  my_elems[3] = l5;
  my_elems[4] = l6;
  my_elems[5] = l4;

  return my_elems;
}

template<typename T>
void show_stack(T &s)
{
  while (!s.empty())
  {
    std::cout << s.top();
    s.pop(); //To iterate over whole stack you have to destoy it and start from end to start
  }
  std::cout << std::endl;
}

template<typename T>
void sget_size(T &ob) { std::cout << "~~ Size: "; std::cout << ob.size() << std::endl; }

template<typename T>
void saccess(T &l) //All the subtests indicated with ~~
{
  struct s_functions_ptr1<T> func[2] = {{sget_size<T>, 0}, {show_stack<T>, 1}};

  for (int i = 0; i < 2; i++)
  {
    pid_t pid = fork();

    if (pid == 0) //Child process
    {
      func[i].function_pointer(l);
      exit(0);
    }
    wait(NULL);
  }
}

template<typename T>
void sdefault_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Default constructor " << std::endl;
  T l;
  saccess<T>(l);
}

template<typename T>
void sempty(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Empty function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  saccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.empty() == false) //Returns false if not empty
    std::cout << "false" << std::endl;
  else
    std::cout << "true" << std::endl;
}

template<typename T>
void stop(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Top function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0)
    return ;
  saccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.top() = 52; //If this line causes compilation error review your code const problem
  saccess<T>(l);
}

template<typename T>
void spush(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Push function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0)
    return ;
  saccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.push(7);
  l.push(0);
  saccess<T>(l);
}

template<typename T>
void spop(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Pop function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  saccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() != 0) //Undefined bahavior segfault
  	l.pop();
  if (l.size() != 0) //Undefined bahavior segfault
  	l.pop();
  if (l.size() != 0) //Undefined bahavior random value
  	saccess<T>(l);
}

template<typename T>
void sequal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l == l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void snon_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Non-equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l != l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void ssmaller_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l < l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void ssmaller_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l <= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void sbigger_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l > l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void sbigger_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  saccess<T>(l);
  saccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l >= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
struct s_functions_ptr<T> *stack_basic_func(unsigned int &lenght)
{
  struct s_functions_ptr<T> func[1] = {{sdefault_constructor<T>, 1}};
  struct s_functions_ptr<T> *ret = new struct s_functions_ptr<T>[1];

  lenght = 1;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func[i];
  return ret;
}


template<typename T>
struct s_functions_ptr1<T> *stack_func1(unsigned int &lenght)
{
  struct s_functions_ptr1<T> func1[4] = {{sempty<T>, 1}, {stop<T>, 2}, {spush<T>, 3}, {spop<T>, 4}};
  struct s_functions_ptr1<T> *ret = new struct s_functions_ptr1<T>[4];

  lenght = 4;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func1[i];
  return ret;
}

template<typename T>
struct s_functions_ptr2<T> *stack_func2(unsigned int &lenght)
{
  struct s_functions_ptr2<T> func2[6] = {{sequal<T>, 5}, {snon_equal<T>, 6}, {ssmaller_than<T>, 7}, \
  {ssmaller_than_equal<T>, 8}, {sbigger_than<T>, 9}, {sbigger_than_equal<T>, 10}};
  struct s_functions_ptr2<T> *ret = new struct s_functions_ptr2<T>[6];

  lenght = 6;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func2[i];
  return ret;
}

#endif
