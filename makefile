BREW=$(HOME)/.brew/bin/brew
SDL=$(HOME)/.brew/Cellar/sdl2/2.0.9_1
GLFW=$(HOME)/.brew/Cellar/glfw/3.3


make: $(GLFW) $(SDL)

glfw: $(GLFW) 
	make -C GLFWdll GLFW=$(GLFW)

sdl : $(SDL)
	make -C SDLdll SDL=$(SDL)

$(GLFW):
	$(BREW) install glfw3

$(SDL):
	$(BREW) install sdl2

$(BREW):
	sh -c "$$(curl -fsSL https://raw.githubusercontent.com/wethinkcode/homebrew/master/install.sh)"