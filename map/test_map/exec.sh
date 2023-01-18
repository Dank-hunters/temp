if [ -e test1 ]; then 
				rm test1
fi
if [ -e test2 ]; then 
				rm test2
fi

c++ -Wall -Wextra -Werror -fsanitize=address -g3 -D TESTED_NAMESPACE=ft $@ && ./a.out >> test1
c++ -Wall -Wextra -Werror -fsanitize=address -g3 -D TESTED_NAMESPACE=std $@ && ./a.out >> test2

diff test1 test2
rm test1 test2
rm -rf a.out.dSYM


c++ -Wall -Wextra -Werror -D TESTED_NAMESPACE=ft $@

printf "\n\n############## leaks test ####################\n\n"
leaks -atExit -- ./a.out

rm -rf a.out.dSYM