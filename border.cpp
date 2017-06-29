#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types_c.h>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;


RNG rng(12345);

Mat removeBackground(Mat Base, Mat Layer);

/** @function main */
int main ( int argc, char** argv ){
	// Carregar imagem de base para subtrair nas seguintes:
	Mat BaseColor = imread( "originais/Vídeo_Axial001.png" );
	Mat Base;
	cvtColor(BaseColor, Base, COLOR_BGR2GRAY);



	// Para cada camada:
	for (int i = 2; i <= 40; i++){
		// Obter o nome do arquivo da imagem:
		char filename[32];
		sprintf(filename,"originais/Vídeo_Axial%03d.png",i);
		// Carregar a imagem da camada:
		Mat Layer = imread(filename);
		cvtColor(Layer, Layer, COLOR_BGR2GRAY);

		Layer = removeBackground(Base, Layer);


		// Remover Ruído:
		Mat NoiseMask;
		// Blur e threshold para tirar os pontos bem isolados mesmo:
		blur(Layer, NoiseMask, Size(8,8));
		threshold(NoiseMask, NoiseMask, 60, 0, THRESH_TOZERO);
		// Dilatação para juntar objetos próximos:
		Mat se1 = getStructuringElement(MORPH_ELLIPSE, Size (5, 5));
		dilate( NoiseMask, NoiseMask, se1 );
		erode( NoiseMask, NoiseMask, se1 );

		// Erosão para tirar ilhas e ruido:
		Mat se2 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
		erode( NoiseMask, NoiseMask, se2 );
		// Crescer de volta ao tamanho natural:
		dilate( NoiseMask, NoiseMask, se2 );


		// Mascarar a imagem original com esta máscara:
		Layer.setTo(Scalar(0), NoiseMask <= 4);

		// // Conseguir uma figura com o mesmo contorno que a camada, mas 100% preenchida:
		Mat CountourMask;
		// Dilata bastante a imagem:
		Mat se3 = getStructuringElement(MORPH_ELLIPSE, Size(130, 130));
		dilate( Layer, CountourMask, se3 );
		// Deixa tudo que importa da mesma cor, e o resto preto:
		threshold(CountourMask, CountourMask, 8, 255, THRESH_BINARY);
		// Coloca de volta pro tamanho certo:
		erode(CountourMask, CountourMask, se3);


		// Remover os órgãos:
		Layer.setTo(Scalar(0), CountourMask != 0);


		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		Mat countours;

		findContours( CountourMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

		Mat drawing = Mat::zeros( Layer.size(), CV_8UC3 );
		for( int i = 0; i< contours.size(); i++ ){
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		}





		// Obter nome do arquivo de destino:
		sprintf(filename,"borders/layer%03d.png",i);
		// Armazenar imagem resultante:
		imwrite( filename, drawing);



	}
}

Mat removeBackground(Mat Base, Mat Layer){
	// Subtrair a base da camada:
	Mat diff = Layer - Base;

	// Aplicar threshhold em diff, inverter, e mascarar a original
	threshold(diff, diff, 1, 255, THRESH_BINARY);
	Mat dst;
	Layer.copyTo(dst, diff);

	return dst;


}
