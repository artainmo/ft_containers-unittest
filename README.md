# ft_containers-unittest
An advanced unit-test written in c++ for 42 school's [ft_containers](https://github.com/artainmo/ft_containers) project or other c++ containers.

### PREPARE

* Change path to your container's '.hpp' in 'main.hpp'

* Optional: Set ERROR LIMIT by changing G_ERROR_LIMIT in 'main.cpp'

* Optional: Set G_STOP_AT_TEST in 'main.cpp' to keep testing a particular case independently of errors

### USE NON-CONST UNITTEST
Launch non-const unittest
```
make <list/stack/map/queue/vector>
```
See Results in '/output'

See Tests in '/src'.

### USE CONST UNITTEST
Launch const unittest
```
make const
```
You should have a certain amount of compilation errors not more or less.

### NOT TESTED
To test vector container correctly set its buffer_size to 10.<br>
Allocator_type.<br>
Undefined behavior; unintialized memory, SIGABORT, SEGFAULT, ...<br>
Max size as you can have different answer than real one. You must be able to explain, your own implementation of it.<br>
Destructor is not tested and memeory leaks are not tested.<br>
Special types like std::string.

### OTHER
Infinite loop results can be checked in output/tmp_my and output/tmp_real

### NOTES
When excess test errors are written to file, fills up computer memory and creates bug.<br>
Solution is to not check in the end but after each test and only write errors to files, max number errors before quiting.<br>
Combination of tests are generated based on different container objects.<br>
Using processes to test segfaults and sigabort, so that the error gets catched and exits the child process.<br>
For error messages that cannot be catched like memory freed not allocated, we redirect the stderr to /dev/null.<br>
Infinte loops cannot be catched unfortunately, but result can be viewed in output/tmp_my and output/tmp_real.<br>
Temp files are used, if program blocks and ctrl-c is used to quit program, tmp files won't be deleted and can be viewed to debug, useful for infinite loops.<br>
Threads used with the failed idea of increasing the programs speed, failed due to impossibility to write to multiple fds at the same time.<br>
But in the end threads increased program speed a lot by increasing the speed of fork.<br>
Fork gets slower as parent process uses more memory both stack and heap memory, due to its copying feature, using threads detaches from parent process and speeds up the forks, threads increased program speed 5X.

Because this unittest is very advanced I doubt it will be used by others, as validating it is probably way more complex than what is demanded in 42 school project ft_containers.
