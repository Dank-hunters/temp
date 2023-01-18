if [ -e test1 ]; then 
				rm test1
fi
if [ -e test2 ]; then 
				rm test2
fi

VAR=int
if [ $@ == "pop_push_erase" ]; then
							VAR=std::string			
fi
c++ -fsanitize=address -g3  -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft -D TESTED_TYPE=$VAR $@  && ./a.out >> test1
c++ -fsanitize=address -g3 -D TESTED_NAMESPACE=std -D TESTED_TYPE=$VAR $@  && ./a.out >> test2
diff test1 test2
rm test1 test2
rm -rf a.out.dSYM
c++  -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft -D TESTED_TYPE=$VAR $@

printf "\n\n############## leaks test ####################\n\n"

leaks -atExit -- ./a.out
rm a.out
rm -rf a.out.dSYM
