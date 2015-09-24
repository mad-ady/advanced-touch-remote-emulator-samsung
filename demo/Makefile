LIB = ..

CFLAGS = -Wall -ggdb -O2 -I$(LIB)/
LDFLAGS = -static -L$(LIB)/ -luinput

DEMOS := keyboard_demo inject_samsung_remote

all: demo

demo: $(DEMOS)

%: %.c $(LIB)/libuinput.a
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(DEMOS) *.o *~

.PHONY: all, clean
