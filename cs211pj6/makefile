proj6Base : proj6Base.o Point3d.o PointSet.o Polygon.o
	g++ -o proj6Base proj6Base.o Point3d.o PointSet.o Polygon.o

proj6Base.o : proj6Base.cpp Point3d.h PointSet.h Polygon.h
	g++ -g -c proj6Base.cpp

Point3d.o : Point3d.cpp Point3d.h
	g++ -g -c Point3d.cpp

PointSet.o : PointSet.cpp PointSet.h Point3d.h
	g++ -g -c PointSet.cpp

Polygon.o : Polygon.cpp PointSet.h Polygon.h Point3d.h
	g++ -g -c Polygon.cpp

.cpp.o :
	g++ -g -c $<

Debug : proj6Base.cpp Point3d.cpp PointSet.cpp Polygon.cpp
	g++ -o proj6BaseDebug -g -DDEBUG proj6Base.cpp Point3d.cpp PointSet.cpp Polygon.cpp

clean :
	rm *.o core

