/*
 * matmult.cpp
 *
 *  Created on: 23 abr 2024
 *      Author: sanchez
 */

#include "matmult.hpp"
#include "matrix_lib.hpp"
#include "common/err_code.h"
#include "common/device_picker.hpp"

#define __CL_ENABLE_EXCEPTIONS

int main(int argc, char *argv[])
{
	// inicializar
    int N;      // A[N][N], B[N][N], C[N][N]
    int size;   // Number of elements in each matrix


    double start_time;      // Starting time
    double run_time;        // Timing data
    util::Timer timer;      // Timer


    N = ORDER;

    size = N * N;

    std::vector<float> h_A(size); // Host memory for Matrix A
    std::vector<float> h_B(size); // Host memory for Matrix B
    std::vector<float> h_C(size); // Host memory for Matrix C

    cl::Buffer d_a, d_b, d_c;   // Matrices in device memory

//--------------------------------------------------------------------------------
// Create a context and queue
//--------------------------------------------------------------------------------

    try
    {

        cl_uint deviceIndex = 0;
        parseArguments(argc, argv, &deviceIndex);

        // Get list of devices
        std::vector<cl::Device> devices;
        unsigned numDevices = getDeviceList(devices);

        if(numDevices==0) {
        	std::cout << "There are  not devices" << std::endl;
        	return 0;
        }

        // Check device index in range
        if (deviceIndex >= numDevices)
        {
          std::cout << "Invalid device index (try '--list')\n";
          return EXIT_FAILURE;
        }

        cl::Device device = devices[deviceIndex];

        std::string name;
        getDeviceName(device, name);
        std::cout << "\nUsing OpenCL device: " << name << "\n";

        std::vector<cl::Device> chosen_device;
        chosen_device.push_back(device);
        cl::Context context(chosen_device);
        cl::CommandQueue queue(context, device);




    //--------------------------------------------------------------------------------
    // Run sequential matmul
    //--------------------------------------------------------------------------------

            initmat(N, h_A, h_B, h_C);

            printf("\n===== Sequential, matrix mult (dot prod), order %d on host CPU ======\n",ORDER);
            for(int i = 0; i < COUNT; i++)
            {
                zero_mat(N, h_C);
                start_time = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0;

                seq_mat_mul_sdot(N, h_A, h_B, h_C);

                run_time  = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0 - start_time;
                results(N, h_C, run_time);
            }

      //--------------------------------------------------------------------------------
      // Setup the buffers, initialize matrices, and write them into global memory
      //--------------------------------------------------------------------------------

                    //  Reset A, B and C matrices (just to play it safe)
                    initmat(N, h_A, h_B, h_C);

                    d_a = cl::Buffer(context, h_A.begin(), h_A.end(), true);

                    d_b = cl::Buffer(context, h_B.begin(), h_B.end(), true);

                    d_c = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * size);

      //--------------------------------------------------------------------------------
      // OpenCL matrix multiplication ... Naive
      //--------------------------------------------------------------------------------

                            // Create the compute program from the source buffer
                            cl::Program program(context, util::loadProgram("C_elem.cl"), true);

                            // Create the compute kernel from the program
                            cl::KernelFunctor<int, cl::Buffer, cl::Buffer, cl::Buffer> naive_mmul(program, "mmul");

                            printf("\n===== OpenCL, matrix mult, C(i,j) per work item, order %d ======\n",N);

                            // Do the multiplication COUNT times
                            for (int i = 0; i < COUNT; i++)
                            {
                                zero_mat(N, h_C);

                                start_time = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0;

                                // Execute the kernel over the entire range of C matrix elements ... computing
                                // a dot product for each element of the product matrix.  The local work
                                // group size is set to NULL ... so I'm telling the OpenCL runtime to
                                // figure out a local work group size for me.
                                cl::NDRange global(N, N);
                                naive_mmul(cl::EnqueueArgs(queue, global),
                                        N, d_a, d_b, d_c);

                                queue.finish();

                                run_time  = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0 - start_time;

                                cl::copy(queue, d_c, h_C.begin(), h_C.end());

                                results(N, h_C, run_time);

                            } // end for loop

    } catch (cl::Error& err)
    {
        std::cout << "Exception\n";
        std::cerr << "ERROR: "
                  << err.what()
                  << "("
                  << err_code(err.err())
                  << ")"
                  << std::endl;
    }

            return EXIT_SUCCESS;
}


