#ifndef MAP_TESTS_HPP
#define MAP_TESTS_HPP

#include "../main.hpp"

template<typename T>
T *map_container_object_creation1(unsigned int &lenght)
{
  T *my_elems = new T[7];
  lenght = 7;

  T l1; //Empty
  std::cout << "\033[30m" << "1 ";

  T l2; //Long same values
  l2[0] = 0;
  l2[1] = 1;
  l2[2] = 2;
  l2[3] = 3;
  l2[4] = 4;
  l2[5] = 5;
  l2[6] = 6;
  l2[7] = 7;
  l2[8] = 8;
  l2[9] = 9;
  l2[10] = 10;
  std::cout << "\033[30m" << "2 ";

  T l3; // 4 values, same front and end
  l3[0] = 8;
  l3[3] = 4;
  l3[5] = 9;
  l3[7] = 3;
  std::cout << "\033[30m" << "3 ";

  T l4; //3 values
  l4[1] = 4;
  l4[2] = 4;
  l4[3] = 9;
  std::cout << "\033[30m" << "4 ";

  T l5; //2 values
  l5[2] = 0;
  l5[8] = 0;
  std::cout << "\033[30m" << "5 ";

  T l6; //1 value
  l6[5] = 9;
  std::cout << "\033[30m" << "6 ";

  T l7; //Random
  l7[0] = 8;
  l7[1] = 4;
  l7[4] = 7;
  l7[6] = 3;
  l7[9] = 8;
  std::cout << "\033[30m" << "7 ";

  my_elems[0] = l7;
  my_elems[1] = l2;
  my_elems[2] = l3;
  my_elems[3] = l4;
  my_elems[4] = l5;
  my_elems[5] = l6;
  my_elems[6] = l1;

  return my_elems;
}

template<typename T>
void mget_size(T &ob) { std::cout << "~~ Size: "; std::cout << ob.size() << std::endl; }

template<typename T>
void show_map_begin(T &l)
{
  typename T::iterator it = l.begin(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with begin iterator: \n";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << it->first << "\t" << it->second << std::endl;
    ++it;
  }
  std::cout << std::endl;
}

template<typename T>
void show_map_rbegin(T &l)
{
  typename T::reverse_iterator it = l.rbegin(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with rbegin iterator: \n";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    std::cout << it->first << "\t" << it->second << std::endl;
    ++it;
  }
  std::cout << std::endl;
}

template<typename T>
void show_map_end(T &l)
{
  typename T::iterator it = l.end(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with end iterator: \n";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    --it;
    std::cout << it->first << "\t" << it->second << std::endl;
  }
  std::cout << std::endl;
}

template<typename T>
void show_map_rend(T &l)
{
  typename T::reverse_iterator it = l.rend(); //Typename to indicate no ambiguity by telling compiler following is a type, is necessary because object creation depends on template parameter

  std::cout << "~~ Show with rend iterator: \n";
  for (unsigned int i = 0; i < l.size(); i++)
  {
    --it;
    std::cout << it->first << "\t" << it->second << std::endl;
  }
  std::cout << std::endl;
}

template<typename T>
void maccess(T &l) //All the subtests indicated with ~~
{
  struct s_functions_ptr1<T> func[5] = {{mget_size<T>, 0}, {show_map_begin<T>, 0}, {show_map_rbegin<T>, 0}, {show_map_end<T>, 0}, {show_map_rend<T>, 0}};

  for (int i = 0; i < 5; i++)
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
void mdefault_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Default constructor " << std::endl;
  T m;
  maccess<T>(m);
}

template<typename T, typename T1, typename T2>
void mrange_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Range constructor " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  T m;
  m.insert(std::pair<T1, T2>(1, 4));
  m.insert(std::pair<T1, T2>(2, 3));
  m.insert(std::pair<T1, T2>(3, 6));
  m.insert(std::pair<T1, T2>(4, 2));
  m.insert(std::pair<T1, T2>(5, 5));
  m.insert(std::pair<T1, T2>(6, 5));
  m.insert(std::pair<T1, T2>(7, 1));
  typename T::iterator i = m.begin();
  typename T::iterator i2 = m.end();
  --i2;
  ++i;
  ++i;
  ++i;
  ++i;
  maccess<T>(m);
  if (i != m.end())
    std::cout << "Iterator 1: " << i->first << "\t" << i->second << std::endl;
  if (i2 != m.end())
    std::cout << "Iterator 2: " << i2->first << "\t" << i2->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  T m2(i, i2);
  maccess<T>(m);
  maccess<T>(m2);
}

template<typename T, typename T1, typename T2>
void mcopy_constructor()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Copy constructor " << std::endl;
  T m;
  m.insert(std::pair<T1, T2>(1, 4));
  m.insert(std::pair<T1, T2>(2, 3));
  m.insert(std::pair<T1, T2>(3, 6));
  m.insert(std::pair<T1, T2>(4, 2));
  m.insert(std::pair<T1, T2>(5, 5));
  m.insert(std::pair<T1, T2>(6, 5));
  m.insert(std::pair<T1, T2>(7, 1));
  T m1(m);
  maccess<T>(m);
  maccess<T>(m1);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  T2 k = 0;
  m[0] = k;
  m1[5] = k;
  maccess<T>(m);
  maccess<T>(m1);
}

template<typename T>
void massignation_operator(T &m, T &m2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Assignation operator " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(m);
  maccess<T>(m2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  m = m2;
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Deep copy test: " << std::endl;
  m[0] = 0;
  m2[5] = 0;
  maccess<T>(m);
  maccess<T>(m2);
}

template<typename T>
void mempty(T &m)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Empty function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (m.empty() == false) //Returns false if not empty
    std::cout << "false" << std::endl;
  else
    std::cout << "true" << std::endl;
}

template<typename T>
void melement_access2(T &m)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Element access 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  m[1] = 3;
  std::cout << "1" << std::endl;
  m[1] = 9; //Not possible two times same key, but possible to reset key value
  std::cout << "2" << std::endl;
  m[5] = 4;
  std::cout << "3" << std::endl;
  m[3] = 5;
  std::cout << "4" << std::endl;
  m[0] = 2;
  std::cout << "5" << std::endl;
  m[10] = 6;
  maccess<T>(m);
}

template<typename T>
void melement_access(T &m)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Element access" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << m[0] << std::endl;
  std::cout << m[1] << std::endl;
  std::cout << m[5] << std::endl;
  std::cout << m[3] << std::endl;
  std::cout << m[10] << std::endl;
}

template<typename T, typename T1, typename T2>
void minsert_single_element3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result:" << std::endl;
  std::pair<typename T::iterator, bool> p = l.insert(std::pair<T1, T2>(8, 9));
  if (p.first != l.end())
    std::cout << "return: " << p.first->first << "\t" << p.first->second << "\t" << p.second << std::endl;
  maccess<T>(l);
}

template<typename T, typename T1, typename T2>
void minsert_single_element2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::pair<typename T::iterator, bool> p = l.insert(std::pair<T1, T2>(0, 1));
  std::cout << "return: " << p.first->first << "\t" << p.first->second << "\t" << p.second << std::endl;
  maccess<T>(l);
}

template<typename T, typename T1, typename T2>
void minsert_single_element(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert single element function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::pair<typename T::iterator, bool> p = l.insert(std::pair<T1, T2>(2, 3));
  std::cout << "return: " << p.first->first << "\t" << p.first->second << "\t" << p.second << std::endl;
  maccess<T>(l);
}

template<typename T, typename T1, typename T2>
void minsert_hint3(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert hint 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result:" << std::endl;
  typename T::iterator p = l.insert(l.end(), std::pair<T1, T2>(8, 9));
  std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  maccess<T>(l);
}

template<typename T, typename T1, typename T2>
void minsert_hint2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert hint 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container:" << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator p = l.insert(l.begin(), std::pair<T1, T2>(0, 1));
  std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  maccess<T>(l);
}

template<typename T, typename T1, typename T2>
void minsert_hint(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert hint" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator p = l.insert(l.end(), std::pair<T1, T2>(2, 3));
  std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  maccess<T>(l);
}

template<typename T>
void minsert_range3(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 3" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  maccess<T>(l2);
  if (l2.size() == 0) //Undefined behavior inifinite loop iterator out of range
    return ;
  typename T::iterator m = l2.end();
  --m;
  --m;
  if (l2.size() > 2) //Out of range iterator random value
    --m;
  typename T::iterator k = l2.begin();
  ++k;
  ++k;
  if (m != l2.end())
    std::cout << "Iterator 1: " << m->first << "\t" << m->second << std::endl;
  if (k != l2.end())
    std::cout << "Iterator 2: " << k->first << "\t" << k->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  if (l2.size() > 4) //Undefined behavior if k comes after m
    l.template insert<typename T::iterator >(k, m); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  else
    l.template insert<typename T::iterator >(m, k);
  maccess<T>(l);
  maccess<T>(l2);
}

template<typename T>
void minsert_range2(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  maccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(l2.begin(), l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  maccess<T>(l);
  maccess<T>(l2);
}

template<typename T>
void minsert_range(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Insert range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  maccess<T>(l2);
  if (l2.size() == 0) //Out of range undefined behavior
    return ;
  typename T::iterator i = l2.begin();
  ++i;
  ++i;
  if (i != l2.end())
    std::cout << "Iterator 1: " << i->first << "\t" << i->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.template insert<typename T::iterator >(i, l2.end()); //When the name of a member template specialization appears after . or -> in a postfix-expression, or after nested-name-specifier in a qualified-id, and the postfix-expression or qualified-id explicitly depends on a template-parameter, the member template name must be prefixed by the keyword template. Otherwise the name is assumed to name a non-template.
  maccess<T>(l);
  maccess<T>(l2);
}

template<typename T>
void merase_iterator_based2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase iterator based 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  typename T::iterator i = l.begin();
  ++i;
  ++i;
  if (i == l.end()) //Trying to erase the end() segfaults
    return ;
  std::cout << "Iterator 1: " << i->first << "\t" << i->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.erase(i);
  maccess<T>(l);
}

template<typename T>
void merase_iterator_based(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase iterator based" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.erase(l.begin());
  maccess<T>(l);
}

template<typename T>
void merase_key_based(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase key element based" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << "return: " << l.erase(0) << std::endl;
  std::cout << "return: " << l.erase(2) << std::endl;
  std::cout << "return: " << l.erase(8) << std::endl;
  std::cout << "return: " << l.erase(10) << std::endl;
  std::cout << "return: " << l.erase(3) << std::endl;
  std::cout << "return: " << l.erase(1) << std::endl;
  maccess<T>(l);
}

template<typename T>
void merase_range2(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  typename T::iterator m = l.begin();
  ++m;
  ++m;
  typename T::iterator k = l.end();
  --k;
  --k;
  if (m != l.end())
    std::cout << "Iterator 1: " << m->first << "\t" << m->second << std::endl;
  if (k != l.end())
    std::cout << "Iterator 2: " << k->first << "\t" << k->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.erase(m, k);
  maccess<T>(l);
}

template<typename T>
void merase_range(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Erase range " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.erase(l.begin(), l.end());
  maccess<T>(l);
}

template<typename T>
void mswap_member_function(T &l, T &l2)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Swap member function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  maccess<T>(l2);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.swap(l2);
  maccess<T>(l);
  maccess<T>(l2);
}

template<typename T>
void mclear(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Clear function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  l.clear();
  maccess<T>(l);
}

template<typename T>
void mkey_compare(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Key comapre function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << l.key_comp()(2, 1) << std::endl; //Returns compare object that takes two parameters //Thus returns 0 if first number is not smaller than second one and returns 1 if first number is smaller than second one
  maccess<T>(l);
}

template<typename T>
void mvalue_compare(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Value compare function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  typename T::iterator m = l.begin();
  ++m;
  ++m;
  typename T::iterator k = l.end();
  --k;
  --k;
  if (m == l.end() || k == l.end()) //Undefined behavior out of range
    return ;
  std::cout << "Iterator 1: " << m->first << "\t" << m->second << std::endl;
  std::cout << "Iterator 2: " << k->first << "\t" << k->second << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << l.value_comp()(*m, *k) << std::endl; //Returns compare class around compare object, takes iterators as parameters instead of key values
  maccess<T>(l);
}

template<typename T>
void mfind(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Find function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator p = l.find(0);
  if (p != l.end()) //Out of range iterator random value
    std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  typename T::iterator p1 = l.find(10);
  if (p1 != l.end()) //Out of range iterator random value
    std::cout << "return: " << p1->first << "\t" << p1->second << std::endl;
  maccess<T>(l);
}

template<typename T>
void mcount(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Count function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested container: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::cout << l.count(0) << std::endl;
  std::cout << l.count(10) << std::endl;
  maccess<T>(l);
}

template<typename T>
void mlower_bound(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Lower bound function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator p = l.lower_bound(3);
  if (p != l.end())
    std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  typename T::iterator p1 = l.lower_bound(0);
  if (p1 != l.end())
    std::cout << "return: " << p1->first << "\t" << p1->second << std::endl;
  typename T::iterator p2 = l.lower_bound(10);
  if (p2 != l.end())
    std::cout << "return: " << p2->first << "\t" << p2->second << std::endl;
  maccess<T>(l);
}

template<typename T>
void mupper_bound(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Upper bound function" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Tested containers: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator p = l.upper_bound(3);
  if (p != l.end())
    std::cout << "return: " << p->first << "\t" << p->second << std::endl;
  typename T::iterator p1 = l.upper_bound(0);
  if (p1 != l.end())
    std::cout << "return: " << p1->first << "\t" << p1->second << std::endl;
  typename T::iterator p2 = l.upper_bound(10);
  if (p2 != l.end())
    std::cout << "return: " << p2->first << "\t" << p2->second << std::endl;
  maccess<T>(l);
}

template<typename T>
void mequal_range(T &l)
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Equal range function " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  maccess<T>(l);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  std::pair<typename T::iterator, typename T::iterator > p = l.equal_range(3);
  if (p.first != l.end())
    std::cout << "return: " << p.first->first << "\t" << p.first->second << std::endl;
  if (p.second != l.end())
    std::cout << "return: " << p.second->first << "\t" << p.second->second << std::endl;
  std::pair<typename T::iterator, typename T::iterator > p1 = l.equal_range(0);
  if (p1.first != l.end())
    std::cout << "return: " << p1.first->first << "\t" << p1.first->second << std::endl;
  if (p1.second != l.end())
    std::cout << "return: " << p1.second->first << "\t" << p1.second->second << std::endl;
  std::pair<typename T::iterator, typename T::iterator > p2 = l.equal_range(10);
  if (p2.first != l.end())
    std::cout << "return: " << p2.first->first << "\t" << p2.first->second << std::endl;
  if (p2.second != l.end())
    std::cout << "return: " << p2.second->first << "\t" << p2.second->second << std::endl;
}

template<typename T>
void miterator_tests2()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests 2" << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T m;
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(1, 4));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(2, 3));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(3, 6));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(4, 2));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(5, 5));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(6, 5));
  m.insert(std::pair<typename T::key_type, typename T::mapped_type>(7, 1));
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = m.begin();
  typename T::reverse_iterator l = m.rbegin();
  std::pair<typename T::key_type, typename T::mapped_type> tmp;

  while (i != m.end())
  {
    tmp = *i++;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;

  while (l != m.rend())
  {
    tmp = *l++;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;

  i = m.begin();
  l = m.rbegin();

  tmp = *++i;
  std::cout << tmp.first << "\t" << tmp.second << std::endl << std::endl;

  tmp = *++l;
  std::cout << tmp.first << "\t" << tmp.second << std::endl << std::endl;

  i = m.end();
  l = m.rend();

  i--;
  while (i != m.begin())
  {
    tmp = *i--;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;

  l--;
  while (l != m.rbegin())
  {
    tmp = *l--;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;

  i = m.end();
  l = m.rend();

  while (i != m.begin())
  {
    tmp = *--i;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;

  while (l != m.rbegin())
  {
    tmp = *--l;
    std::cout << tmp.first << "\t" << tmp.second << std::endl;
  }
  std::cout << std::endl;
}

template<typename T, typename T1, typename T2>
void miterator_tests1()
{
  std::cout << std::setfill ('#') << std::setw (100) << std::left << "Iterator tests " << std::endl;
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Compared containers: " << std::endl;
  T m;
  m.insert(std::pair<T1, T2>(1, 4));
  m.insert(std::pair<T1, T2>(2, 3));
  m.insert(std::pair<T1, T2>(3, 6));
  m.insert(std::pair<T1, T2>(4, 2));
  m.insert(std::pair<T1, T2>(5, 5));
  m.insert(std::pair<T1, T2>(6, 5));
  m.insert(std::pair<T1, T2>(7, 1));
  maccess<T>(m);
  std::cout << std::setfill ('>') << std::setw (50) << std::left << "Result: " << std::endl;
  typename T::iterator i = m.begin();
  ++i;
  typename T::iterator k(m.end());
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

  std::pair<T1, T2> p = *i;
  std::cout << p.first << "\t" << p.second << std::endl;
  p.first = 7;
  p.second = 2;
  std::cout << i->first << "\t" << i->second << std::endl;

  std::pair<T1, T2> p1 = *k;
  std::cout << p1.first << "\t" << p1.second << std::endl;
  p1.first = 7;
  p1.second = 2;
  std::cout << k->first << "\t" << k->second << std::endl;
}

template<typename T, typename T1, typename T2>
struct s_functions_ptr<T> *map_basic_func(unsigned int &lenght)
{
  struct s_functions_ptr<T> func[6] = {{mdefault_constructor<T>, 1}, {mrange_constructor<T, T1, T2>, 2}, \
  {mcopy_constructor<T, T1, T2>, 3}, {miterator_tests1<T, T1, T2>, 4}, {miterator_tests2<T>, 5}};
  struct s_functions_ptr<T> *ret = new struct s_functions_ptr<T>[6];

  lenght = 6;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func[i];
  return ret;
}


template<typename T, typename T1, typename T2>
struct s_functions_ptr1<T> *map_func1(unsigned int &lenght)
{
  struct s_functions_ptr1<T> func1[22] = {{mempty<T>, 1}, {melement_access<T>, 2}, {melement_access2<T>, 3}, {minsert_single_element<T, T1, T2>, 4}, \
  {minsert_single_element2<T, T1, T2>, 5}, {minsert_single_element3<T, T1, T2>, 6}, {minsert_hint<T, T1, T2>, 7}, {minsert_hint2<T, T1, T2>, 8}, \
  {minsert_hint3<T, T1, T2>, 9}, {merase_iterator_based<T>, 10}, {merase_iterator_based2<T>, 11}, {merase_key_based<T>, 12}, {merase_range<T>, 13}, \
  {merase_range2<T>, 14}, {mclear<T>, 15}, {mkey_compare<T>, 16}, {mvalue_compare<T>, 17}, {mfind<T>, 18}, {mcount<T>, 19}, {mlower_bound<T>, 20}, \
  {mupper_bound<T>, 21}, {mequal_range<T>, 22}};
  struct s_functions_ptr1<T> *ret = new struct s_functions_ptr1<T>[22];

  lenght = 22;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func1[i];
  return ret;
}

template<typename T, typename T1, typename T2>
struct s_functions_ptr2<T> *map_func2(unsigned int &lenght)
{
  struct s_functions_ptr2<T> func2[5] = {{massignation_operator<T>, 23}, {minsert_range<T>, 24}, {minsert_range2<T>, 25}, {minsert_range3<T>, 26}, \
  {mswap_member_function<T>, 27}};
  struct s_functions_ptr2<T> *ret = new struct s_functions_ptr2<T>[5];

  lenght = 5;
  for (unsigned int i = 0; i < lenght; i++)
    ret[i] = func2[i];
  return ret;
}

#endif
