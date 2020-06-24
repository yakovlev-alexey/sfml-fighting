CC = g++
SDIR = src
ODIR = out
APPNAME = sfml-app
CPPFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers -Wold-style-cast -std=gnu++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

sources := $(wildcard $(SDIR)/*/*.cpp $(SDIR)/*.cpp)
objects := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o, $(call sources))

all: clean $(ODIR) $(call objects) link

.PHONY: $(ODIR)

$(ODIR):
	@mkdir $(ODIR)

$(objects): $(ODIR)/%.o : $(SDIR)/%.cpp
	$(if $(SILENT),,@echo [C++] $<)
	@$(CC) $(CPPFLAGS) -c $< -o $@

link:
	$(if $(SILENT),,@echo [LINK] $(call objects))
	@$(CC) $(call objects) -o $(APPNAME) $(SFMLFLAGS)

clean: 
	rm -rf -f out
	rm -f $(APPNAME)
