all:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -o pong.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c -lSDL2 -lGL -lm -o pong -Wall -Wextra -Wpedantic

mac:
	gcc -Iinclude/ -I/opt/homebrew/include $(shell sdl2-config --cflags) -DGL_SILENCE_DEPRECATION \
	src/*.c -o pong \
	$(shell sdl2-config --libs) -L/opt/homebrew/lib -lSDL2_image -framework OpenGL -lm