#include "../main.hpp"

void segfault( int signum ) { std::cout << "SEGFAULT" << std::endl; exit(signum); } //Catch segfaults and write in correct fd
void sigabort( int signum ) { std::cout << "SIGABORT" << std::endl; exit(signum); } //Catch sigaborts and write in correct fd
void sigquit(int sig) { sig = 0; exit(sig); } //SIGQUIT send from childprocess to stop program does not return error code

std::string itoa(int num) //c++ has no itoa!! Only c++11 has itoa equivalent
{
  std::string s;
  std::stringstream out;

  out << num;
  s = out.str();
  return s;
}

unsigned int G_ERROR_COUNT = 0; //Lifetime end is not scope but whole program as assigned in static memory
unsigned int G_LINE = 0; //By knowing how much lines/tests you went through you can view your progress

void check_answer(std::ifstream &fd_r, std::ifstream &fd_r_r, std::ofstream &output_my, std::ofstream &output_real) //Check all lines takes the test name and compares following test output
{
  std::string me;
  std::string real;
  std::string tmp_me;
  std::string tmp_real;
  int error = 0;

  //Take file input tmp_my and tmp_real into string objects
  while(getline(fd_r_r, tmp_real))
  {
    G_LINE++;
    getline(fd_r, tmp_me);
    if (std::strcmp(tmp_real.c_str(), tmp_me.c_str()) == 0) //c++ string compare function bizarre bug returning errors once we start writing in output fds, c strcmp does not bug
    {
      std::cout << "\033[1m\033[32m" << "<>" << " "; //Use green color code
      fflush(stdout);
    }
    else
    {
      std::cout << "\033[1m\033[31m" << "<>" << " "; //Use red color code
      fflush(stdout);
      error = 1;
    }
    me += tmp_me + '\n';
    real += tmp_real + '\n';
  }

  //Clear the file by truncating it at opening
  fd_r.close();
  fd_r_r.close();
  fd_r.open("output/tmp_my", std::ofstream::out | std::ofstream::trunc);
  fd_r_r.open("output/tmp_real", std::ofstream::out | std::ofstream::trunc);

  if (error != 0 || (G_STOP_AT_TEST != 0 && G_STOP_AT_TEST <= G_LINE)) //Write errors to output files and check error limit
  {
    G_ERROR_COUNT++;
    output_my << me << std::endl;
    output_real << real << std::endl;
    if ((G_ERROR_COUNT >= G_ERROR_LIMIT && G_STOP_AT_TEST == 0) || (G_STOP_AT_TEST != 0 && G_STOP_AT_TEST <= G_LINE))
    {
      int dev_null = open("/dev/null", O_CREAT | O_WRONLY);
      feedback();
      dup2(dev_null, 1); //Bizarre bug whereby continues writing numbers after error message, resolved
      std::remove("output/tmp_my");
      std::remove("output/tmp_real");
      kill(0, SIGQUIT);
    }
  }
}

void feedback()
{
  float total;

  if (G_LIST == 1)
    total = LIST_TOTAL_TESTS;
  if (G_MAP == 1)
    total = MAP_TOTAL_TESTS;
  if (G_QUEUE == 1)
    total = QUEUE_TOTAL_TESTS;
  if (G_STACK == 1)
    total = STACK_TOTAL_TESTS;
  if (G_VECTOR == 1)
    total = VECTOR_TOTAL_TESTS;
  if (G_ERROR_LIMIT > 1)
    std::cout << "\033[34m" << "\n" << G_ERROR_COUNT << " ERRORS ATTAINED ON "<< G_LINE << " TESTS" << std::endl;
  else
    std::cout << "\033[34m" << "\n" << G_ERROR_COUNT << " ERROR ATTAINED ON "<< G_LINE << " TESTS" << std::endl;
  fflush(stdout);
  float correct_answers = G_LINE - G_ERROR_COUNT;
  std::cout << "\033[34m" << "------> " << std::setprecision(3) << (correct_answers / total) * 100 << "%\n" << std::endl;
  fflush(stdout);
}

void cont()
{
  std::string input;

  feedback();
  std::cout << "\033[30m" <<"\nPRESS ENTER to continue";
  std::getline(std::cin, input);
  std::cout << "\n";
}
