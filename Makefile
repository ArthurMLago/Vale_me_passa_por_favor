all: border
	./border
border: border.cpp
	g++ border.cpp -o border -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs