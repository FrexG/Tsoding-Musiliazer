CC := clang 
CFLAGS := -Wall -Wextra `pkg-config --cflags raylib` -g

LIBS := `pkg-config --libs --cflags raylib` -lm 

SRC := main.c
OBJS := main.o
MAIN := main
DLIB := plug.c
PLUG := libplug.so

all: $(MAIN)

$(PLUG):$(DLIB)
	$(CC) $(CFLAGS) -fPIC -shared -o $(PLUG) $(DLIB) $(LIBS)

$(MAIN):$(OBJS) $(PLUG)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS) 

$(OBJS):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(MAIN) $(PLUG)
