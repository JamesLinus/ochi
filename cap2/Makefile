
.PHONY: default

default: cap

OBJ := cap.o
CFLAGS := 

LIBS := -L /usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_videoio
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc

%.o: %.cpp
	g++ -c -o $@ $(CFLAGS) $<

cap: $(OBJ)
	g++ $(OBJ) $(LIBS) -o $@
