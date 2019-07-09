SRC=$(shell find src -name "*.cpp" -type f)
OBJ=$(patsubst src/%.cpp, obj/%.o, $(SRC))
INCLUDE=$(addprefix -I,$(GLFW)/include $(realpath include))
OBJ_PATH=obj
LIBS=-L$(GLFW)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

FLAGS= -std=c++11

GCC=clang++

NAME=GLFWDll.dll

$(NAME): $(OBJ_PATH) $(OBJ) $(GLFW)
	@echo "Building $(NAME)"
	@$(GCC)  $(SRC) $(INCLUDE) $(FLAGS) -shared -o $(NAME)  $(LIBS)

$(OBJ_PATH)/%.o : src/%.cpp
	@$(GCC) $< -o $@ $(INCLUDE) -L$(GLFW)/lib -c $(FLAGS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
clean:
	@rm -r $(OBJ_PATH)

fclean: clean
	@rm $(NAME)
re: fclean $(NAME)