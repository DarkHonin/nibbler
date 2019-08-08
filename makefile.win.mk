DEP_FOLDER=$(HOME)/dep
SDL=$(DEP_FOLDER)/.brew/Cellar/sdl2/2.0.9_1
GLFW=$(DEP_FOLDER)/GLFW/
GLEW=$(HOME)/.brew/Cellar/glew/2.1.0
SFML=$(HOME)/nibbler/SFML-2.5.1-macos-clang
echo = /bin/echo
BUILD = $(realpath build.mk)

DEPENDENCIES= $(SDL) $(GLFW) $(GLEW)

DLLS=interface/sfml.interface.dll interface/sdl.interface.dll interface/glfw.interface.dll

NAME=./nibbler

PATH=$(shell pwd)
INCLUDE_PATHS=$(PATH)/interface/include

export PATH
export NAME
export INCLUDE_PATHS

include $(BUILD)

GCC=/usr/bin/g++.exe
export GCC
$(NAME): $(SFML) $(DLLS) $(DEPENDENCIES) 
	@$(echo) "Building $(NAME)"
	@$(GCC) $(OBJ) $(INCLUDE) -o $(NAME) -ldl

reall: _fclean re

_fclean:
	@$(make) -C interface fclean BUILD=$(BUILD)

scrub: _fclean clean

