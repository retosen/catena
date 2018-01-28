CC=clang
TARGETDIR=../

CFLAGS=-fomit-frame-pointer -O3 -std=c99 -fgnu89-inline -march=native -s -W -Wall

#Silence the warnings from blake2s
CFLAGS+= -Wno-unused-function -Wno-unused-const-variable

BASEFILES = catena.c catena-helpers.c

#Determine if SSE2 or greater is available
SSE_TAGS = $(shell /bin/grep -m 1 flags /proc/cpuinfo | /bin/grep -o \
	'sse2\|sse3\|ssse3\|sse4a\|sse4.1\|sse4.2' | sed  's/\_/./g')

ifneq (${SSE_TAGS},)
    #Choose optimized hash function
    HDIR=./blake2-sse
    CFLAGS += -L$(HDIR) -I$(HDIR)
	HASH=$(HDIR)/blake2s.c
	HASHIMPL = catena-blake2s-sse.c
else
	#use reference implementation
    HDIR=./blake2-ref
    CFLAGS += -L$(HDIR) -I$(HDIR)
	HASH=$(HDIR)/blake2s-ref.c
	HASHIMPL = catena-blake2s-ref.c
endif

#if requested use the full hash function for H' instead of single rounds
ifndef FULLHASH
	CFLAGS += -DFAST
endif

#if requested enable password overwriting and inform the user
ifdef SAFE

CFLAGS += -DOVERWRITE

$(warning )
$(warning Password overwriting is enabled. Please make sure the password)
$(warning resides in a writeable part of the heap.)
$(warning The PHS interface is not avaiable with this setting.)
$(warning )

else

$(warning )
$(warning )
$(warning WARNING: PASSWORD OVERWRITING IS DISABLED)
$(warning We strongly advise against doing this in a productive enviroment.)
$(warning To enable password overwriting build with SAFE=1)
$(warning )
$(warning )

endif


.PHONY: all blake2s Butterfly Dragonfly clean

all: blake2s

blake2s: Butterfly-blake2s Dragonfly-blake2s

Butterfly: Butterfly-blake2s
Dragonfly: Dragonfly-blake2s

Butterfly-blake2s: catena-Butterfly-blake2s-test catena-Butterfly-blake2s-test_vectors
Dragonfly-blake2s: catena-Dragonfly-blake2s-test catena-Dragonfly-blake2s-test_vectors


catena-Butterfly-blake2s-test:
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$@ test-catena.c $(BASEFILES) $(HASHIMPL) catena-DBG.c $(HASH)

catena-Butterfly-blake2s-test_vectors:
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$@ catena_test_vectors.c $(BASEFILES) $(HASHIMPL) catena-DBG.c $(HASH)


catena-Dragonfly-blake2s-test:
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$@ test-catena.c $(BASEFILES) $(HASHIMPL) catena-BRG.c $(HASH)

catena-Dragonfly-blake2s-test_vectors:
	$(CC) $(CFLAGS) -o $(TARGETDIR)/$@ catena_test_vectors.c $(BASEFILES) $(HASHIMPL) catena-BRG.c $(HASH)

clean:
	rm -f  *~ *.o
