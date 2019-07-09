SRC=$(shell find src -name "*.cpp" -type f)
OBJ=$(patsubst src/%.cpp, obj/%.o, $(SRC))
INCLUDE=$(addprefix -I,$(SFML)/include $(realpath include))
OBJ_PATH=obj
LIBS=-F$(SFML)/Frameworks -framework sfml -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

FLAGS= -std=c++11

GCC=clang++

NAME=SFMLDll.dll

$(NAME): $(OBJ_PATH) $(OBJ) $(SFML)
	@echo "Building $(NAME)"
	@$(GCC)  $(SRC) $(INCLUDE) $(FLAGS) -shared -o $(NAME)  $(LIBS)

$(OBJ_PATH)/%.o : src/%.cpp
	@$(GCC) $< -o $@ $(INCLUDE) -c $(FLAGS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
clean:
	@rm -r $(OBJ_PATH)

fclean: clean
	@rm $(NAME)
re: fclean $(NAME)