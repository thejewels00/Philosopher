LIBRARY = philo
CC = @cc
CFLAGS = -Wall -Werror -Wextra -g
SRC =	main.c \
		ft_atoi.c \
		threads.c \
		pthread_1.c \


OBJECT_FILE = $(SRC:%.c=%.o)

all : $(LIBRARY) 

clean :
	@rm -rf *.o 
	@printf "\033[1;36mObject Files Deleted !\033[0m\n"

fclean : clean
	@rm  -rf $(LIBRARY) 		
	@printf "\033[1;36mProgram Deleted !\033[0m\n"

re : fclean all

$(LIBRARY) : $(OBJECT_FILE) 
	$(CC) $(CFLAGS) -pthread $(OBJECT_FILE) -o $(LIBRARY)
	@printf "\033[1;33m****PHILO compiled Succesfully ! ****\033[0m\n"


