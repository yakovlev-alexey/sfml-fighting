CC = g++
CPPFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast -std=gnu++14
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DLIBS = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d

SDIR = src
IDIR = inc
ODIR = out
DATADIR = data
DISTDIR = dist

TARGET = $(ODIR)/sfml-app

sources := $(wildcard $(SDIR)/**/*.cpp $(SDIR)/*.cpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(call sources))

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
	@$(CC) $(CPPFLAGS) -I./$(IDIR) -c $< -o $@ -O4

link:
	$(if $(SILENT),,@echo [LINK] $(call objects))
	@$(CC) $(call objects) -o $(TARGET) $(LIBS)

debug:
	$(if $(SILENT),,@echo [LINK] $(call objects))
	@$(CC) $(call objects) -o $(TARGET) $(DLIBS)

clean: 
	rm -rf -f out
	rm -f $(TARGET)

.PHONY: all run $(DISTDIR) link clean
