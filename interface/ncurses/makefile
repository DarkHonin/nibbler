
NAME=ncur.interface.dll
INCLUDE_PATHS=$(INTERFACE) $(NCUR)/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME):
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -L$(NCUR)/lib -lncurses -shared -o $(NAME)