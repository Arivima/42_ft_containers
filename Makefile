# Makefile

SHELL=/bin/zsh

NAME_STD			= $(EXC_DIR)/std_containers
NAME_FT 			= $(EXC_DIR)/ft_containers

# Executables
EXC_DIR				:= ./executables
# Sources
SRCS_DIR			= ./test
SRCS				= $(shell find $(SRCS_DIR) -name "*.cpp" -print)
# Objects 
OBJS_DIR_FT			= ./objs_ft
OBJS_DIR_STD		= ./objs_std
OBJS				= $(patsubst $(SRCS_DIR)%,$(OBJS_DIR)%,$(SRCS:.cpp=.o))
# Compilation, Flags and header files
INC_DIR				= ./inc
INCLUDES			= $(shell find $(INC_DIR) -name "*.hpp" -print)

OUTPUT_DIR			= ./output

CC					= c++
CFLAGS 				= -Wall -Wextra -Werror -std=c++98 -Wshadow -I $(INC_DIR)

# Rules
all:				
	@$(MAKE) std
	@$(MAKE) ft

$(NAME):			$(OBJS) | $(EXC_DIR)
					@$(CC)  $(CFLAGS) $(OBJS)  -o $(NAME)
					@echo $(GREEN)$(NAME)"\tSuccessfully compiled" $(RESET)

$(OBJS_DIR)/%.o: 	$(SRCS_DIR)/%.cpp $(INCLUDES)
					@mkdir -p $(@D)
					@$(CC) -c $(CFLAGS) -DCOMPILE_MODE=$(COMPILE_MODE_VAL) $< -o $@

$(OBJS): 			| $(OBJS_DIR)

$(OBJS_DIR):
					@mkdir $(OBJS_DIR)

$(EXC_DIR):
					@mkdir $(EXC_DIR)

std:				
					
					@echo $(GREEN)$(NAME_STD)"\tnow trying to compile" $(RESET)
					@$(MAKE) NAME=$(NAME_STD) COMPILE_MODE_VAL=1 OBJS_DIR=$(OBJS_DIR_STD) $(NAME_STD)

ft:				
					@echo $(GREEN)$(NAME_FT)"\tnow trying to compile" $(RESET)
					@$(MAKE) NAME=$(NAME_FT) COMPILE_MODE_VAL=0 OBJS_DIR=$(OBJS_DIR_FT) $(NAME_FT)

clean:				
					@rm -rf $(OBJS_DIR_FT)
					@rm -rf $(OBJS_DIR_STD)
					@echo $(GREEN)"\t\tSuccessfully removed objects ft and std" $(RESET)

fclean: 			clean
					@rm -rf $(EXC_DIR)
					@rm -rf $(OBJS_DIR_FT)
					@rm -rf $(OBJS_DIR_STD)
					@rm -rf $(OUTPUT_DIR)
					@echo $(GREEN)"\t\tSuccessfully removed executables and cleaned folders ft and std" $(RESET)

re: 				fclean all
diff:				all
					@echo $(GREEN)"\t\tTesting" $(RESET)
					@mkdir -p output
					@export ft_time=$$(\
						( time ./$(NAME_FT) > $(OUTPUT_DIR)/output_ft.txt ) \
							|& cat | cut -d ' ' -f7 | cut -d 's' -f1\
					); \
					export std_time=$$(\
						( time ./$(NAME_STD) > $(OUTPUT_DIR)/output_std.txt ) \
							|& cat | cut -d ' ' -f7 | cut -d 's' -f1\
					); \
					printf "ft_time\t\t: %.50f\\n" $$ft_time; \
					printf "std_time\t: %.50f\\n" $$std_time; \

					@diff -y --suppress-common-line $(OUTPUT_DIR)/output_std.txt $(OUTPUT_DIR)/output_ft.txt | cat > $(OUTPUT_DIR)/diff.txt;
					@cat $(OUTPUT_DIR)/diff.txt
					@echo $(GREEN)"\t\tSuccessfully executed" $(RESET)


.PHONY: 			all clean fclean re std ft diff

# Colors
RESET		:= "\033[0m"
BLACK		:= "\033[30m"
RED			:= "\033[31m"
GREEN		:= "\033[32m"
YELLOW		:= "\033[33m"
BLUE		:= "\033[34m"
MAGENTA		:= "\033[35m"
CYAN		:= "\033[36m"
WHITE		:= "\033[37m"
BOLDBLACK	:= "\033[1m\033[30m"
BOLDRED		:= "\033[1m\033[31m"
BOLDGREEN	:= "\033[1m\033[32m"
BOLDYELLOW	:= "\033[1m\033[33m"
BOLDBLUE	:= "\033[1m\033[34m"
BOLDMAGENTA	:= "\033[1m\033[35m"
BOLDCYAN	:= "\033[1m\033[36m"
BOLDWHITE	:= "\033[1m\033[37m"

# END Makefile