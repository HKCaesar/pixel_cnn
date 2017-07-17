/*
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <tiffio.h>
#include <algorithm>
#include<iostream>
#include<math.h>
#include<graphics.h>
*/
#include <stdio.h>
#include <tiffio.h>
#include <stdlib.h>
#include <iostream>
#include<fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include<math.h>
#include<graphics.h>
#include <GL/glut.h>
#include<omp.h>
#include<sys/time.h>
//#include<vector>

#define SWIR_X 8 //17
#define SWIR_Y 2//67
#define P_FACT 25
#define RGB_FACT 25
#define M_FACT 4
#define P_IMAGE_X (P_FACT*SWIR_X)
#define P_IMAGE_Y (P_FACT*SWIR_Y)
#define RGB_IMAGE_X (RGB_FACT*SWIR_X)
#define RGB_IMAGE_Y (RGB_FACT*SWIR_Y)
#define M_IMAGE_X (M_FACT*SWIR_X)
#define M_IMAGE_Y (M_FACT*SWIR_Y)
#define NUM_OF_THREADS 16
#define X_PART SWIR_X
#define Y_PART SWIR_Y
#define IMAGE_X_SIZE 136
#define IMAGE_Y_SIZE 134
#define WEIGHT_ROW 5
#define WEIGHT_COLUMN 5
#define NO_IMAGES_PARTS ((IMAGE_X_SIZE/X_PART)*(IMAGE_Y_SIZE/Y_PART))
#define NO_LAYERS 5
#define NO_HOSTS 6
#define NO_OF_FILES 452
#define TRAINING_PERCENTAGE 80
#define TESTING_PERCENTAGE 20
#define NO_POOLING_LAYERS 2
#define NO_CONVOLUTION_LAYERS 3
#define POOL_SIZE 2
#define NO_CLASS 10
#define NO_NEURAN 10

#define WEIGHT_SIZE (WEIGHT_COLUMN*WEIGHT_ROW+1)
#define LR 0.5

using namespace std;





#define FOLDER_PATH "../data/"
#define TRAIN_FILE "train_wkt_v4.csv"
#define GRID_FILE "grid_sizes.csv"

#include "pixel_wise_convolutional_neural_network.cpp"
#include "image_read_view.cpp"
#include "image_marge.cpp"
#include "softmax_backprpagation.cpp"
#include "nn_analysis_network.cpp"
#include "file_seletion.cpp"
#include "before_image_process.cpp"
