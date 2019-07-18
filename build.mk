OBJ_PATH=$(PATH)/obj
echo = /bin/echo
make=/usr/bin/make
rm=/bin/rm


SRC=$(shell /usr/bin/find $(PATH)/src -name "*.cpp" -type f)
OBJ=$(patsubst $(PATH)/src/%.cpp, $(OBJ_PATH)/%.o, $(SRC))

INCLUDE_PATHS += $(PATH)/include

INCLUDE=$(addprefix -I, $(INCLUDE_PATHS))

FLAGS= -std=c++11 #-Wextra -Wall -Werror
GCC=/usr/bin/clang++

make: info $(OBJ_PATH) $(OBJ) $(NAME)
	
info:
	@$(echo) "#### INFO ####"
	@$(echo) path: $(PATH)
	@$(echo) object path: $(OBJ_PATH)
	@$(echo) SRC: $(SRC)
	@$(echo) Includes: $(INCLUDE)
	@$(echo) "#############"

$(OBJ_PATH)/%.o : $(PATH)/src/%.cpp
	@$(echo) "$@ >> $< "
	@$(GCC) $< -o $@ $(INCLUDE) -c $(FLAGS)

$(OBJ_PATH):
	@/bin/mkdir $(OBJ_PATH)

clean:
	@$(rm) -r $(OBJ_PATH)

fclean: clean
	@$(rm) $(NAME)

re: fclean make