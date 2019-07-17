
PATH=$(shell pwd)
NAME=sdl.interface.dll
INCLUDE_PATHS=$(INTERFACE) $(SDL)/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME):
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -L$(SDL)/lib -lsdl2 -shared -o $(NAME)