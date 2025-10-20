NAME = philo
SRC_DIR = src
INCLUDES = includes

SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/routines.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/philos.c \
	$(SRC_DIR)/mutexs.c \
	$(SRC_DIR)/rules.c \
	$(SRC_DIR)/destroy_all.c \
	$(SRC_DIR)/you_can_move_one.c
	

OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDES) -pthread

# Cores
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RED = \033[0;31m
RESET = \033[0m

# Regras

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)🔧 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Build complete: $(NAME)$(RESET)"

%.o: %.c $(INCLUDES)/philo.h
	@echo "$(YELLOW)🧱 Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)🔥 Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re