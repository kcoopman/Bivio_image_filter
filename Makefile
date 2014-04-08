#makefile written by Kevin Coopman

# tar -cf code.tar *.cpp *.h Makefile Cheering-crowd.jpg run_script 

# make
# cd    20130602
# mkdir faces; mkdir resize; mkdir histo; mkdir skin
# for filename in  *; do ../image_process ${filename}; done

#

#../image_process _A5Q3686.jpg 



HDRS =  image_functions.h  image_parameters.h image_structs.h

SRCS =  image_main.cpp image_detect.cpp \
	image_crop.cpp image_resize.cpp  \
	image_sharpness.cpp image_histo.cpp\
	image_skin.cpp make_picture.cpp

all: image_process canny

canny: canny.cpp
	g++  `pkg-config --cflags opencv` canny.cpp  -o canny `pkg-config --libs opencv`   


image_process: $(SRCS) $(HDRS)
	g++  -Wall `pkg-config --cflags opencv` $(SRCS) -o image_process `pkg-config --libs opencv`

run_test:
	image_process Cheering-crowd.jpg

run:
	image_process 20130602/10.jpg out.jpg

run_all:
	./run_script > file_output.txt

check_memory:
	valgrind image_process 20130602/10.jpg out.jpg


clean:
	rm -f  image_process

tar:
	tar -cf code.tar $(SRCS) $(HDRS) Makefile XML_Cascades canny.cpp

backup: 
	cp $(SRCS) $(HDRS) canny.cpp test.jpg Cheering-crowd.jpg run_script Makefile /media/Seagate\ Backup\ Plus\ Drive/nagler 