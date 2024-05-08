/*
 * main_OpenCL_cpp.cpp
 *
 *  Created on: 2 nov. 2019
 *      Author: sanchez
 */

#include <iostream>
#include <string>
#include <array>
#include <numeric>
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <CL/opencl.hpp>



int main(){

	// Get All platforms
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()<=0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    } else {
    	std::cout<<" Platforms:" << all_platforms.size() << std::endl;
    }

    for(unsigned long int i=1; i<all_platforms.size(); i++ ) {
        cl::Platform default_platform=all_platforms[i];

        std::cout << "Platform Name: " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
        std::cout << "Platform Vendor: " << default_platform.getInfo<CL_PLATFORM_VENDOR>() << std::endl;

        std::vector<cl::Device> all_devices;
        default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
        if(all_devices.size()==0){
            std::cout<<" No devices found. Check OpenCL installation!\n";
            exit(1);
        }

        std::cout << "Platform " << i << " : " << default_platform.getInfo<CL_PLATFORM_NAME>() << " :" << std::endl;
        for(unsigned long int j=0; j < all_devices.size(); j++) {
            cl::Device default_device=all_devices[j];

            std::cout << " " << j << ". Device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;
            std::cout << "   " << j << ".1 Hardware Version: " << default_device.getInfo<CL_DEVICE_VERSION>() << std::endl;
            std::cout << "   " << j << ".2 Software Version: " << default_device.getInfo<CL_DRIVER_VERSION>() << std::endl;
            std::cout << "   " << j << ".3 OpenCL CPP Version: " << default_device.getInfo<CL_DEVICE_OPENCL_C_VERSION>() << std::endl;
            std::cout << "   " << j << ".3 Parallel Compute units: " << default_device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl;
        }
    }


}




