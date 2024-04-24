/*
 * host_code.cpp
 *
 *  Created on: 8 oct. 2021
 *      Author: sanchez
 */



#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200

#include <CL/opencl.hpp> 	// Khronos C++ Wrapper API
#include <cstdio> 		// C style IO (e.g. printf)
#include <iostream> 	// C++ style IO
#include <vector> 		// C++ vector types
#include <cmath>
#include <omp.h>

#include <fstream>
#include <string>
#include <random>
#include "bmpfuncs.h"


/*
 * This code loads the opencl kernel code
 */

namespace util {		// This code could be allocated in an external file
std::string loadProgram(std::string program_source) { // Read the program source
    std::ifstream sourceFile(program_source);
    std::string sourceCode( std::istreambuf_iterator<char>(sourceFile),
        (std::istreambuf_iterator<char>()));
    return sourceCode;
	}
}

/*
 *  Sequential implementation
 */
void img_rotate(float* dest_data,
                float* src_data,
                           int  W,
                           int  H,
                         float  sinTheta,
                         float  cosTheta,
                         int ix,
                         int iy
                         ) ;

/*
 * Main function
 */
int main() {
	int i;

/*
 *  Define rotation angle
 */
	   // Set the image rotation (in degrees)
	   float theta = 3.14159/6;			// 60 degrees
	   float cos_theta = cosf(theta);
	   float sin_theta = sinf(theta);
	   printf("theta = %f (cos theta = %f, sin theta = %f)\n", theta, cos_theta,
	      sin_theta);
/*
 * Read images
 */
	   int imageHeight;
	   int imageWidth;

	   const char* inputFile = "input.bmp";
	   const char* outputFile = "output.bmp";

	   float* h_inputImage = readImage(inputFile, &imageWidth,&imageHeight);

	   // Size of the input and output images on the host
	   int dataSize = imageHeight*imageWidth;

	   // Output image on the host
	   float* h_outputImage = new float[dataSize];
	   float* h_outputImageGood = new float[dataSize];

/*
 * OpenCl infrastructure
 */


    cl::Program program;
    std::vector<cl::Device> currentDevice;

try {

// Create context
    cl::Context context;

// Context OPTION 1 - Select platform and device
    std::vector<cl::Platform> platforms;    // Platform list
    cl::Platform::get(&platforms);			// Identify all Platforms
    if(platforms.size() <=0) {
    	std::cout << " No OpenCL Platform" << std::endl;
    	return 1;
    } else {
    	std::cout << platforms.size() << " Platform detected " << std::endl;
    }

    std::vector<cl::Device> devices;   // List of devices on selected platform
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices); // All devices of platform 0
    if(devices.size() <=0) {
    	std::cout << " No Devices in OpenCL Platform" << std::endl;
    	return 2;
    } else {
    	std::cout << devices.size() << " Device detected " << std::endl;
    }


    // Create a context with first device
    context= cl::Context(devices[0]);

// Context OPTION 2 - Select default device
    //context= cl::Context(CL_DEVICE_TYPE_DEFAULT);

    // Report selected device
    currentDevice=context.getInfo<CL_CONTEXT_DEVICES>();
    std::cout << "Execute code on device " << currentDevice[0].getInfo<CL_DEVICE_NAME>() << std::endl;

    // Create a command queue for device
    cl::CommandQueue queue(context);

/*
 *
 *   TODO = Code!!
 *
 */




    // Verify the result
    bool result = true;

    // Store result
    // Write the output image to file
  storeImage(h_outputImage, outputFile, imageHeight, imageWidth, inputFile);

    // Main loop
    for(int x=0;x<imageWidth;x++)
 	   for(int y=0;y<imageHeight;y++) {
		   img_rotate(h_outputImageGood,h_inputImage,imageWidth,imageHeight,sin_theta,cos_theta,x,y);
		   if(fabs((double)(h_outputImageGood[(y*imageWidth)+x]-h_outputImage[(y*imageWidth)+x])) > 0.0001) {
			   std::cout << x << " " << y << std::endl;
			   result=false;
		   }
 	   }

    if (result)
      std::cout << "Output is correct" << std::endl;
    else
      std::cout << "Output is not correct" << std::endl;

  }
  catch(cl::Error& error)
  {
	  if (error.err() == CL_BUILD_PROGRAM_FAILURE)
	  {
		  for (cl::Device dev : currentDevice)	// Vector iterator
		     {
		       cl_build_status status = program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(dev);
		       if (status == CL_BUILD_ERROR) {	// Get the build log of this device
		    	   std::string name     = dev.getInfo<CL_DEVICE_NAME>();
		    	   std::string buildlog = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(dev);
		    	   std::cout << "Build log for " << name << ":" << std::endl
		                 << buildlog << std::endl;
		       }
		   }
	 } else {
		 std::cout << "OpenCL execution Error. Type : " << error.what() << "(" << error.err() << ") " << std::endl;
	 }
  }

  return 0;
}


