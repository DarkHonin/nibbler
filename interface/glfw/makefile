
PATH=$(shell pwd)
NAME=glfw.interface.dll
INCLUDE_PATHS=$(INTERFACE) $(GLFW)/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME):
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -shared -o $(NAME) -L$(GLFW)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo