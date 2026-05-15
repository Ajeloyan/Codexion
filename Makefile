NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCDIR = .
OBJDIR = objs
DEPDIR = $(SRCDIR)/.deps
INCDIR = includes

SRCS = main.c parsing.c work.c init.c utils.c request.c queue.c dongle.c monitor.c action.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR)

DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

-include $(SRCS:%.c=$(DEPDIR)/%.d)

clean: 
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
