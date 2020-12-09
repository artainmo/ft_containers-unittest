#ifndef QUEUE_TESTS_HPP
#define QUEUE_TESTS_HPP

#include "../main.hpp"

template<typename T, typename T2>
T *queue_container_object_creation1(unsigned int &lenght)
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
void qget_back(T &ob) { if (ob.size() == 0) return ; std::cout << "~~ Back: "; std::cout << ob.back() << std::endl; }

template<typename T>
void qget_front(T &ob) { if (ob.size() == 0) return ; std::cout << "~~ Front: "; std::cout << ob.front() << std::endl; }

template<typename T>
void qget_size(T &ob) { std::cout << "~~ Size: "; std::cout << ob.size() << std::endl; }

template<typename T>
void show_queue(T &s)
{
  while (!s.empty())
  {
    std::cout << s.front();
    s.pop(); //To iterate over whole queue you have to destroy it, reading it from start to end
  }
  std::cout << std::endl;
}

template<typename T>
void qaccess(T &l) //All the subtests indicated with ~~
{
  struct s_functions_ptr1<T> func[4] = {{qget_size<T>, 0}, {qget_front<T>, 1}, {qget_back<T>, 2}, {show_queue<T>, 3}};

  for (int i = 0; i < 4; i++)
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
void qdefault_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Default constructor " << std::endl;
  T l;
  qaccess<T>(l);
}

template<typename T>
void qempty(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Empty function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  qaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.empty() == false) //Returns false if not empty
    std::cout << "false" << std::endl;
  else
    std::cout << "true" << std::endl;
}

template<typename T>
void qfront(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  qaccess<T>(l);
  if (l.size() == 0) //Linux undefined
	return ;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.front() = l.back(); //If this line causes compilation error review your code const problem
  qaccess<T>(l);
}

template<typename T>
void qback(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0)//Linux undeined
	  return ;
  qaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.back() = l.front(); //If this line causes compilation error review your code const problem
  qaccess<T>(l);
}

template<typename T>
void qpush(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Push_front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  qaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.push(7);
  l.push(0);
  qaccess<T>(l);
}

template<typename T>
void qpop(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Pop_front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  qaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() != 0) //Undefined bahavior segfault
    l.pop();
  if (l.size() != 0) //Undefined bahavior segfault
    l.pop();
  if (l.size() != 0) //Undefined bahavior random value
    qaccess<T>(l);
}

template<typename T>
void qequal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l == l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void qnon_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Non-equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l != l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void qsmaller_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l < l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void qsmaller_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l <= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void qbigger_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l > l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void qbigger_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  qaccess<T>(l);
  qaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l >= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
struct s_functions_ptr<T> *queue_basic_func(unsigned int &lenght)
{
  struct s_functions_ptr<T> func[1] = {{qdefault_constructor<T>, 1}};
  struct s_functions_ptr<T> *ret = new struct s_functions_ptr<T>[1];

  lenght = 1;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func[i];
  return ret;
}


template<typename T>
struct s_functions_ptr1<T> *queue_func1(unsigned int &lenght)
{
  struct s_functions_ptr1<T> func1[5] = {{qempty<T>, 1}, {qfront<T>, 2}, {qback<T>, 3}, {qpush<T>, 4}, {qpop<T>, 5}};
  struct s_functions_ptr1<T> *ret = new struct s_functions_ptr1<T>[5];

  lenght = 5;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func1[i];
  return ret;
}

template<typename T>
struct s_functions_ptr2<T> *queue_func2(unsigned int &lenght)
{
  struct s_functions_ptr2<T> func2[6] = {{qequal<T>, 6}, {qnon_equal<T>, 7}, {qsmaller_than<T>, 8}, \
  {qsmaller_than_equal<T>, 9}, {qbigger_than<T>, 10}, {qbigger_than_equal<T>, 11}};
  struct s_functions_ptr2<T> *ret = new struct s_functions_ptr2<T>[6];

  lenght = 6;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func2[i];
  return ret;
}

#endif
