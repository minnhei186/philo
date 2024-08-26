CC=cc
CFLAGS=-Wall -Wextra -Werror
INCDIR=-Iinclude 

SRCS = src/check_validation.c \
       src/error.c \
       src/philo.c \
       src/time.c \
       src/data_init.c \
       src/free.c \
       src/philo_func.c \
       src/data_init_utils.c \
       src/observe_and_moniter.c \
       src/philo_utils.c
OBJS=$(SRCS:.c=.o)

NAME=philo

all:$(NAME)

$(NAME):$(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $(NAME)


%.o:%.c
	$(CC) $(CFLAGS) $(INCDIR) -g -c $< -o $@

clean:
	rm -rf $(OBJS)
fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re

