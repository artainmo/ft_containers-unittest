#ifndef LIST_TESTS_HPP
#define LIST_TESTS_HPP

#include "../main.hpp"

template<typename T>
T *list_container_object_creation1(unsigned int &lenght)
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
bool remove_if_test(T x)
{
  if (x == 8)
    return true;
  return false;
}

template<typename T>
bool unique_test(T x, T follow)
{
  if (x > follow)
    return false;
  return true;
}

template<typename T>
bool merge_test(T x, T x2)
{
  if (x < x2)
    return true;
  return false;
}

template<typename T>
bool sort_test(T x, T x2)
{
  if (x > x2)
    return true;
  return false;
}

template<typename T>
void lget_size(T &ob) { std::cout << "~~ Size: "; std::cout << ob.size() << std::endl; }

template<typename T>
void lget_back(T &ob) { std::cout << "~~ Back: "; std::cout << ob.back() << std::endl; }

template<typename T>
void lget_front(T &ob) { std::cout << "~~ Front: "; std::cout << ob.front() << std::endl; }

template<typename T>
void show_list_begin(T &l)
{
  typename T::iterator it = l.begin(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with begin iterator: ";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << *it;
    it++;
  }
  std::cout << std::endl;
}

template<typename T>
void show_list_rbegin(T &l)
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
void show_list_end(T &l)
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
void show_list_rend(T &l)
{
  typename T::reverse_iterator it = l.rend(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with rend iterator: ";
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
void laccess(T &l) //All the subtests indicated with ~~
{
  struct s_functions_ptr1<T> func[7] = {{lget_size<T>, 0}, {lget_front<T>, 0}, {lget_back<T>, 0}, {show_list_begin<T>, 0}, {show_list_rbegin<T>, 0}, {show_list_end<T>, 0}, {show_list_rend<T>, 0}};

  for (int i = 0; i < 7; i++)
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
void ldefault_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Default constructor " << std::endl;
  T l;
  laccess<T>(l);
}

template<typename T>
void lfill_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Fill constructor " << std::endl;
  T l((unsigned int)10, 5);
  laccess<T>(l);
}

template<typename T>
void lspecial_fill_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Special Fill constructor " << std::endl;
  T l((unsigned int)0, 4);
  laccess<T>(l);
}

template<typename T>
void lrange_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range constructor " << std::endl;
  T tmp((unsigned int)10, 5);
  typename T::iterator i = tmp.begin();
  ++i;
  ++i;
  ++i;
  T l(i, tmp.end());
  laccess<T>(l);
}

template<typename T, typename T2>
void lcopy_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Copy constructor " << std::endl;
  T tmp((unsigned int)10, 5);
  T l(tmp);
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  T2 k = 0;
  l.front() = k;
  tmp.back() = k;
  laccess<T>(l);
  laccess<T>(tmp);
}

template<typename T, typename T2>
void lassignation_operator(T &l, T &l2)
{
  T l3;
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Assignation operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l3 = l = l2; //Test if proper return and not just pointer used
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  T2 k = 0;
  l.front() = k;
  l2.back() = k;
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lempty(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Empty function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.empty() == false) //Returns false if not empty
    std::cout << "false" << std::endl;
  else
    std::cout << "true" << std::endl;
}

template<typename T>
void lfront(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.front() = l.back(); //If this line causes compilation error review your code const problem
  laccess<T>(l);
}

template<typename T>
void lback(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.back() = l.front(); //If this line causes compilation error review your code const problem
  laccess<T>(l);
}

template<typename T>
void lfill_assign2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Fill assign function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign((unsigned int)0, 0); //If you do not cast it to an unsigned int, it will enter the other assign function with two int parameters
  laccess<T>(l);
}

template<typename T>
void lfill_assign(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Fill assign function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign((unsigned int)12, 7); //If you do not cast it to an unsigned int, it will enter the other assign function with two int parameters
  laccess<T>(l);
}

template<typename T>
void lrange_assign2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range assign function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l2.begin();
  ++i;
  ++i;
  typename T::iterator i2 = l2.end();
  --i2;
  --i2;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << "Iterator 2: " << *i2 << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign(i, i2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lrange_assign(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range assign function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.assign(l2.begin(), l2.end());
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lpush_front(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Push_front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.push_front(7);
  laccess<T>(l);
}

template<typename T>
void lpop_front(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Pop_front function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined behavior sigabort
    return ;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.pop_front();
  laccess<T>(l);
}

template<typename T>
void lpush_back(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Push_back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.push_back(9);
  laccess<T>(l);
}

template<typename T>
void lpop_back(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Pop_back function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined behavior sigabort
    return ;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.pop_back();
  laccess<T>(l);
}

template<typename T>
void linsert_single_element3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(l.end(), 3)) << std::endl;
  laccess<T>(l);
}

template<typename T>
void linsert_single_element2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(l.begin(), 0)) << std::endl;
  laccess<T>(l);
}

template<typename T>
void linsert_single_element(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  typename T::iterator i = l.end();
  --i;
  --i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.insert(i, 3)) << std::endl;
  laccess<T>(l);
}

template<typename T>
void linsert_fill3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(l.end(), (unsigned int)3, 4);
  laccess<T>(l);
}

template<typename T>
void linsert_fill2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(l.begin(), (unsigned int)0, 4);
  laccess<T>(l);
}

template<typename T>
void linsert_fill(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert fill " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  typename T::iterator i = l.end();
  --i;
  --i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.insert(i,  (unsigned int)3, 4);
  laccess<T>(l);
}

template<typename T>
void linsert_range3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
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
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void linsert_range2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(l.end(), l2.begin(), l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void linsert_range(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(i, l2.begin(), l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lerase_single_element2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase single element 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  if (l.size() == 0) //Undefined behavior sigabort
    return ;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.erase(l.begin())) << std::endl;
  laccess<T>(l);
}

template<typename T>
void lerase_single_element(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase single element " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  if (l.size() < 3) //Out of scope iterator undefined behavior, sigabort
    return ;
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  typename T::iterator check = i;
  ++check;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (check != l.end()) //Return value is undefined when iterator points on back, because goes out of scope and returns random value
    std::cout << "return: " << *(l.erase(i)) << std::endl;
  else
    l.erase(i);
  laccess<T>(l);
}

template<typename T>
void lerase_range2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  if (l.size() == 1) //Undefined bahavior sigabort
    return ;
  typename T::iterator m = l.begin();
  ++m;
  ++m;
  typename T::iterator k = l.end();
  --k;
  --k;
  std::cout << "Iterator 1: " << *m << std::endl;
  std::cout << "Iterator 2: " << *k << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() > 3) //Undefined behavior if unordered
    std::cout << "return: " << *(l.erase(m, k)) << std::endl;
  else
    std::cout << "return: " << *(l.erase(k, m)) << std::endl;
  laccess<T>(l);
}

template<typename T>
void lerase_range(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << *(l.erase(l.begin(), l.end())) << std::endl;
  laccess<T>(l);
}

template<typename T>
void lswap_member_function(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Swap member function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.swap(l2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lresize_range_bigger(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize range bigger " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.resize(l.size() + 1, 9);
  laccess<T>(l);
}

template<typename T>
void lresize_range_smaller(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize range smaller " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;

  if (l.size() < 3)
    l.resize(0, 9);
  else
    l.resize(l.size() - 3, 9);
  laccess<T>(l);
}

template<typename T>
void lresize_bigger(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize bigger " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.resize(65); //Size_t minimum upper limit is 65535
  laccess<T>(l);
}

template<typename T>
void lresize_smaller(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Resize smaller " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l.size() < 3) //Size_t does not take negative numbers
    l.resize(0);
  else
    l.resize(l.size() - 3);
  laccess<T>(l);
}

template<typename T>
void lclear(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Clear function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.clear();
  laccess<T>(l);
}

template<typename T>
void lsplice_list3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice entire list 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  std::cout << "Iterator 1: " << *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(i, l2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_list2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice entire list 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(l.end(), l2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_list(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice entire list " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(l.begin(), l2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_single_element4(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice single element 4" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l2.begin();
  ++i;
  l.splice(l.begin(), l2, l.begin());
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_single_element3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice single element 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l2.begin();
  ++i;
  l.splice(i, l2, i);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_single_element2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice single element 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  if (l2.size() == 0) // !!REAL COMPLETE BUG!!
    return ;
  typename T::iterator i = l.end();
  --i;
  --i;
  --i;
  typename T::iterator k = l2.end();
  --k;
  --k;
  --k;
  std::cout << "~~~Iterator 1: "<< *i<< std::endl;
  std::cout << "~~~Iterator 2: "<< *k<< std::endl;
  if (l2.size() == 2) //Undefined behavior out of range iterator
    return ;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(i, l2, k);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_single_element(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice single element " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  if (l2.size() == 0)// !!== 0 REAL COMPLETE BUG!!
    return ;
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  typename T::iterator k = l2.begin();
  ++k;
  ++k;
  std::cout << "~~~Iterator 1: "<< *i<< std::endl;
  std::cout << "~~~Iterator 2: "<< *k<< std::endl;
  if (l2.size() == 2) //Undefined behavior out of range iterator
    return ;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(i, l2, k);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_range3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice range 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l2.end();
  --i;
  typename T::iterator k = l2.begin();
  ++k;
  std::cout << "~~~Iterator 1: "<< *k<< std::endl;
  std::cout << "~~~Iterator 2: "<< *i<< std::endl;
  if (l2.size() == 1) //Undefined behavior
    return ;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(l.begin(), l2, k, i);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_range2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l.end();
  --i;
  --i;
  --i;
  std::cout << "~~~Iterator 1: "<< *i << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(i, l2, l2.begin(), l2.end());
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsplice_range(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Splice range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  std::cout << "~~~Iterator 1: "<< *i<< std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.splice(i, l2, l2.begin(), l2.end());
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lremove(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Remove function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.remove(5);
  laccess<T>(l);
}

template<typename T, typename T2>
void lremove_if(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Remove_if function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.remove_if(remove_if_test<T2>);
  laccess<T>(l);
  laccess<T>(l);
}

template<typename T>
void lunique(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Unique function default " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.unique();
  laccess<T>(l);
}

template<typename T, typename T2>
void lunique_if(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Unique function function parameter " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.unique(unique_test<T2>);
  laccess<T>(l);
}

template<typename T>
void lmerge(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Merge function default " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  l.sort(); //Both containers should already be ordered or undefined behavior
  l2.sort();
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.merge(l2);
  l.merge(l); //Test if function successfully negates merging itself
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T, typename T2>
void lmerge_if(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Merge function function parameter " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  l.sort(); //Both containers should already be ordered or undefined behavior
  l2.sort();
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.merge(l2, merge_test<T2>);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lsort(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Sort function default" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.sort();
  laccess<T>(l);
}

template<typename T, typename T2>
void lsort_if(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Sort function function argument" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.sort(sort_test<T2>);
  laccess<T>(l);
}

template<typename T>
void lreverse(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Reverse function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.reverse();
  laccess<T>(l);
}

template<typename T>
void lswap_non_member_function(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Swap non-member function overload " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  swap(l, l2);
  laccess<T>(l);
  laccess<T>(l2);
}

template<typename T>
void lequal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l == l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void lnon_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Non-equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l != l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void lsmaller_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l < l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void lsmaller_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Smaller than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l <= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void lbigger_than(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l > l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void lbigger_than_equal(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Bigger than or equal operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  laccess<T>(l);
  laccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l >= l2)
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;
}

template<typename T>
void literator_tests3()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l.begin();
  typename T::reverse_iterator r = l.rbegin();

  while(i != l.end())
    std::cout << *i++;
  std::cout << std::endl;

  while(r != l.rend())
    std::cout << *r++;
  std::cout << std::endl;

  i = l.begin();
  r = l.rbegin();

  while(i != l.end())
    std::cout << *++i;
  std::cout << std::endl;

  while(r != l.rend())
    std::cout << *++r;
  std::cout << std::endl;

  i = l.end();
  r = l.rend();

  while(i != l.begin())
    std::cout << *--i;
  std::cout << std::endl;

  while(r != l.rbegin())
    std::cout << *--r;
  std::cout << std::endl;

  i = l.end();
  r = l.rend();

  while(i != l.begin())
    std::cout << *i--;
  std::cout << std::endl;

  while(r != l.rbegin())
    std::cout << *r--;
  std::cout << std::endl;
}

template<typename T>
void literator_tests2()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l.begin();
  typename T::iterator k = l.end();

  std::cout << *i << std::endl;
  std::cout << *k << std::endl;
  --i;
  ++k;
  std::cout << *i << std::endl;
  std::cout << *k << std::endl;
  --i;
  ++k;
  std::cout << *i << std::endl;
  std::cout << *k << std::endl;
}

template<typename T, typename T2>
void literator_tests1()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  laccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = l.begin();
  ++i;
  typename T::iterator k = l.end();
  --k;
  T2 test;

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

  test = *i;
  test = 10; //If this causes compilation error review your code const problem
  std::cout << *i << std::endl;

  *k = 10; //If this causes compilation error review your code const problem
  std::cout << *k << std::endl;
}

template<typename T>
void lmember_types()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Member types " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::value_type q;
  (void)q;
  typename T::reference w = q;
  (void)w;
  typename T::const_reference e = 0;
  (void)e;
  typename T::pointer r;
  (void)r;
  typename T::const_pointer t;
  (void)t;
  typename T::difference_type y;
  (void)y;
  typename T::size_type u;
  (void)u;
}

template<typename T, typename T2>
struct s_functions_ptr<T> *list_basic_func(unsigned int &lenght)
{
  struct s_functions_ptr<T> func[9] = {{ldefault_constructor<T>, 1}, {lfill_constructor<T>, 2}, {lspecial_fill_constructor<T>, 3}, \
  {lrange_constructor<T>, 4}, {lcopy_constructor<T, T2>, 5}, {literator_tests1<T, T2>, 6}, {literator_tests2<T>, 7},  {literator_tests3<T>, 8}, {lmember_types<T>, 9}};
  struct s_functions_ptr<T> *ret = new struct s_functions_ptr<T>[9];

  lenght = 9;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func[i];
  return ret;
}


template<typename T, typename T2>
struct s_functions_ptr1<T> *list_func1(unsigned int &lenght)
{
  struct s_functions_ptr1<T> func1[31] = {{lempty<T>, 1}, {lfront<T>, 2}, {lback<T>, 3}, {lfill_assign<T>, 4}, {lfill_assign2<T>, 5}, {lpush_front<T>, 6}, \
  {lpop_front<T>, 7}, {lpush_back<T>, 8}, {lpop_back<T>, 9}, {linsert_single_element<T>, 10}, {linsert_single_element2<T>, 11}, {linsert_single_element3<T>, 12}, \
  {linsert_fill<T>, 13}, {linsert_fill2<T>, 14}, {linsert_fill3<T>, 15}, {lerase_single_element<T>, 16}, {lerase_single_element2<T>, 17}, \
  {lerase_range<T>, 18}, {lerase_range2<T>, 19}, {lresize_bigger<T>, 20}, {lresize_smaller<T>, 21}, {lresize_range_bigger<T>, 22}, {lresize_range_smaller<T>, 23}, \
  {lclear<T>, 24}, {lremove<T>, 25}, {lremove_if<T, T2>, 26}, {lunique<T>, 27}, {lunique_if<T, T2>, 28}, {lsort<T>, 29}, {lsort_if<T, T2>, 30}, {lreverse<T>, 31}};
  struct s_functions_ptr1<T> *ret = new struct s_functions_ptr1<T>[31];

  lenght = 31;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func1[i];
  return ret;
}

template<typename T, typename T2>
struct s_functions_ptr2<T> *list_func2(unsigned int &lenght)
{
  struct s_functions_ptr2<T> func2[26] = {{lassignation_operator<T, T2>, 32}, {lrange_assign<T>, 33}, {lrange_assign2<T>, 34}, {linsert_range<T>, 35}, {linsert_range2<T>, 36}, \
  {linsert_range3<T>, 37}, {lswap_member_function<T>, 38}, {lsplice_list<T>, 39}, {lsplice_list2<T>, 40}, {lsplice_list3<T>, 41}, \
  {lsplice_single_element<T>, 42}, {lsplice_single_element2<T>, 43}, {lsplice_single_element3<T>, 44}, {lsplice_single_element4<T>, 45}, {lsplice_range<T>, 46}, {lsplice_range2<T>, 47}, \
  {lsplice_range3<T>, 48}, {lmerge<T>, 49}, {lmerge_if<T, T2>, 50}, {lswap_non_member_function<T>, 51}, {lequal<T>, 52}, {lnon_equal<T>, 53}, \
  {lsmaller_than<T>, 54}, {lsmaller_than_equal<T>, 55}, {lbigger_than<T>, 56}, {lbigger_than_equal<T>, 57}};
  struct s_functions_ptr2<T> *ret = new struct s_functions_ptr2<T>[26];

  lenght = 26;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func2[i];
  return ret;
}

#endif
