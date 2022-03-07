OBJS = SlabWiseBillCalculator.o main.o ApartmentWaterBillCalculator.o

%.o : %.cpp
	g++ -c -std=c++11 $< 

all: $(OBJS)
	g++ $(OBJS) -o bill_calc

clean:
	rm *.o bill_calc
