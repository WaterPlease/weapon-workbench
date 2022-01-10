CXX             = g++ 
SRCS            = $(wildcard *.cpp) $(wildcard *.c)
OBJS            = $(SRCS:.cpp=.o)
TARGET          = out.exe
LIBS            = -lglfw3 -lgdi32 -lopengl32
LIB_DIRS        = -L./lib
INC             = -I./include
 
all : $(TARGET)
	$(CXX) -g -o $(TARGET) $(OBJS) $(INC) $(LIB_DIRS) $(LIBS)
	del -f *.o

$(TARGET) :
	$(CXX) -g -c $(SRCS) $(INC) $(LIB_DIRS) $(LIBS)

clean :
	del -f $(TARGET)
	del -f *.o