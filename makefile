default=\033[0m
red=\033[0;31m
brown=\033[0;33m
blue=\033[0;34m
purple=\033[0;35m
lightRed=\033[1;31m
lightGreen=\033[1;32m
yellow=\033[1;33m
redBackground=\033[41;1;37m
yellowBackground=\033[43;1;37m
blueBackground=\033[44;1;37m
purpleBackground=\033[45;1;37m

BIN_NAME=trab1
ARG1=./input/pr1002.tsp

C_SOURCE=$(wildcard ./source/*.c)
H_SOURCE=$(wildcard ./include/*.h)

OBJ=$(subst .c,.o,$(subst source,object,$(C_SOURCE)))

CPL=gcc

CPL_FLAGS=-c   \
          -lm  \
          -W   \
          -Wall


VALGRIND_FLAGS=-s \
           --leak-check=full \
           --show-leak-kinds=all \
           --show-reachable=yes \
           --track-origins=yes \
           --verbose



run: all
	@ ./${BIN_NAME} ${ARG1}


valgrind: all
	@ clear
	@ valgrind ${VALGRIND_FLAGS} ./${BIN_NAME} ${ARG1}


assembly: all
	@ gcc -E ./source/main.c > ./object/precomp_code.i
	@ gcc -S ./object/precomp_code.i -o ./object/assembly_code.s


all: objectFolder ./${BIN_NAME}
	@ echo " ${lightGreen}  Done!  ${default} "
	@ echo ''


objectFolder:
	@ mkdir -p object output


./${BIN_NAME}: ${OBJ}
	@ ${CPL} $^ -o $@ -lm
	@ echo " ${brown}  Building Binary ${yellowBackground}$@${default}${brown}  ${default} "
	@ echo ''


./object/%.o: ./source/%.c ./include/%.h
	@ ${CPL} $< -o $@ -I ./include ${CPL_FLAGS}
	@ echo " ${purple}  Generating compilation object ${purpleBackground}$@${default}${purple}  ${default} "
	@ echo ''


./object/main.o: ./source/main.c ${H_SOURCE}
	@ ${CPL} $< -o $@ -I ./include ${CPL_FLAGS}
	@ echo " ${blue}  Generating compilation object ${blueBackground}$@${default}${blue}  ${default} "
	@ echo ''


clean:
	@ rm -rf ./object/*.o ./object/*.i ./object/*.s ./output/ *~ ./${BIN_NAME}
	@ rmdir object
	@ echo " ${lightRed}  Removing binary ${redBackground}./${BIN_NAME}${default}${lightRed} and compilation objects ${redBackground}${OBJ}${default}${lightRed} and output files  ${default} "
	@ echo ''
