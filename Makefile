all: border
	./border > output.txt
border: border.cpp
	g++ border.cpp -o border -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

render: draw
	./draw

draw: draw.cpp output.txt
	g++ draw.cpp -o draw -framework GLUT -framework OpenGL -Wall -Wno-deprecated-declarations
