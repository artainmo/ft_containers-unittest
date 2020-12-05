# ft_containers_unittest
Unit-test for 42 school project ft_containers written in c++ for following containers, list, map, queue, stack, vector



#PREPARE
Prepare -> Change path to your containers hpp's in main.hpp
Optional prepare -> Choose ERROR LIMIT by changing G_ERROR_LIMIT in main.cpp
Optional prepare -> Set G_STOP_AT_TEST to keep testing a particular case independently of errors

#USE NON-CONST UNITTEST
Launch non-const unittest -> make list/stack/...
Results -> output/real and output/my
Tests -> src/..._tests.hpp

#USE CONST UNITTEST
Launch const unittest -> make const
You should have a certain amount of compilation errors not more or less

#NOT TESTED
To test vector container correctly set its buffer_size to 10
Allocator_type
Undefined behavior; unintialized memory, SIGABORT, SEGFAULT, ...
Max size as you can have different answer than real one. You must be able to explain, your own implementation of it.
Destructor is not tested and memeory leaks are not tested

#OTHER
Infinite loop results can be checked in output/tmp_my and output/tmp_real



#ABOUT UNITTEST
When excess test errors are written to file, fills up computer memory and creates bug.
Solution is to not check in the end but after each test and only write errors to files, max number errors before quiting.
Combination of tests are generated based on different container objects.
Using processes to test segfaults and sigabort, so that the error gets catched and exits the child process
For error messages that cannot be catched like memory freed not allocated, we redirect the stderr to /dev/null
Infinte loops cannot be catched unfortunately, but result can be viewed in output/tmp_my and output/tmp_real.
Temp files are used, if program blocks and ctrl-c is used to quit program, tmp files won't be deleted and can be viewed to debug, useful for infinite loops.
Threads used with the failed idea of increasing the programs speed, failed due to impossibility to write to multiple fds at the same time.
But in the end threads increased program speed a lot by increasing the speed of fork.
Fork gets slower as parent process uses more memory both stack and heap memory, due to its copying feature, using threads detaches from parent process and speeds up the forks, threads increased program speed 5X.
