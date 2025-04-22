all: runB runC runD

runB: revenue_pb.cpp
	g++ revenue_pb.cpp -o runB

runC: revenue_pc.cpp
	g++ revenue_pc.cpp -o runC

runD: revenue_pd.cpp
	g++ revenue_pd.cpp -o runD

clean:
	rm -f run