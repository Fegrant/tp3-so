include Makefile.inc

SOURCES=$(wildcard $(SOURCES_FOLDER)/*.c)

SOURCES_FOLDER=src
OUTPUT_FOLDER=bin
INCLUDE_FOLDER=$(SOURCES_FOLDER)/include

OUTPUT_SERVER=$(OUTPUT_FOLDER)/server

all: $(OUTPUT_SERVER)

$(OUTPUT_SERVER): $(SOURCES)
	$(GCC) $(GCCFLAGS) -I$(INCLUDE_FOLDER) $^ -o $@

install:
	mkdir -p $(OUTPUT_FOLDER)

clean:
	rm -rf $(OUTPUT_FOLDER)/*

.PHONY: all clean install