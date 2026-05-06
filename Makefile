NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCDIR = .
DEPDIR = $(SRCDIR)/.deps
INCDIR = includes

SRCS = main.c parsing.c utils.c work.c
OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(INCDIR)

DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o: %.c
	@mkdir -p $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

-include $(SRCS:%.c=$(DEPDIR)/%.d)
clean: 
	rm -rf $(DEPDIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) 10 100 100 100 100 4 200 "edf"