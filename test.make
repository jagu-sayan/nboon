# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.make                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/12 19:17:25 by jzak              #+#    #+#              #
#    Updated: 2014/03/12 19:17:25 by jzak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),release)
  OBJDIR     = bin/obj/Release/test
  TARGETDIR  = bin
  TARGET     = $(TARGETDIR)/test
  DEFINES   += 
  INCLUDES  += -Iincludes
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -Wall -Wextra -Werror
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x -Lbin
  LIBS      += -lnboon
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += bin/libnboon.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) \
			   $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = bin/obj/Debug/test
  TARGETDIR  = bin
  TARGET     = $(TARGETDIR)/test
  DEFINES   += 
  INCLUDES  += -Iincludes
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -Wall -Wextra
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Lbin
  LIBS      += -lnboon
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += bin/libnboon.a
  LINKCMD    = $(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) \
			   $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

NAME = test

OBJECTS := \
	$(OBJDIR)/main.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking test
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

$(NAME): all

clean:
	@echo Cleaning test
	$(SILENT) rm -rf $(OBJDIR)

fclean: clean
	@echo Remove $(TARGET)
	$(SILENT) rm -f $(TARGET)

re: fclean all

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/main.o: test/main.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
