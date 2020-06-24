CC = g++
SDIR = src
ODIR = out
TARGET = sfml-app
CPPFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast -std=gnu++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

sources := $(wildcard $(SDIR)/*/*.cpp $(SDIR)/*.cpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(call sources))

all: clean $(ODIR) $(call objects) link

run: all
	./$(TARGET)

.PHONY: $(ODIR)

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
