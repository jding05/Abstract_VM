NAME = avm

SRCS = main.cpp Lexer.cpp Parser.cpp RPNCal.cpp Factory.cpp

CC = clang++ -Wall -Werror -Wextra -std=c++11

FSAN = -g -fsanitize=address

OBJS		:= $(SRCS:.cpp=.o)

# colorize
RED		:= "\033[1;31m"
GREEN	:= "\033[1;32m"
YELLOW	:= "\033[0;33m"
RESET	:= "\033[0m"

# compile and create everything
all: $(NAME)
	@echo $(GREEN)"\n[Executable] $(NAME) created\n"$(RESET)
# Compile the program with the Objects
$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $@

# This won't run if the source files don't exist or are not modified
%.o: %.cpp

	@ echo $(YELLOW)"[Compiling] $<..."$(RESET)
	$(CC) -o $@ -c $<


clean:
	@/bin/rm -rf *~ \#*\# *.swp* *.gch* a.out *.o
	@echo $(RED)"[INFO] Objects removed!"$(RESET)

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo $(RED)"[INFO] $(NAME) removed!\n"$(RESET)

re: fclean all

fsan:
	$(CC) $(FSAN) $(SRCS) -o $(NAME)

run: $(NAME)
	./$(NAME)
.PHONY: all clean fclean re run fsan
