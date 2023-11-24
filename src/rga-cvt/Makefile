CXXFLAGS+=-l:librga.so.2

INCLUDE_IM2D:=../../libs/im2d/include/
INCLUDE_RGA:=../../libs/rga/include/
INCLUDE_DMA:=../../libs/dma/
INCLUDE_BMP:=../../libs/bmp/

SRC_DMA:=$(wildcard $(INCLUDE_DMA)*.cpp)
SRC_BMP:=$(wildcard $(INCLUDE_BMP)*.cpp)

SRC:=main.cpp
OUT:=main

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
