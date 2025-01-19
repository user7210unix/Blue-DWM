# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = nfetch

# Directories
BINDIR = /bin/
SRCDIR = .
OBJDIR = build/

# Source files
SRCS = $(wildcard $(SRCDIR)/get_data/*.c) $(SRCDIR)/main.c
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Version and color codes
APPVER = 0.4.3
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
RESET=\033[0m

# Default target
all: $(TARGET)
	@echo -e ""
	@echo -e "${GREEN} [✓] - Complete"
	@echo -e ""
	@echo -e "${RED}"
	@echo -e "   ▄   ▄████  ▄███▄     ▄▄▄▄▀ ▄█▄     ▄  █ "
	@echo -e "    █  █▀   ▀ █▀   ▀ ▀▀▀ █    █▀ ▀▄  █   █ "
	@echo -e "██   █ █▀▀    ██▄▄       █    █   ▀  ██▀▀█ "
	@echo -e "█ █  █ █      █▄   ▄▀   █     █▄  ▄▀ █   █ "
	@echo -e "█  █ █  █     ▀███▀    ▀      ▀███▀     █  "
	@echo -e "█   ██   ▀                             ▀   "
	@echo -e "                                           "
	@echo -e "${YELLOW}          🗲 Created by Nighty3098"
	@echo -e "${YELLOW}        https://nighty3098.github.io/"

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)  # Create the directory for the object file if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo -e ""
	@echo -e "${GREEN} [✓] - Complete"
	@echo -e ""
	@echo -e "${RED}"
	@echo -e "   ▄   ▄████  ▄███▄     ▄▄▄▄▀ ▄█▄     ▄  █ "
	@echo -e "    █  █▀   ▀ █▀   ▀ ▀▀▀ █    █▀ ▀▄  █   █ "
	@echo -e "██   █ █▀▀    ██▄▄       █    █   ▀  ██▀▀█ "
	@echo -e "█ █  █ █      █▄   ▄▀   █     █▄  ▄▀ █   █ "
	@echo -e "█  █ █  █     ▀███▀    ▀      ▀███▀     █  "
	@echo -e "█   ██   ▀                             ▀   "
	@echo -e "                                           "
	@echo -e "${YELLOW}          🗲 Created by Nighty3098"
	@echo -e "${YELLOW}        https://nighty3098.github.io/"

# Install the executable
install:
	sudo cp $(TARGET) $(BINDIR)
	@echo -e ""
	@echo -e "${GREEN} [✓] - Complete"
	@echo -e ""
	@echo -e "${RED}"
	@echo -e "   ▄   ▄████  ▄███▄     ▄▄▄▄▀ ▄█▄     ▄  █ "
	@echo -e "    █  █▀   ▀ █▀   ▀ ▀▀▀ █    █▀ ▀▄  █   █ "
	@echo -e "██   █ █▀▀    ██▄▄       █    █   ▀  ██▀▀█ "
	@echo -e "█ █  █ █      █▄   ▄▀   █     █▄  ▄▀ █   █ "
	@echo -e "█  █ █  █     ▀███▀    ▀      ▀███▀     █  "
	@echo -e "█   ██   ▀                             ▀   "
	@echo -e "                                           "
	@echo -e "${YELLOW}          🗲 Created by Nighty3098"
	@echo -e "${YELLOW}        https://nighty3098.github.io/"
