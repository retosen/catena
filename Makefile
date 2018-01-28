
all: blake2s

blake2s:
	cd src; make $@; cd

clean:
	cd src;	make clean; cd ..
	rm -f *~ catena-Dragonfly-blake2s-test
	rm -f catena-Butterfly-blake2s-test
	rm -f catena-Dragonfly-blake2s-test_vectors
	rm -f catena-Butterfly-blake2s-test_vectors
