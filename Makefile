include Makefile.inc

SOURCES_FOLDER=src
OUTPUT_FOLDER=bin
INCLUDE_FOLDER=$(SOURCES_FOLDER)/include

SOURCES_CLIENT=$(SOURCES_FOLDER)/client.c  
SOURCES_SERVER=$(filter-out $(SOURCES_CLIENT),$(wildcard $(SOURCES_FOLDER)/*.c))
SOURCES_ASM=$(wildcard src/*.asm)

OBJECTS_SERVER=$(SOURCES_SERVER:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

OUTPUT_SERVER=$(OUTPUT_FOLDER)/server
OUTPUT_CLIENT=$(OUTPUT_FOLDER)/client

all: $(OUTPUT_SERVER) $(OUTPUT_CLIENT)

$(OUTPUT_SERVER): $(OBJECTS_SERVER) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -I$(INCLUDE_FOLDER) -o $@ $^ -lm -no-pie
	@echo too_easy >> $(OUTPUT_SERVER)

$(OUTPUT_CLIENT): $(SOURCES_CLIENT) 
	$(GCC) $(GCCFLAGS) -I$(INCLUDE_FOLDER) $^ -o $@

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

install:
	mkdir -p $(OUTPUT_FOLDER)

clean:
	rm -rf $(OUTPUT_FOLDER)/*
	rm -rf $(SOURCES_FOLDER)/*.o

pvs:
	pvs-studio-analyzer trace -- make
	pvs-studio-analyzer analyze
	plog-converter -a '64:1,2,3;GA:1,2,3;OP:1,2,3' -t tasklist -o report.tasks PVS-Studio.log

.PHONY: all clean install pvs