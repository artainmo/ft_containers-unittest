#ifndef TEST_LISTS_HPP
#define TEST_LISTS_HPP

#include "../main.hpp"

template<typename T>
void safe_space_test(void (function_pointer)(T &l), T &l, std::ofstream &fd)
{
  pid_t pid = fork(); //vfork is faster than fork, the parent process automatically waits for child process because they share the same stack memory
  std::streambuf *sfd = fd.rdbuf();

  if (pid == 0)
  {
    std::cout.rdbuf(sfd);  //Redirect cout or stream 1 to file
    function_pointer(l); //Call real
    exit(0);
  }
  wait(NULL);
}

template<typename T>
void safe_space_test(void (function_pointer)(T &l, T &l2), T &l, T &l2, std::ofstream &fd)
{
  pid_t pid = fork();
  std::streambuf *sfd = fd.rdbuf();

  if (pid == 0)
  {
    std::cout.rdbuf(sfd);  //Redirect cout or stream 1 to file
    function_pointer(l, l2); //Call real
    exit(0);
  }
  wait(NULL);
}

template<typename T, typename R, typename T1, typename T2>
void tests(T l, T l2, R lr, R lr2, std::ofstream &fd_w, std::ifstream &fd_r, std::ofstream &fd_w_r, std::ifstream &fd_r_r,
  std::ofstream &output_my, std::ofstream &output_real, struct test_args<T, R> *args)
{
  std::streambuf *fd_1 = std::cout.rdbuf();
  unsigned int total = args->functions1_number + args->functions2_number;

  for (unsigned int i = 0; i < total ; i++)
  {
    if (i < args->functions1_number) //Functions with one parameter
    {
      std::cout << "\033[30m" << args->real_func1[i].num << ' ';
      fflush(stdout); //Necessary otherwise bug occurs if not using \n that naturally flushes the buffer
      safe_space_test<R>(args->real_func1[i].function_pointer, lr, fd_w_r); //Call real
      safe_space_test<T>(args->my_func1[i].function_pointer, l, fd_w); //Call own
      std::cout.rdbuf(fd_1); //Reset stream 1
    }
    else //Functions with two parameters
    {
      std::cout << "\033[30m" << args->real_func2[i - args->functions1_number].num << ' ';
      fflush(stdout); //Necessary otherwise bug occurs if not using \n that naturally flushes the buffer
      safe_space_test<R>(args->real_func2[i - args->functions1_number].function_pointer, lr, lr2, fd_w_r); //Call real
      safe_space_test<T>(args->my_func2[i - args->functions1_number].function_pointer, l, l2, fd_w); //Call own
      std::cout.rdbuf(fd_1); //Reset stream 1
    }
    check_answer(fd_r, fd_r_r, output_my, output_real);
  }
}

template<typename T, typename R, typename T1, typename T2>
void *pthread_start2(void *arg)
{
  struct test_args<T, R> *args;
  args = (struct test_args<T, R> *)arg;
  std::ofstream fd_w("output/tmp_my");
  std::ifstream fd_r("output/tmp_my");
  std::ofstream fd_w_r("output/tmp_real");
  std::ifstream fd_r_r("output/tmp_real");
  std::ofstream output_my("output/my");
  std::ofstream output_real("output/real");

  tests<T, R, T1, T2>(args->my_elems[args->thread_num1], args->my_elems[args->thread_num2], args->real_elems[args->thread_num1], args->real_elems[args->thread_num2],
     fd_w, fd_r, fd_w_r, fd_r_r, output_my, output_real, args);
  fd_w.close();
  fd_r.close();
  fd_w_r.close();
  fd_r_r.close();
  output_my.close();
  output_real.close();
  return 0;
}

template<typename T, typename R, typename T1, typename T2>
void *pthread_start(void *arg)
{
  struct test_args<T, R> *args;
  args = (struct test_args<T, R> *)arg;
  pthread_t id;

  for (unsigned int l = 0; l < args->containers_number; l++)
  {
    args->thread_num2 = l;
    pthread_create(&id, NULL, pthread_start2<T, R, T1, T2>, args);
    pthread_join(id, NULL); //Waits for just created thread to end before continuing, using new threads fastens forks
  }
  return 0;
}

template<typename T, typename R, typename T1, typename T2>
void test(struct test_args<T, R> *args)
{
  int fd_2 = dup(2);
  int dev_null = open("/dev/null", O_CREAT | O_WRONLY); // /dev/null Discards all data written to it, open and dup are used instead of c++ cerr object because it does not work...
  args->thread_num1 = 0;
  args->thread_num2 = 0;
  pthread_t id;

  std::cout << "\033[35m" << "Functions tests:" << std::endl;
  dup2(dev_null, 2); //Redirect stderr to dev/null (a file that discards input) => avoid non-catchable "malloc not allocated error" output in stdin
  for (unsigned int i = 0; i < args->containers_number; i++) //Do all tests
  {
    args->thread_num1 = i;
    pthread_create(&id, NULL, pthread_start<T, R, T1, T2>, args);
    pthread_join(id, NULL); //Waits for just created thread to end before continuing, using new threads fastens forks
  }
  dup2(2, fd_2); //Reset stderr
  std::cout << "\033[35m" << "\nEnd functions tests\n" << std::endl;
  fflush(stdout);

  close(fd_2);
  close(dev_null);
}

template<typename T, typename R, typename T2>
void basis_tests(struct s_functions_ptr<T> *(function_pointer)(unsigned int &lenght), struct s_functions_ptr<R> *(function_pointer2)(unsigned int &lenght))
{
  unsigned int lenght;
  //Create fds to output files
  std::ofstream fd_w("output/tmp_my");
  std::ifstream fd_r("output/tmp_my");
  std::ofstream fd_w_r("output/tmp_real");
  std::ifstream fd_r_r("output/tmp_real");
  std::ofstream output_my("output/my");
  std::ofstream output_real("output/real");

  //Create streambuffers to redirect output
  std::streambuf *fd_1 = std::cout.rdbuf();
  std::streambuf *fd_my = fd_w.rdbuf();
  std::streambuf *fd_real = fd_w_r.rdbuf();

  struct s_functions_ptr<T> *my_func = function_pointer(lenght);
  struct s_functions_ptr<R> *real_func = function_pointer2(lenght);

  std::cout << "\033[35m" << "\nConstructors and iterators basis tests:" << std::endl;
  for (unsigned int i = 0; i < lenght; i++)
  {
    pid_t pid = fork();

    if (pid == 0)
    {
      std::cout << "\033[30m" << real_func[i].num << ' ';
      fflush(stdout); //Necessary otherwise bug occurs if not using \n that naturally flushes the buffer
      std::cout.rdbuf(fd_real);
      real_func[i].function_pointer(); //Call real
      std::cout.rdbuf(fd_my); //Redirect cout or stream 1 to file
      my_func[i].function_pointer(); //Call own
      std::cout.rdbuf(fd_1); //Reset stream 1
      exit(0);
    }
    wait(NULL);
    check_answer(fd_r, fd_r_r, output_my, output_real);
  }
  std::cout << "\033[35m" << "\nEnd constructors and iterators basis tests\n" << std::endl;

  fd_w.close();
  fd_w_r.close();
  fd_r.close();
  fd_r_r.close();
  output_my.close();
  output_real.close();
  delete [] my_func;
  delete [] real_func;
}

#endif
