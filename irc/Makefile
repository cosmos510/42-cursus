NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
INCDIR = includes
OBJDIR = obj

SRC = main.cpp Server.cpp Client.cpp Channel.cpp Commands.cpp
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
