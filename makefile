BREW=$(HOME)/.brew/bin/brew
SDL=$(HOME)/.brew/Cellar/sdl2/2.0.9_1
GLFW=$(HOME)/.brew/Cellar/glfw/3.3
SFML=$(HOME)/nibbler/SFML-2.5.1-macos-clang
echo = /bin/echo
BUILD = $(realpath build.mk)

DEPENDENCIES= $(SDL) $(GLFW)

DLLS=interface/sfml.interface.dll interface/sdl.interface.dll interface/glfw.interface.dll

NAME=./nibbler

PATH=$(shell pwd)
INCLUDE_PATHS=$(INTERFACE) interface/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

$(NAME): $(DLLS)
	@$(echo) "Building $(NAME)"
	$(GCC) $(OBJ) $(INCLUDE) -o $(NAME) -ldl

_fclean:
	@make -C interface fclean BUILD=$(BUILD)

scrub: dep_clear

$(DLLS):
	@$(make) -C interface BUILD=$(BUILD) SDL=$(SDL) GLFW=$(GLFW) SFML=$(SFML)

$(SFML):
	@curl https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz -o SFML-2.5.1-macOS-clang.tar.gz
	@tar -xf SFML-2.5.1-macOS-clang.tar.gz

$(DEPENDENCIES): $(BREW)
	@$(echo) "Installing brews: $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))"
	@brew install $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))

$(BREW):
	@sh -c "$$(curl -fsSL https://raw.githubusercontent.com/wethinkcode/homebrew/master/install.sh)"

dep_clear:
	@$(echo) "Cleaning all brews"
	@brew uninstall $(foreach dep,$(DEPENDENCIES), $(shell basename $(dir $(dir $(dep)))))
	@rm -rf SFML-2.5.1-macOS-clang.tar.gz SFML-2.5.1-macos-clang