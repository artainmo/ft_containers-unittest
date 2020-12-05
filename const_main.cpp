#include "main.hpp"

//NOK = Should not create a compilation error
//OK = Should create a compilation error

void test_const_containers()
{
  std::cout << "Const list and iterator" << std::endl;
  const ft::list<int> cl((unsigned int)4,4);
  const ft::list<int> cl2((unsigned int)4,4);

  ft::list<int>::const_iterator cli(cl.end()); //NOK
  ft::list<int>::const_iterator cli2(cl.begin()); //NOK
  *cli; //NOK
  if (cli == cli2) {} //NOK
  if (cli != cli2) {} //NOK
  ft::list<int>::const_reverse_iterator crli(cl.rend()); //NOK
  ft::list<int>::const_reverse_iterator crli2(cl.rbegin()); //NOK
  *crli; //NOK
  if (crli == crli2) {} //NOK
  if (crli != crli2) {} //NOK

  cl.empty(); //NOK
  cl.size(); //NOK
  cl.max_size(); //NOK

  cl.front(); //NOK
  cl.front() = 9; //OK
  cl.back(); //NOK
  cl.back() = 9; //OK
  if (cl == cl2) {} //NOK
  if (cl != cl2) {} //NOK
  if (cl < cl2) {} //NOK
  if (cl > cl2) {} //NOK
  if (cl <= cl2) {} //NOK
  if (cl >= cl2) {} //NOK

  std::cout << "Const vector and iterator" << std::endl;
  const ft::vector<int> cv((unsigned int)4,4);
  const ft::vector<int> cv2((unsigned int)4,4);

  ft::vector<int>::const_iterator cvi(cv.end()); //NOK
  ft::vector<int>::const_iterator cvi2(cv.begin()); //NOK
  if (cvi == cvi2) {} //NOK
  if (cvi != cvi2) {} //NOK
  if (cvi > cvi2) {} //NOK
  if (cvi < cvi2) {} //NOK
  if (cvi >= cvi2) {} //NOK
  if (cvi <= cvi2) {} //NOK
  ft::vector<int>::const_reverse_iterator crvi(cv.rend()); //NOK
  ft::vector<int>::const_reverse_iterator crvi2(cv.rbegin()); //NOK
  if (crvi == crvi2) {} //NOK
  if (crvi != crvi2) {} //NOK
  if (crvi > crvi2) {} //NOK
  if (crvi < crvi2) {} //NOK
  if (crvi >= crvi2) {} //NOK
  if (crvi <= crvi2) {} //NOK

  cv.empty(); //NOK
  cv.size(); //NOK
  cv.max_size(); //NOK
  cv.capacity(); //NOK

  cv[0]; //NOK
  cv[0] = 9; //OK
  cv.at(0); //NOK
  cv.at(0) = 9; //OK
  cv.front(); //NOK
  cv.front() = 9; //OK
  cv.back(); //NOK
  cv.back() = 9; //OK
  if (cv == cv2) {} //NOK
  if (cv != cv2) {} //NOK
  if (cv < cv2) {} //NOK
  if (cv > cv2) {} //NOK
  if (cv <= cv2) {} //NOK
  if (cv >= cv2) {} //NOK

  std::cout << "Const map and iterator" << std::endl;
  ft::map<int, int> m;
  m[2] = 2;
  m[3] = 3;
  const ft::map<int, int> cm(m);
  const ft::map<int, int> cm2(m);

  ft::map<int, int>::const_iterator cmi(cm.end()); //NOK
  ft::map<int, int>::const_iterator cmi2(cm.begin()); //NOK
  *cmi2; //NOK
  *cmi = 9; //OK
  if (cmi == cmi2) {} //NOK
  if (cmi != cmi2) {} //NOK
  ft::map<int, int>::const_reverse_iterator crmi(cm.rend()); //NOK
  ft::map<int, int>::const_reverse_iterator crmi2(cm.rbegin()); //NOK
  *crmi2; //NOK
  *crmi = 9; //OK
  if (crmi == crmi2) {} //NOK
  if (crmi != crmi2) {} //NOK
  cm.empty(); //NOK
  cm.size(); //NOK
  cm.max_size(); //NOK

  cm.value_comp(); //NOK
  cm.key_comp(); //NOK
  cm.find(2); //NOK
  cm.count(2); //NOK
  cm.lower_bound(2); //NOK
  cm.upper_bound(2); //NOK
  std::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> er = cm.equal_range(2); //NOK

  std::cout << "Const stack" << std::endl;
  std::deque<int> mydeque(4,4);
  const ft::stack<int> cs(mydeque);
  const ft::stack<int> cs2(mydeque);

  cs.empty(); //NOK
  cs.size(); //NOK
  cs.top(); //NOK
  cs.top(); = 9; //OK

  if (cs == cs2) {} //NOK
  if (cs != cs2) {} //NOK
  if (cs < cs2) {} //NOK
  if (cs > cs2) {} //NOK
  if (cs <= cs2) {} //NOK
  if (cs >= cs2) {} //NOK


  std::cout << "Const queue" << std::endl;
  const ft::queue<int> cq(mydeque);
  const ft::queue<int> cq2(mydeque);

  cq.empty(); //NOK
  cq.size(); //NOK
  cq.back(); //NOK
  cq.back() = 9; //OK
  cq.front(); //NOK
  cq.front() = 9; //OK

  if (cq == cq2) {} //NOK
  if (cq != cq2) {} //NOK
  if (cq < cq2) {} //NOK
  if (cq > cq2) {} //NOK
  if (cq <= cq2) {} //NOK
  if (cq >= cq2) {} //NOK
}

//You should have gotten 11 compilation errors in total, not more or less, all commented with OK
int main()
{
  test_const_containers();
}
