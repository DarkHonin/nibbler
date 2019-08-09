NCUR_DLL=ncur.interface.dll
GLFW_DLL=glfw.interface.dll
SDL_DLL=sdl.interface.dll

PATHS=$(realpath ncurses sdl glfw)
echo = /bin/echo
make=/usr/bin/make

DLLS = $(GLFW_DLL) $(SDL_DLL) $(NCUR_DLL) 

make: $(DLLS)

$(NCUR_DLL):
	@$(make) -f ncurses/makefile INTERFACE=$(realpath include) PATH=$(realpath ncurses) NCUR=$(NCUR) BUILD=$(realpath $(BUILD))

$(SDL_DLL):
	@$(make) -f sdl/makefile INTERFACE=$(realpath include) PATH=$(realpath sdl) SDL=$(SDL) BUILD=$(realpath $(BUILD))

$(GLFW_DLL):
	@$(make) -f glfw/makefile INTERFACE=$(realpath include) PATH=$(realpath glfw) GLFW=$(GLFW) GLEW=$(GLEW) BUILD=$(realpath $(BUILD))

fclean:
	@for i in $(PATHS); do \
		$(make) -f  $$i/makefile PATH=$$i BUILD=$(realpath $(BUILD)) fclean; \
	done;

clean:
	@for i in $(PATHS); do \
		$(make) -f  $$i/makefile PATH=$$i BUILD=$(realpath $(BUILD)) clean; \
	done;

re: fclean make