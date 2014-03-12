# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    nboon.make                                         :+:      :+:    :+:    #
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
  OBJDIR     = bin/obj/Release/nboon
  TARGETDIR  = bin
  TARGET     = $(TARGETDIR)/libnboon.a
  DEFINES   += 
  INCLUDES  += -Iincludes
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -Wall -Wextra -Werror
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -Wl,-x
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR     = bin/obj/Debug/nboon
  TARGETDIR  = bin
  TARGET     = $(TARGETDIR)/libnboon.a
  DEFINES   += 
  INCLUDES  += -Iincludes
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -Wall -Wextra
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += 
  LIBS      += 
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += 
  LINKCMD    = $(AR) -rcs $(TARGET) $(OBJECTS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

NAME = nboon

OBJECTS := \
	$(OBJDIR)/completion.o \
	$(OBJDIR)/evt.o \
	$(OBJDIR)/history.o \
	$(OBJDIR)/history_file.o \
	$(OBJDIR)/lib.o \
	$(OBJDIR)/mode.o \
	$(OBJDIR)/nboon.o \
	$(OBJDIR)/refresh.o \
	$(OBJDIR)/unicode.o \
	$(OBJDIR)/backspace.o \
	$(OBJDIR)/ctrl_a.o \
	$(OBJDIR)/ctrl_e.o \
	$(OBJDIR)/ctrl_k.o \
	$(OBJDIR)/ctrl_l.o \
	$(OBJDIR)/ctrl_n.o \
	$(OBJDIR)/ctrl_p.o \
	$(OBJDIR)/ctrl_t.o \
	$(OBJDIR)/ctrl_u.o \
	$(OBJDIR)/ctrl_w.o \
	$(OBJDIR)/delete.o \
	$(OBJDIR)/move_left.o \
	$(OBJDIR)/move_right.o \

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
	@echo Linking nboon
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
	@echo Cleaning nboon
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

$(OBJDIR)/completion.o: srcs/completion.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/evt.o: srcs/evt.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/history.o: srcs/history.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/history_file.o: srcs/history_file.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/lib.o: srcs/lib.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/mode.o: srcs/mode.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/nboon.o: srcs/nboon.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/refresh.o: srcs/refresh.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/unicode.o: srcs/unicode.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/backspace.o: srcs/evt/backspace.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_a.o: srcs/evt/ctrl_a.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_e.o: srcs/evt/ctrl_e.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_k.o: srcs/evt/ctrl_k.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_l.o: srcs/evt/ctrl_l.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_n.o: srcs/evt/ctrl_n.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_p.o: srcs/evt/ctrl_p.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_t.o: srcs/evt/ctrl_t.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_u.o: srcs/evt/ctrl_u.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ctrl_w.o: srcs/evt/ctrl_w.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/delete.o: srcs/evt/delete.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/move_left.o: srcs/evt/move_left.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"
$(OBJDIR)/move_right.o: srcs/evt/move_right.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(CFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
