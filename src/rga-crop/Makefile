SRC:=main.cpp
OUT:=main

CXXFLAGS+=-lrga

INCLUDE_IM2D:=../../include/im2d/
INCLUDE_RGA:=../../include/rga/
INCLUDE_DMA:=../../include/dma/
INCLUDE_BMP:=../../include/bmp/

SRC_DMA:=$(wildcard $(INCLUDE_DMA)*.cpp)
SRC_BMP:=$(wildcard $(INCLUDE_BMP)*.cpp)

OBJS:=$(SRC:.cpp=.o) $(SRC_BMP:.cpp=.o) $(SRC_DMA:.cpp=.o)

default: $(OUT)

$(OUT): $(OBJS)
	$(CC) -Wall -Wextra \
	-I $(INCLUDE_IM2D) \
	-I $(INCLUDE_RGA) \
	-I $(INCLUDE_DMA) \
	-I $(INCLUDE_BMP) \
	$(OBJS) -o $(OUT) $(CXXFLAGS)

%.o: %.cpp
	$(CC) -Wall -Wextra \
	-I $(INCLUDE_RGA) \
	-c $< -o $@

clean:
	rm -rf $(OUT) $(OBJS)
