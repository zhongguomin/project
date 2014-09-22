
.PHONY : all clean cleanobj

objects = main.o kbd.o command.o display.o \
	insert.o search.o files.o utils.o
export var_1 = hello


all : edit main_2 subsystem

edit : $(objects)
	cc -o edit $(objects)

main_2 : main_2.o
	cc -o main_2 main_2.o
	@echo This is test debug output
	@echo var_1 = $(var_1)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

main_2 : main_2.c

subsystem:
	cd subdir &&  make


clean : cleanobj subclean
	-rm edit main_2

cleanobj:
	-rm -rf *.o

subclean:
	cd subdir && make clean

