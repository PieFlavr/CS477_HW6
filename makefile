all:
	g++ revenue_pb.cpp -o run

clean:
	rm -f run