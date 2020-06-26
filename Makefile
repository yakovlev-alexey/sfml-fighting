CC = g++
CPPFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast -std=gnu++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SDIR = src
IDIR = inc
ODIR = out
DATADIR = data
DISTDIR = dist

TARGET = $(ODIR)/sfml-app

sources := $(wildcard $(SDIR)/**/*.cpp $(SDIR)/*.cpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(call sources))

uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))

headers := $(foreach d,$(call uniq,$(dir $(call sources))), $(patsubst $(SDIR)/%, -I./$(IDIR)/%, $(d)))

all: clean $(call objects) link

run: $(call objects) link
	./$(TARGET)

$(DISTDIR): all
	rm -rf -f $(DISTDIR)
	mkdir $(DISTDIR)
	cp -r $(DATADIR) $(DISTDIR)
	cp $(TARGET) $(DISTDIR)

$(objects): $(ODIR)/%.o : $(SDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(if $(SILENT),,@echo [C++] $<)
	@$(CC) $(CPPFLAGS) $(call headers) -c $< -o $@ -O4

link:
	$(if $(SILENT),,@echo [LINK] $(call objects))
	@$(CC) $(call objects) -o $(TARGET) $(SFMLFLAGS)

clean: 
	rm -rf -f out
	rm -f $(TARGET)

.PHONY: all run $(DISTDIR) link clean
