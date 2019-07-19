
PATH=$(shell pwd)
NAME=glfw.interface.dll
INCLUDE_PATHS=$(INTERFACE) $(GLFW)/include $(GLEW)/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME):
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -shared -o $(NAME) -L$(GLEW)/lib -L$(GLFW)/lib -lglfw -lglew -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo