BREW=$(HOME)/.brew/bin/brew
SDL=$(HOME)/.brew/Cellar/sdl2/2.0.9_1
GLFW=$(HOME)/.brew/Cellar/glfw/3.3
SFML=$(HOME)/nibbler/SFML-2.5.1-macos-clang


DEPENDENCIES= $(CMAKE) $(DOXY) $(SDL) $(GLFW)

GLFWDLL=GLFWdll/GLFWDll.dll
SDLDLL=SDLdll/SDLDll.dll
SFMLDLL=SFMLdll/SFMLDll.dll

DLLS=$(GLFWDLL) $(SDLDLL) $(SFMLDLL)

SRC=$(shell find src -name "*.cpp" -type f)
OBJ=$(patsubst src/%.cpp, obj/%.o, $(SRC))
INCLUDE=$(addprefix -I, $(realpath include))
OBJ_PATH=obj

FLAGS= -std=c++11
GCC=clang++

NAME=nibbler

$(NAME): $(DLLS) $(OBJ_PATH) $(OBJ)
	@echo "Building $(NAME)"
	@$(GCC) $(SRC) -o $(NAME) $(INCLUDE)

$(OBJ_PATH)/%.o : src/%.cpp
	@$(GCC) $< -o $@ $(INCLUDE) -c $(FLAGS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

clean_dlls:
	@$(foreach dl, $(DLLS), make -C $(dir $(dl)) clean;)

fclean_dlls:
	$(foreach dl, $(DLLS), make -C $(dir $(dl)) fclean;)

clean:
	@rm -r $(OBJ_PATH)

fclean: clean
	@rm $(NAME)
re: fclean $(NAME)

scrub: fclean fclean_dlls dep_clear

$(GLFWDLL): $(GLFW) 
	@make -C $(dir $(GLFWDLL)) GLFW=$(GLFW)

$(SDLDLL): $(SDL) 
	@make -C $(dir $(SDLDLL)) SDL=$(SDL)

$(SFMLDLL): $(SFML)
	@make -C $(dir $(SFMLDLL)) SFML=$(SFML)

$(SFML):
	@curl https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz -o SFML-2.5.1-macOS-clang.tar.gz
	@tar -xf SFML-2.5.1-macOS-clang.tar.gz

$(DEPENDENCIES): $(BREW)
	@echo "Installing brews: $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))"
	@brew install $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))

$(BREW):
	@sh -c "$$(curl -fsSL https://raw.githubusercontent.com/wethinkcode/homebrew/master/install.sh)"

dep_clear:
	@echo "Cleaning all brews"
	@brew uninstall $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))
	@rm -rf SFML-2.5.1-macOS-clang.tar.gz SFML-2.5.1-macos-clang