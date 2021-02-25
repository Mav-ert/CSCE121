#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

int* createSeam(int length) {
	int *seam = new int[length];
	for(int i =0; i < length; i++){
		seam[i]=0;
	}
	return seam;
}

void deleteSeam(int* seam) {
	delete [] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height) {
	ifstream ifs (filename);
  
	if (!ifs.is_open()) {
		cout << "Error: failed to open input file - " << filename << endl;
		return false;
	}
  
	char type[3];
	ifs >> type; // should be P3
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
	int w = 0;
	int h = 0;
	ifs >> w;
	if(ifs.fail()){
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	else if (w <=0) { 
		cout << "Error: width must be greater than 0. You entered " << w << endl;
		return false;
	}else if (w!= width){
		cout << "Error: input width (" << width << ") does not match value in file (" << w <<  ")" << endl;
		return false;
	}
	ifs >> h;
	if(ifs.fail()){
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	else if (h <=0) { 
		cout << "Error: height must be greater than 0. You entered " << h << endl;
		return false;
	}else if (h!= height){
		cout << "Error: input height (" << height <<") does not match value in file (" << h << ")" << endl;
		return false;
	}
  
  // get maximum value from preamble
	int colorMax = 0;
	ifs >> colorMax;
	if (colorMax != 255) {
		cout << "Error: file is not using RGB color values." << endl;
		return false;
	}
	int Pixcount =width*height*3;
	int count =0;
	
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			ifs >> image[j][i].r;
			count+=1;
			if (ifs.fail()) {
				cout << "Error: read non-integer value "  << endl;
				return false;
			}if (image[j][i].r <0 || image[j][i].r > 255){
				cout << "Error: invalid color value " << image[j][i].r << endl;
				return false;
			}
			ifs >> image[j][i].g;
			count+=1;
			if (ifs.fail()) {
				cout << "Error: read non-integer value "  << endl;
				return false;
			}if (image[j][i].g <0 || image[j][i].g > 255){
				cout << "Error: invalid color value " << image[j][i].r << endl;
				return false;
			}
			ifs >> image[j][i].b;
			count+=1;
			if (ifs.fail()) {
				cout << "Error: read non-integer value " << endl;
				return false;
			}if (image[j][i].b <0 || image[j][i].b > 255){
				cout << "Error: invalid color value " << image[j][i].r << endl;
				return false;
			}
		
		}
	}
  if(count < Pixcount){
		cout <<"Error: not enough color values" << endl;
		return false;
	}
	if(count > Pixcount){
		cout <<"Error: too many color values" << endl;
		return false;
	}
	return true;

	
}


bool outputImage(string filename, Pixel** image, int width, int height) {
	cout << "Outputting image..." << endl;
  // declare/define and open output file stream
	ofstream ofs (filename);
  // check if output stream opened successfully
	if (!ofs.is_open()) {
		cout << "Error: failed to open output file - " << filename << endl;
		return false;
	}
  
  // output preamble
	ofs << "P3" << endl;
	ofs << width << " " << height << endl;
	ofs << 255 << endl;
  // output pixels
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < width; ++j) {
			ofs << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << endl;
			
		}
	}
	return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
	int rx,gx,bx,ry,gy,by,gradx,grady;
	if (x==0){
		rx = image[x+1][y].r-image[width-1][y].r;
		gx = image[x+1][y].g-image[width-1][y].g;
		bx = image[x+1][y].b-image[width-1][y].b;
	}
	if (x==width-1){
		rx = image[width-2][y].r-image[0][y].r;
		gx = image[width-2][y].g-image[0][y].g;
		bx = image[width-2][y].b-image[0][y].b;
	}
	else if (x>0){
		rx = image[x+1][y].r-image[x-1][y].r;
		gx = image[x+1][y].g-image[x-1][y].g;
		bx = image[x+1][y].b-image[x-1][y].b;
	}
	gradx = pow(rx,2)+pow(gx,2)+pow(bx,2);
	if (y==0){
		ry = image[x][y+1].r-image[x][height-1].r;
		gy = image[x][y+1].g-image[x][height-1].g;
		by = image[x][y+1].b-image[x][height-1].b;
	}
	if (y==height-1){
		ry = image[x][height-2].r-image[x][0].r;
		gy = image[x][height-2].g-image[x][0].g;
		by = image[x][height-2].b-image[x][0].b;
	}
	else if (y>0){
		ry = image[x][y+1].r-image[x][y-1].r;
		gy = image[x][y+1].g-image[x][y-1].g;
		by = image[x][y+1].b-image[x][y-1].b;
	}
	grady = pow(ry,2)+pow(gy,2)+pow(by,2);

	return gradx+grady;
}

// implement for part 2

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
	int totVal=0;
	int compare1,compare2,compare3;
	totVal+=energy(image,start_col,0,width,height);
	seam[0] = start_col;
	for(int i = 1; i < height; i++){
		
		compare2 = energy(image,start_col,i,width,height);
		
		if(start_col-1<0){
			compare1=compare2;
		}
		else{
			compare1 = energy(image,start_col-1,i,width,height);
		}
		if(start_col+1>width-1){
			compare3=compare2;
		}
		else{
			compare3 = energy(image,start_col+1,i,width,height);
		}
		if(compare1 < compare2 && compare1 < compare3){
			seam[i] = start_col-1;
			totVal+=compare1;
			start_col = start_col-1;
			
		}
		else if(compare2 <= compare1 && compare2 <= compare3){
			seam[i] = start_col;
			totVal+=compare2;
			
		}
		else if(compare3<=compare1 && compare3<compare2){
			seam[i] = start_col+1;
			totVal+=compare3;
			start_col=start_col+1;
		}
		
	}
	return totVal;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
	int totVal=0;
	int compare1,compare2,compare3;
	totVal+=energy(image,0,start_row,width,height);
	seam[0] = start_row;
	for(int i = 1; i < width; i++){
		compare2 = energy(image,i,start_row,width,height);
		if(start_row-1<0){
			compare1=compare2;
		}
		else{
			compare1 = energy(image,i,start_row-1,width,height);
		}
		if(start_row+1>height-1){
			compare3=compare2;
		}
		else{
			compare3 = energy(image,i,start_row+1,width,height);
		}
		if(compare1 < compare2 && compare1 <= compare3){
			seam[i] = start_row-1;
			totVal+=compare1;
			start_row=start_row-1;
			
		}
		else if(compare2 <= compare1 && compare2 <= compare3){
			seam[i] = start_row;
			totVal+=compare2;
		}
		else if(compare3<compare1 && compare3<compare2){
			seam[i] = start_row+1;
			totVal+=compare3;
			start_row=start_row+1;
		}
		
	}
	return totVal;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	int* seam = createSeam(height);
	int minseam=0,energyvalue=0,energyvaluemin=loadVerticalSeam(image,0,width,height,seam);
	for(int i = 1; i < width; i++){
		energyvalue = loadVerticalSeam(image,i,width,height,seam);
		if(energyvalue < energyvaluemin){
			energyvaluemin = energyvalue;
			minseam = i;
		}
	}
	loadVerticalSeam(image,minseam,width,height,seam);
  return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
	int* seam = createSeam(width);
	int minseam=0,energyvalue=0,energyvaluemin=loadHorizontalSeam(image,0,width,height,seam);
	for(int i = 1; i < height; i++){
		energyvalue = loadHorizontalSeam(image,i,width,height,seam);
		if(energyvalue < energyvaluemin){
			energyvaluemin = energyvalue;
			minseam = i;
		}
	}
	loadHorizontalSeam(image,minseam,width,height,seam);
	return seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	for(int i = 0; i < height; i++){
		for(int j = verticalSeam[i]; j < width-1; j++){
			image[j][i] = image[j+1][i];
		}
		
	}
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	for(int i = 0; i < width; i++){
		for(int j = horizontalSeam[i]; j < height-1; j++){
			image[i][j] = image[i][j+1];
		}
		
	}
}