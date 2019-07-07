SDL_URL_WIN = https://www.libsdl.org/release/SDL2-devel-2.0.9-mingw.tar.gz
SDL_URL_MAC = https://www.libsdl.org/release/SDL2-2.0.9.dmg
SDL_ARCHIVE_WIN = SDL2-devel-2.0.9-mingw.tar.gz
SDL_ARCHIVE_MAC = SDL2-2.0.9.dmg

ifeq ($(OS), Windows_NT)
SDL_ARCHIVE=$(SDL_ARCHIVE_WIN)
else
SDL_ARCHIVE=$(SDL_ARCHIVE_MAX)
endif

SDL_PATH=SDL2-2.0.9
SDL=/usr/include/SDL2/SDL.h

make: $(OS)

Windows_NT: $(SDL)

$(SDL): $(SDL_ARCHIVE)

	@tar -xf $(SDL_ARCHIVE)
	@cd $(SDL_PATH); \
	make native;\
	echo "SDL Has been installed"
	
$(SDL_ARCHIVE):
ifeq ($(OS), Windows_NT)
	curl -LO $(SDL_URL_WIN)
endif
	