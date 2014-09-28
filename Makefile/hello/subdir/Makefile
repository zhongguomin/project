define run-cmd
@echo test cmd run ... $@  -- $^
endef


main_3 : main_3.o
	cc -o main_3 main_3.o
	$(run-cmd)
	@echo make level $(MAKELEVEL)

main_3.o : main_3.c
	cc -c main_3.c
	@echo var_1 = $(var_1)

.PHONY : clean

clean:
	-rm -rf main_3 *.o


