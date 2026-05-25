# Force Make to use bash so 'source' works correctly
SHELL := /bin/bash

# Source files (shared across all platforms)
SRCS = src/main.c src/cat.c src/player.c src/game.c src/audio.c

# Common flags
CFLAGS_COMMON = -Wall -Isrc

# macOS Configurations
MAC_CC = clang
MAC_DIR = dist
MAC_TARGET = $(MAC_DIR)/clickthecat-macos
MAC_CFLAGS = $(CFLAGS_COMMON) -I/Volumes/Repos/ClickTheCat/raylib-6.0_macos/include
MAC_LIBS = /Volumes/Repos/ClickTheCat/raylib-6.0_macos/lib/libraylib.a
MAC_FRAMEWORKS = -framework CoreVideo -framework CoreAudio -framework AudioToolbox \
                 -framework AVFoundation -framework OpenAL -framework IOKit \
                 -framework Cocoa -framework GLUT -framework OpenGL

# Windows Configurations
WIN_CC = x86_64-w64-mingw32-gcc
WIN_DIR = dist
WIN_TARGET = $(WIN_DIR)/clickthecat.exe
WIN_CFLAGS = $(CFLAGS_COMMON) -I/Volumes/Repos/ClickTheCat/raylib-6.0_win64_mingw-w64/include
WIN_LIBS = /Volumes/Repos/ClickTheCat/raylib-6.0_win64_mingw-w64/lib/libraylib.a \
           -lwinmm -lgdi32 -lopengl32 -lcomdlg32 -lole32

# Web Configurations
WEB_CC = emcc
WEB_DIR = dist/web
WEB_TARGET = $(WEB_DIR)/ctc.html
WEB_CFLAGS = $(CFLAGS_COMMON) -I/Volumes/Repos/ClickTheCat/raylib-web/include
WEB_LIBS = -L/Volumes/Repos/ClickTheCat/raylib-web/lib -lraylib
WEB_FLAGS = --shell-file /Volumes/AppleSeed/MacOS/cieloforge/dev/raylib/raylib/src/shell.html \
            -s USE_GLFW=3 -s ASYNCIFY --preload-file src -s TOTAL_MEMORY=33554432

# Default rule builds everything
all: macos windows web

# --- macOS Build Rule ---
macos: $(MAC_TARGET)

$(MAC_TARGET): $(SRCS)
	@mkdir -p $(MAC_DIR)
	$(MAC_CC) $(MAC_CFLAGS) $(SRCS) $(MAC_LIBS) $(MAC_FRAMEWORKS) -o $(MAC_TARGET)

# --- Windows Build Rule ---
windows: $(WIN_TARGET)

$(WIN_TARGET): $(SRCS)
	@mkdir -p $(WIN_DIR)
	$(WIN_CC) $(WIN_CFLAGS) $(SRCS) $(WIN_LIBS) -o $(WIN_TARGET)

# --- Web Build Rule ---
web: $(WEB_TARGET)

$(WEB_TARGET): $(SRCS)
	@mkdir -p $(WEB_DIR)
	source ~/dev/emsdk/emsdk_env.sh && emsdk activate latest && $(WEB_CC) $(SRCS) $(WEB_CFLAGS) $(WEB_LIBS) $(WEB_FLAGS) -o $(WEB_TARGET)

# --- Clean Build Artifacts ---
clean:
	rm -rf $(MAC_DIR) $(WIN_DIR)

# --- Case Insensitivity Shortcuts (Fixed) ---
macOS:
	$(MAKE) macos

Windows:
	$(MAKE) windows

Web:
	$(MAKE) web

.PHONY: all macos windows web clean macOS Windows Web

