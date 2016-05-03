#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include <opencv2/face.hpp>

using namespace cv;

void readme();

/** @function main */
int main(int argc, char** argv)
{
    //read the folder
    std::string data_fold      = argv[1]; // location where images are held
    std::string output_fold    = argv[2]; // location where output model, images, measurements written

    int numImages=1;
    std::stringstream strStream;
    std::string imageName;
    while(1){               //read all images in format 000000.jpg - 000NNN.jpg
        strStream << std::setw(6) << std::setfill('0') << numImages;
        imageName = data_fold + strStream.str() + ".jpg";
        if (FILE *file = fopen(imageName.c_str(), "r")) {
            fclose(file);
            numImages++;     //keep track
        } else {
            break;
        }
        strStream.str("");
    }

    //run bash script, .sh file should be chmod +x
    system("/bin/bash -c 'chmod +x ../../scripts/runTest.sh'");
    system("../../scripts/runTest.sh");

    //write some output files
    std::ofstream myfile;
    myfile.open(output_fold + "leftFoot.ply");
    myfile << "Writing this to a file.\n";
    myfile.close();

    myfile.open (output_fold + "rightFoot.ply");
    myfile << "Writing this to a file.\n";
    myfile.close();

    myfile.open (output_fold + "view1.png");
    myfile << "Writing this to a file.\n";
    myfile.close();

    myfile.open (output_fold + "view2.png");
    myfile << "Writing this to a file.\n";
    myfile.close();

    myfile.open (output_fold + "measurements.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();

    //make feature detector used for template and scene
    cv::Ptr <cv::face::FaceRecognizer> model = cv::face::createLBPHFaceRecognizer();
	return 0;
}
