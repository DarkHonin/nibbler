SFML_DLL=sfml.interface.dll
GLFW_DLL=glfw.interface.dll
SDL_DLL=sdl.interface.dll

PATHS=$(realpath sfml sdl glfw)
echo = /bin/echo
make=/usr/bin/make

DLLS = $(GLFW_DLL) $(SDL_DLL) # $(SFML_DLL) 

make: $(DLLS)

$(SFML_DLL):
	@$(make) -f sfml/makefile INTERFACE=$(realpath include) PATH=$(realpath sfml) SFML=$(SFML) BUILD=$(realpath $(BUILD))

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