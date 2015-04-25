# project name (generate executable with this name)
TARGET   = touche-coule

CC       = g++
# compiling flags here
CFLAGS   = -w -Wall -Isrc/inc/

LINKER   = g++ -o
# linking flags here
LFLAGS   = -Wall -I.
SDLFLAG  = -lncurses -Wl,-rpath=/usr/local/lib

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/inc/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(SDLFLAG)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
fclean: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

re: fclean all
