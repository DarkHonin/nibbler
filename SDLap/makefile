DEP_BUILD_DIR:=SDL
SDL_URL:=https://www.libsdl.org/release/SDL2-2.0.9.zip
SDL_ARCHIVE:=SDL2-2.0.9.zip
SDL:=$(DEP_BUILD_DIR)/include/SDL.h

SDL_INCLUDE=$(DEP_BUILD_DIR)/include

INCLUDE=$(addprefix -I,$(realpath ../dInterface include $(SDL_INCLUDE)) )
OBJ_PATH=objs
SRC_PATH=src
SRC=$(shell find $(SRC_PATH) -name "*.cpp" -type f)
OBJ:=$(patsubst $(SRC_PATH)%.cpp,$(OBJ_PATH)%.o, $(SRC))

GCC=clang++

NAME:=SDLap.dll

$(NAME): $(SDL) $(OBJ)

$(OBJ_PATH)/%.o : src/%.cpp $(OBJ_PATH)
	@echo $@ '<<' $<
	@mkdir -p $(@D)
	$(GCC) $< -o $@ $(FLAGS) $(INCLUDE)   -c

$(SDL): $(SDL_BUILD_DIR) $(SDL_ARCHIVE)
	unzip -o $(SDL_ARCHIVE) -d $(DEP_BUILD_DIR)
	cd $(DEP_BUILD_DIR); \
	cmake SDL2-2.0.9; \
	./configure; \
	make; \
	cp -r SDL2-2.0.9/include/* include

$(SDL_ARCHIVE):
	curl https://www.libsdl.org/release/SDL2-2.0.9.zip -o $(SDL_ARCHIVE)

$(SDL_BUILD_DIR):
	@mkdir $(SDL_BUILD_DIR)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

re: fclean $(NAME)

fclean:
	rm -rf $(DEP_BUILD_DIR)

test: $(OBJ) $(SDL)
	clang++ $(OBJ) src/test.cpp $(FLAGS) $(INCLUDE) -LSDL -lSDL2 -F /Library/Frameworks