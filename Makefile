CC = g++
CPPFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast -std=gnu++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SDIR = src
ODIR = out
DATADIR = data
DISTDIR = dist

TARGET = $(ODIR)/sfml-app

sources := $(wildcard $(SDIR)/**/*.cpp $(SDIR)/*.cpp)
headers := $(wildcard $(SDIR)/**/*.hpp $(SDIR)/*.hpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(call sources))

all: clean $(ODIR) $(call objects) link

run: $(call objects) link
	./$(TARGET)

.PHONY: $(ODIR) $(DISTDIR)

$(DISTDIR): all
	rm -rf -f $(DISTDIR)
	mkdir $(DISTDIR)
	cp -r $(DATADIR) $(DISTDIR)
	cp $(TARGET) $(DISTDIR)

$(ODIR):
	@mkdir $(ODIR)

$(objects): $(ODIR)/%.o : $(SDIR)/%.cpp
	$(if $(SILENT),,@echo [C++] $<)
	@$(CC) $(CPPFLAGS) -c $< -o $@ -O4

link:
	$(if $(SILENT),,@echo [LINK] $(call objects))
	@$(CC) $(call objects) -o $(TARGET) $(SFMLFLAGS)

clean: 
	rm -rf -f out
	rm -f $(TARGET)
