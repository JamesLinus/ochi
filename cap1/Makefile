
.PHONY: default

default: cap

OBJ := cap.o
CFLAGS :=
LIBS := -lgphoto2

%.o: %.c
	gcc -c -o $@ $(CFLAGS) $<

cap: $(OBJ)
	gcc -o $@ $(OBJ) $(LIBS)
