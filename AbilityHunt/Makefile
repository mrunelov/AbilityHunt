TARGETNAME 	= AHunt

# Main Compiler
CC = g++ 
CFLAGS = -g -std=c++11
SRCEXT = cpp

# Directories
SRCDIR 		= src
BUILDDIR 	= build
BINDIR 		= bin

TARGET = $(BINDIR)/$(TARGETNAME)
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
INCLUDE = 

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p "$(shell dirname $@)"
	@echo " $(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<"; $(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo "  rm $(shell find $(BUILDDIR)/ -type f -delete -print)"
	@echo "  $(RM) $(TARGET)"
	@echo " .. done!"

.PHONY: clean