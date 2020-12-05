#ifndef VECTOR_TESTS_HPP
#define VECTOR_TESTS_HPP

#include "../main.hpp"

template<typename T>
T *vector_container_object_creation1(unsigned int &lenght)
{
  T *my_elems = new T[8];
  lenght = 8;

  T l1; //Empty
  std::cout << "\033[30m" << "1 ";

  T l2((unsigned int)10, 5); //Long same values
  std::cout << "\033[30m" << "2 ";

  T l3; // 4 values, same front and end
  l3.push_back(1);
  l3.push_back(4);
  l3.push_back(3);
  l3.push_back(1);
  std::cout << "\033[30m" << "3 ";

  T l4; //3 values
  l4.push_back(0);
  l4.push_back(3);
  l4.push_back(7);
  std::cout << "\033[30m" << "4 ";

  T l5; //2 values
  l5.push_back(5);
  l5.push_back(6);
  std::cout << "\033[30m" << "5 ";

  T l6; //1 value
  l6.push_back(7);
  std::cout << "\033[30m" << "6 ";

  T l7; //Small to big 5 values
  l7.push_back(0);
  l7.push_back(1);
  l7.push_back(2);
  l7.push_back(3);
  l7.push_back(4);
  l7.push_back(5);
  std::cout << "\033[30m" << "7 ";

  T l8; //Big to small 5 values
  l8.push_back(5);
  l8.push_back(4);
  l8.push_back(3);
  l8.push_back(2);
  l8.push_back(1);
  l8.push_back(0);
  std::cout << "\033[30m" << "8 ";

  my_elems[0] = l7;
  my_elems[1] = l8;
  my_elems[2] = l3;
  my_elems[3] = l4;
  my_elems[4] = l5;
  my_elems[5] = l6;
  my_elems[6] = l1;
  my_elems[7] = l2;

  return my_elems;
}

template<typename T>
void vget_size(T &ob) { std::cout << "~~ Size: "; std::cout << ob.size() << std::endl; }

template<typename T> //Instead of showing the capacity (which can be different than real one capacity), compare size and capacity, if capcity is equal to or smaller than size, return true else false
void vget_capacity(T &ob) { std::cout << "~~ Capacity: "; if (ob.size() <= ob.capacity()) std::cout << "OK" << std::endl; else std::cout << "NOK" << std::endl; }

template<typename T>
void vget_back(T &ob) { if (ob.size() == 0) return ; std::cout << "~~ Back: "; std::cout << ob.back() << std::endl; } //Undefined behavior if empty container

template<typename T>
void vget_front(T &ob) { if (ob.size() == 0) return ; std::cout << "~~ Front: "; std::cout << ob.front() << std::endl; }

template<typename T>
void show_vector_begin(T &l)
{
  typename T::iterator it = l.begin(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with begin iterator: ";
  for (unsigned int i = 0; i < l.size(); i++)
    std::cout << it[i];
  std::cout << std::endl;
}

template<typename T>
void show_vector_rbegin(T &l)
{
  typename T::reverse_iterator it = l.rbegin(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with rbegin iterator: ";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << *it;
    ++it;
  }
  std::cout << std::endl;
}

template<typename T>
void show_vector_end(T &l)
{
  typename T::iterator it = l.end(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with end iterator: ";
  --it;
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << *it;
    --it;
  }
  std::cout << std::endl;
}

template<typename T>
void show_vector_rend(T &l)
{
  typename T::reverse_iterator it = l.rend(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with rend iterator: ";
  if (l.size() == 0) //Undefined behavior
    return ;
  --it;
  std::cout << *it;
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << *it;
    --it;
  }
  std::cout << std::endl;
}

template<typename T>
void show_vector_operator(T &l)
{
  std::cout << "~~ Show with [] operator: ";
  for (unsigned int i = 0; i < l.size(); i++)
    std::cout << l[i];
  std::cout << std::endl;
}

template<typename T>
void show_vector_at(T &l)
{
  std::cout << "~~ Show with at function: ";
  for (unsigned int i = 0; i < l.size(); i++)
    std::cout << l.at(i);
  std::cout << std::endl;
}

template<typename T>
void vaccess(T &l) //All the subtests indicated with ~~
{
  struct s_functions_ptr1<T> func[10] = {{vget_size<T>, 0}, {vget_capacity<T>, 0}, {vget_front<T>, 0}, \
  {vget_back<T>, 0}, {show_vector_begin<T>, 0}, {show_vector_rbegin<T>, 0}, {show_vector_end<T>, 0}, {show_vector_rend<T>, 0}, \
  {show_vector_operator<T>, 0}, {show_vector_at<T>, 0}};

  for (int i = 0; i < 10; i++)
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
void vdefault_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Default constructor " << std::endl;
  T l;
  vaccess<T>(l);
}

template<typename T>
void vfill_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Fill constructor " << std::endl;
  T l((unsigned int)10, 5); //Indicate unsigned int is necessary otherwise it will use the templated inputiterator (int, int) function
  vaccess<T>(l);
}

template<typename T>
void vspecial_fill_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Special Fill constructor " << std::endl;
  T l((unsigned int)0, 4);
  vaccess<T>(l);
}

template<typename T>
void vrange_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range constructor " << std::endl;
  T tmp((unsigned int)10, 5);
  typename T::iterator i = tmp.begin();
  ++i;
  ++i;
  ++i;
  T l(i, tmp.end());
  vaccess<T>(l);
}

template<typename T, typename T2>
void vcopy_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Copy constructor " << std::endl;
  T tmp((unsigned int)10, 5);
  T l(tmp);
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  T2 k = 0;
  l.front() = k;
  tmp.back() = k;
  vaccess<T>(l);
  vaccess<T>(tmp);
}

template<typename T, typename T2>
void vassignation_operator(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Assignation operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l = l2;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  if (l2.size() == 0) //Undefined behavior segfault
    return ;
  T2 k = 0;
  l.front() = k;
  l2.back() = k;
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vresize4(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize 4" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.resize(l.size());
  vaccess<T>(l);
}

template<typename T>
void vresize3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.resize(l.size() + 20, 9);
  vaccess<T>(l);
}

template<typename T>
void vresize2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.resize(l.size() + 1);
  vaccess<T>(l);
}

template<typename T>
void vresize(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize 1" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() < 3)
    l.resize(0, 9);
  else
    l.resize(l.size() - 3, 9);
  vaccess<T>(l);
}

template<typename T>
void vreserve3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Reserve 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  size_t tmp = l.capacity() + 10;
  l.reserve(tmp);
  vaccess<T>(l);
  l.resize(tmp); //Should not sigabort if prior reserve occured correctly
}

template<typename T>
void vreserve2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Reserve 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.reserve(l.size());
  vaccess<T>(l);
}

template<typename T>
void vreserve(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Reserve 1" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() >= 5) //Undefined behavior sigabort
    l.reserve(l.size() - 5);
  else
    l.reserve(0);
  vaccess<T>(l);
}

template<typename T>
void vempty(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Empty function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.empty() == false) //Returns false if not empty
    std::cout << "false" << std::endl;
  else
    std::cout << "true" << std::endl;
}

template<typename T>
void voperator(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Operator [] function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() == 0) //Undefined segfault
    return ;
  l[0] = l.back(); //If this line causes compilation error review your code const problem
  vaccess<T>(l);
}

template<typename T>
void vat(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "At function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() == 0) //Undefined segfault
    return ;
  l.at(0) = l.back();
  vaccess<T>(l);
}

template<typename T>
void vfront(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined segfault
    return ;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.front() = l.back(); //If this line causes compilation error review your code const problem
  vaccess<T>(l);
}

template<typename T>
void vback(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined segfault
    return ;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.back() = l.front(); //If this line causes compilation error review your code const problem
  vaccess<T>(l);
}

template<typename T>
void vfill_assign(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Fill assign function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign((unsigned int)12, 7); //If you do not cast it to an unsigned int, it will enter the other assign function with two int parameters
  vaccess<T>(l);
}

template<typename T>
void vrange_assign2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range assign function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  if (l2.size() < 3) //Out of range iterator undefined behavior
    return ;
  typename T::iterator i = l2.begin();
  ++i;
  ++i;
  typename T::iterator i2 = l2.end();
  --i2;
  --i2;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << "Iterator 2: " << *i2 << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l2.size() > 3)
    l.assign(i, i2);
  else
    l.assign(i2, i);
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vrange_assign(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range assign function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign(l2.begin(), l2.end());
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vpush_back(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Push_back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.push_back(9);
  vaccess<T>(l);
}

template<typename T>
void vpop_back(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Pop_back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined bahavior capacity NOK
    return ;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.pop_back();
  vaccess<T>(l);
}

template<typename T>
void vinsert_single_element3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(l.end(), 3)) << std::endl;
  vaccess<T>(l);
}

template<typename T>
void vinsert_single_element2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(l.begin(), 0)) << std::endl;
  vaccess<T>(l);
}

template<typename T>
void vinsert_single_element(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  if (l.size() < 2) //Out of range undefined behavior random values
    return ;
  typename T::iterator i = l.end();
  --i;
  --i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(i, 3)) << std::endl;
  vaccess<T>(l);
}

template<typename T>
void vinsert_fill3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(l.end(), (unsigned int)3, 4);
  vaccess<T>(l);
}

template<typename T>
void vinsert_fill2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(l.begin(), (unsigned int)0, 4);
  vaccess<T>(l);
}

template<typename T>
void vinsert_fill(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  if (l.size() < 2) //Out of range undefined behavior random values
    return ;
  typename T::iterator i = l.end();
  --i;
  --i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(i,  (unsigned int)3, 4);
  vaccess<T>(l);
}

template<typename T>
void vinsert_range3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  if (l2.size() < 3) //Out of range iterator undefined behavior
    return ;
  typename T::iterator m = l2.end();
  --m;
  --m;
  --m;
  typename T::iterator k = l2.begin();
  ++k;
  ++k;
  std::cout << "Iterator 1: " << *m << std::endl;
  std::cout << "Iterator 2: " << *k << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l2.size() > 4) //Undefined behavior if k comes after m
    l.template insert<typename T::iterator >(l.begin(), k, m); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  else
    l.template insert<typename T::iterator >(l.begin(), m, k);
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vinsert_range2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(l.end(), l2.begin(), l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vinsert_range(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  if (l.size() < 2) //Out of range iterator random value and capacity NOK
    return ;
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  if (l.size() != 2) //Out of range iterator random value
    std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(i, l2.begin(), l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void verase_single_element2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase single element 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() > 1) //Return out of range random value iterator
    std::cout << "return: " << *(l.erase(l.begin())) << std::endl;
  else if (l.size() == 1) //SEGFAULT when erasing empty
    l.erase(l.begin());
  vaccess<T>(l);
}

template<typename T>
void verase_single_element(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase single element " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  if (l.size() < 3) //Out of range iterator undefined behavior
    return ;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() > 3) //Out of range iterator return random value
    std::cout << "return: " << *(l.erase(i)) << std::endl;
  else if (l.size() == 3)
    l.erase(i);
  vaccess<T>(l);
}

template<typename T>
void verase_range2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  typename T::iterator m = l.begin();
  ++m;
  ++m;
  typename T::iterator k = l.end();
  --k;
  --k;
  if (l.size() < 3) //Undefined behavior out of range iterator
    return ;
  std::cout << "Iterator 1: " << *m << std::endl;
  std::cout << "Iterator 2: " << *k << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() < 4) //Good order iterator or undefined behavior
    std::cout << "return: " << *(l.erase(k, m)) << std::endl;
  else
    std::cout << "return: " << *(l.erase(m, k)) << std::endl;
  vaccess<T>(l);
}

template<typename T>
void verase_range(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.erase(l.begin(), l.end()); //DOn not show return because on random mem
  vaccess<T>(l);
}

template<typename T>
void vswap_member_function(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Swap member function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.swap(l2);
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vclear(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Clear function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.clear();
  vaccess<T>(l);
}

template<typename T>
void vswap_non_member_function(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Swap non-member function overload " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  swap(l, l2);
  vaccess<T>(l);
  vaccess<T>(l2);
}

template<typename T>
void vequal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l == l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void vnon_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Non-equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l != l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void vsmaller_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l < l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void vsmaller_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l <= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void vbigger_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l > l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void vbigger_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  vaccess<T>(l);
  vaccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l >= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void viterator_tests2()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i1 = l.begin();
  typename T::iterator k1 = l.end();

  i1 += 2;
  std::cout << *i1 << std::endl;
  k1 -= 2;
  std::cout << *k1 << std::endl;
  typename T::iterator i2 = i1 + 1;
  std::cout << *i1 << std::endl;
  std::cout << *i2 << std::endl;
  typename T::iterator k2 = k1 - 1;
  std::cout << *k1 << std::endl;
  std::cout << *k2 << std::endl;
}

template<typename T, typename T2>
void viterator_tests1()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  vaccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l.begin();
  ++i;
  typename T::iterator k = l.end();
  --k;

  if (i == i)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  if (i == k)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  if (i != i)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  if (i != k)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  if (i > k)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  if (i < k)
    std::cout << "YES" << std::endl;
  else
      std::cout << "NO" << std::endl;

  *i = 10;
  std::cout << *i << std::endl;

  *k = 10; //If this causes compilation error review your code const problem
  std::cout << *k << std::endl;
}

template<typename T, typename T2>
struct s_functions_ptr<T> *vector_basic_func(unsigned int &lenght)
{
  struct s_functions_ptr<T> func[7] = {{vdefault_constructor<T>, 1}, {vfill_constructor<T>, 2}, {vspecial_fill_constructor<T>, 3}, \
  {vrange_constructor<T>, 4}, {vcopy_constructor<T, T2>, 5}, {viterator_tests1<T, T2>, 6}, {viterator_tests2<T>, 7}};
  struct s_functions_ptr<T> *ret = new struct s_functions_ptr<T>[7];

  lenght = 7;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func[i];
  return ret;
}


template<typename T, typename T2>
struct s_functions_ptr1<T> *vector_func1(unsigned int &lenght)
{
  struct s_functions_ptr1<T> func1[26] = {{vresize<T>, 1}, {vresize2<T>, 2}, {vresize3<T>, 3}, {vresize4<T>, 4}, {vreserve<T>, 5}, {vreserve2<T>, 6}, {vreserve3<T>, 7}, \
  {vempty<T>, 8}, {voperator<T>, 9}, {vat<T>, 10}, {vfront<T>, 11}, {vback<T>, 12}, {vfill_assign<T>, 13}, \
  {vpush_back<T>, 14}, {vpop_back<T>, 15}, {vinsert_single_element<T>, 16}, {vinsert_single_element2<T>, 17}, {vinsert_single_element3<T>, 18}, \
  {vinsert_fill<T>, 19}, {vinsert_fill2<T>, 20}, {vinsert_fill3<T>, 21}, {verase_single_element<T>, 22}, {verase_single_element2<T>, 23}, \
  {verase_range<T>, 24}, {verase_range2<T>, 25}, {vclear<T>, 26}};
  struct s_functions_ptr1<T> *ret = new struct s_functions_ptr1<T>[26];

  lenght = 26;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func1[i];
  return ret;
}

template<typename T, typename T2>
struct s_functions_ptr2<T> *vector_func2(unsigned int &lenght)
{
  struct s_functions_ptr2<T> func2[14] = {{vassignation_operator<T, T2>, 28}, {vrange_assign<T>, 29}, {vrange_assign2<T>, 30}, {vinsert_range<T>, 31}, \
  {vinsert_range2<T>, 32}, {vinsert_range3<T>, 33}, {vswap_member_function<T>, 34}, {vswap_non_member_function<T>, 35}, {vequal<T>, 36}, {vnon_equal<T>, 37}, \
  {vsmaller_than<T>, 38}, {vsmaller_than_equal<T>, 39}, {vbigger_than<T>, 40}, {vbigger_than_equal<T>, 41}};
  struct s_functions_ptr2<T> *ret = new struct s_functions_ptr2<T>[14];

  lenght = 14;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func2[i];
  return ret;
}

#endif
