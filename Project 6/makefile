bin/carBase: mainA3.o addNewCar.o printAll.o loadCarData.o noMoreCars.o printOne.o lookForCarId.o lookForCarModelType.o countCars.o sortCarId.o oneLessCar.o
	gcc -Wall -std=c99 mainA3.o addNewCar.o printAll.o loadCarData.o noMoreCars.o printOne.o lookForCarId.o lookForCarModelType.o countCars.o sortCarId.o oneLessCar.o -o bin/carBase

mainA3.o: src/mainA3.c include/headerA3.h
	gcc -Wall -std=c99 -c src/mainA3.c -o mainA3.o

addNewCar.o: src/addNewCar.c include/headerA3.h
	gcc -Wall -std=c99 -c src/addNewCar.c -o addNewCar.o

loadCarData.o: src/loadCarData.c include/headerA3.h
	gcc -Wall -std=c99 -c src/loadCarData.c -o loadCarData.o 

printAll.o: src/printAll.c include/headerA3.h
	gcc -Wall -std=c99 -c src/printAll.c -o printAll.o 

noMoreCars.o: src/noMoreCars.c include/headerA3.h
	gcc -Wall -std=c99 -c src/noMoreCars.c -o noMoreCars.o

printOne.o: src/printOne.c include/headerA3.h
	gcc -Wall -std=c99 -c src/printOne.c -o printOne.o

lookForCarId.o: src/lookForCarId.c include/headerA3.h
	gcc -Wall -std=c99 -c src/lookForCarId.c -o lookForCarId.o

lookForCarModelType.o: src/lookForCarModelType.c include/headerA3.h
	gcc -Wall -std=c99 -c src/lookForCarModelType.c -o lookForCarModelType.o

countCars.o: src/countCars.c include/headerA3.h
	gcc -Wall -std=c99 -c src/countCars.c -o countCars.o

sortCarId.o: src/sortCarId.c include/headerA3.h
	gcc -Wall -std=c99 -c src/sortCarId.c -o sortCarId.o

oneLessCar.o: src/oneLessCar.c include/headerA3.h
	gcc -Wall -std=c99 -c src/oneLessCar.c -o oneLessCar.o

clean: 
	rm -f *.o bin/carBase