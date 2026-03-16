all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm -o origin.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c -lSDL2 -lSDL2_image -lGL -lm -o origin -Wall -Wextra -Wpedantic

mac:
	gcc -Iinclude/ -I/opt/homebrew/include $(shell sdl2-config --cflags) -DGL_SILENCE_DEPRECATION \
	src/*.c -o origin \
	$(shell sdl2-config --libs) -L/opt/homebrew/lib -lSDL2_image -framework OpenGL -lm