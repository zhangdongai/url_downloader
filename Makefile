TARGET=url_downloader

CC=g++

CPPFLAGS=-D__LINUX__       \
		-g         \
		-O0        \
                -I.        \
		-std=c++11 \

LINKFALGS=-lcurl

#CPPOBJS=$(shell find ./ -name "*.cpp" | awk -F".cpp" '{printf "%s.o\n", $$1}')
CPPOBJS=$(shell find ./ -name "*.cpp")

all:
	$(CC) $(CPPFLAGS) $(CPPOBJS) $(LINKFALGS) -o $(TARGET)
