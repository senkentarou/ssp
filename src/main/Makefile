#
# Makefile for main and requires
#

COMPILER  := g++
CPPFLAGS  := -Wall -std=c++11
INCLUDE   := -I../lib

LIBDIR    := ../lib
OBJDIR    := ../obj
MAINDIR   := ./
BINDIR    := ../bin

MAIN      := main.cpp
TARGET    := a.out
LIBSRC    := $(wildcard $(LIBDIR)/*.cpp)
LIBOBJ    := $(subst $(LIBDIR), $(OBJDIR), $(LIBSRC:.cpp=.o))
MAINSRC   := $(addprefix $(MAINDIR)/, $(MAIN))
MAINOBJ   := $(subst $(MAINDIR), $(OBJDIR), $(MAINSRC:.cpp=.o))

TARGETBIN := $(addprefix $(BINDIR)/, $(TARGET))
OBJECTS   := $(LIBOBJ) $(MAINOBJ)

.PHONY: all clean

all: $(OBJDIR) $(BINDIR) $(TARGETBIN)

$(OBJDIR):
	@if [ ! -d $@ ]; \
		then echo "mkdir -p $@"; mkdir -p $@; \
	fi

$(BINDIR):
	@if [ ! -d $@ ]; \
		then echo "mkdir -p $@"; mkdir -p $@; \
	fi

$(TARGETBIN): $(OBJECTS)
	$(COMPILER) $(CPPFLAGS) -o $@ $^

$(MAINOBJ): $(MAIN)
	$(COMPILER) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	$(COMPILER) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)
