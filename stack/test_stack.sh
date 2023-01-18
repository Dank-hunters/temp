rm diff diff2
c++ -fsanitize=address -g3 -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESP=ft  main_test_stack.cpp  && ./a.out >> diff
c++ -fsanitize=address -g3 -D TESTED_NAMESP=std main_test_stack.cpp  && ./a.out >> diff2
diff diff diff2

rm -rf a.out.dSYM

c++ -std=c++98 -Wall -Wextra -Werror -D TESTED_NAMESP=ft main_test_stack.cpp
printf "############## leaks test ####################\n"
leaks -atExit -- ./a.out
rm a.out

