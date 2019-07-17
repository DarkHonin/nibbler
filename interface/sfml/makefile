
PATH=$(shell pwd)
NAME=sfml.interface.dll
INCLUDE_PATHS=$(INTERFACE) $(SFML)/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME):
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -L$(SFML)/lib -lsfml-system -lsfml-window -shared -o $(NAME)