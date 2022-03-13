
SERVER = server
CLIENT = client
LIBFT = libft.a
LIBS = -L ./libft -lft
INC = -I . -I libft

# B_OBJS = $(B_SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C libft

$(SERVER): server.o minitalk.h
	$(CC) $(CFLAGS) server.o $(LIBS) -o $@

$(CLIENT): client.o minitalk.h
	$(CC) $(CFLAGS) client.o $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c $(INC)

clean:
	@rm -f server.o client.o
	@make clean -C libft

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@make fclean -C libft

re: fclean all