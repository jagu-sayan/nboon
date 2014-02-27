# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jzak </var/mail/jzak>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/27 19:27:54 by jzak              #+#    #+#              #
#    Updated: 2014/02/27 19:27:54 by jzak             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = all

ifndef config
  config=release
endif
export config

PROJECTS := nboon test

.PHONY: all clean help $(PROJECTS)

$(NAME): $(PROJECTS)

nboon: 
	@echo "==== Building nboon ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f nboon.make

test: nboon
	@echo "==== Building test ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f test.make

clean:
	@${MAKE} --no-print-directory -C . -f nboon.make clean
	@${MAKE} --no-print-directory -C . -f test.make clean

fclean:
	@${MAKE} --no-print-directory -C . -f nboon.make fclean
	@${MAKE} --no-print-directory -C . -f test.make fclean

re:
	@${MAKE} --no-print-directory -C . -f nboon.make re
	@${MAKE} --no-print-directory -C . -f test.make re

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   release"
	@echo "   debug"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   fclean"
	@echo "   re"
	@echo "   nboon"
	@echo "   test"
	@echo ""
	@echo "For more information :"
	@echo "https://github.com/jagu-sayan/42Premake"
