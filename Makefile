
SOS:
	./build/sos_project

clean:
	rm -rf build

build: clean
	mkdir build &&\
	cd build &&\
	cmake .. &&\
	make &&\
	cd ..