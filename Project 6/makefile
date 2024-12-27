carBase: mainA3.o addNewCar.o printAll.o loadCarData.o noMoreCars.o printOne.o lookForCarId.o lookForCarModelType.o countCars.o sortCarId.o oneLessCar.o
	gcc -Wall -std=c99 mainA3.o addNewCar.o printAll.o loadCarData.o noMoreCars.o printOne.o lookForCarId.o lookForCarModelType.o countCars.o sortCarId.o oneLessCar.o -o carBase

mainA3.o: mainA3.c headerA3.h
	gcc -Wall -std=c99 -cmainA3.c -o mainA3.o

addNewCar.o: addNewCar.c headerA3.h
	gcc -Wall -std=c99 -caddNewCar.c -o addNewCar.o

loadCarData.o: loadCarData.c headerA3.h
	gcc -Wall -std=c99 -cloadCarData.c -o loadCarData.o 

printAll.o: printAll.c headerA3.h
	gcc -Wall -std=c99 -cprintAll.c -o printAll.o 

noMoreCars.o: noMoreCars.c headerA3.h
	gcc -Wall -std=c99 -cnoMoreCars.c -o noMoreCars.o

printOne.o: printOne.c headerA3.h
	gcc -Wall -std=c99 -cprintOne.c -o printOne.o

lookForCarId.o: lookForCarId.c headerA3.h
	gcc -Wall -std=c99 -clookForCarId.c -o lookForCarId.o

lookForCarModelType.o: lookForCarModelType.c headerA3.h
	gcc -Wall -std=c99 -clookForCarModelType.c -o lookForCarModelType.o

countCars.o: countCars.c headerA3.h
	gcc -Wall -std=c99 -ccountCars.c -o countCars.o

sortCarId.o: sortCarId.c headerA3.h
	gcc -Wall -std=c99 -csortCarId.c -o sortCarId.o

oneLessCar.o: oneLessCar.c headerA3.h
	gcc -Wall -std=c99 -coneLessCar.c -o oneLessCar.o

clean: 
	rm -f *.o carBase
