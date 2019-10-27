// openc_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)
#define pf(x , y)  (cout << #x << #y << ":" << y << endl)
const char* programSource =
"__kernel void vecadd(__global int* A, __global int* B, __global int* C)\n"
"{                                                                        \n"
"    int idx=get_global_id(0);                                            \n"
"    C[idx]=A[idx]+B[idx];                                                \n"
"}                                                                        \n"
;
/*
int main()
{
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;
	cl_uint work_item_dim;
	size_t work_item_sizes[3];
	size_t work_group_size;
	cl_uint ucomput_uint = 0;
	cl_uint uconstant_args = 0;
	cl_ulong uconstant_buffer_size = 0;

	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	printf("devices   : %d\n", ret_num_devices);

	char pform_vendor[40];
	clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, sizeof(pform_vendor), &pform_vendor, NULL);
	printf("vendor   : %s\n", &pform_vendor);

	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), (void *)&work_item_dim, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_item_sizes), (void *)work_item_sizes, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), (void *)&work_group_size, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), (void *)&ucomput_uint, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint), (void *)&uconstant_args, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), (void *)&uconstant_buffer_size, NULL);

	printf("Max work-item dimensions   : %d\n", work_item_dim);
	printf("Max work-item sizes        : %d %d %d\n", work_item_sizes[0], work_item_sizes[1], work_item_sizes[2]);
	printf("Max work-group sizes       : %d\n", work_group_size);
	printf("Max comput_uint            : %u\n", ucomput_uint);
	printf("Max constant_args          : %u\n", uconstant_args);
	printf("Max constant_buffer_size   : %u\n", uconstant_buffer_size);

	system("pause");
	return 0;
}

*/

int32_t get_device_info(cl_device_id &device_id)
{
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;
	cl_uint work_item_dim;
	size_t work_item_sizes[3];
	size_t work_group_size;
	cl_uint ucomput_uint = 0;
	cl_uint uconstant_args = 0;
	cl_ulong uconstant_buffer_size = 0;
	cl_ulong max_mem_size = 0;
	size_t len = 100;
	vector<char> buf(len);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), (void *)&work_item_dim, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_item_sizes), (void *)work_item_sizes, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), (void *)&work_group_size, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), (void *)&ucomput_uint, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint), (void *)&uconstant_args, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), (void *)&uconstant_buffer_size, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &max_mem_size, nullptr);


	clGetDeviceInfo(device_id, CL_DEVICE_NAME, len, &buf[0], &len);
	printf("device name : %s\n", &buf[0]);
	printf("device has max memory :%u MB\n", max_mem_size / 1048576);

	printf("Max work-item dimensions   : %d\n", work_item_dim);
	printf("Max work-item sizes        : %d %d %d\n", work_item_sizes[0], work_item_sizes[1], work_item_sizes[2]);
	printf("Max work-group sizes       : %d\n", work_group_size);
	printf("Max comput_uint            : %u\n", ucomput_uint);
	printf("Max constant_args          : %u\n", uconstant_args);
	printf("Max constant_buffer_size   : %u\n", uconstant_buffer_size);

	return 0;
}

int32_t get_plateform_info(cl_platform_id &plt_id)
{
	size_t size = 0;
	cl_uint gpu_num = 0;
	cl_int status;
	clGetDeviceIDs(plt_id, CL_DEVICE_TYPE_GPU, 0, nullptr, &gpu_num);


	pf("plate has ", gpu_num);
	cl_uint cpu_num = 0;
	clGetDeviceIDs(plt_id, CL_DEVICE_TYPE_CPU, 0, nullptr, &cpu_num);
	pf("plate has ", cpu_num);

	//name
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_NAME, 0, NULL, &size);
	char* name = (char*)malloc(size);
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_NAME, size, name, NULL);
	printf("CL_PLATFORM_NAME:%s\n", name);

	//vendor
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_VENDOR, 0, NULL, &size);
	char *vendor = (char *)malloc(size);
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_VENDOR, size, vendor, NULL);
	printf("CL_PLATFORM_VENDOR:%s\n", vendor);

	//version
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_VERSION, 0, NULL, &size);
	char *version = (char *)malloc(size);
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_VERSION, size, version, NULL);
	printf("CL_PLATFORM_VERSION:%s\n", version);

	// profile
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_PROFILE, 0, NULL, &size);
	char *profile = (char *)malloc(size);
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_PROFILE, size, profile, NULL);
	printf("CL_PLATFORM_PROFILE:%s\n", profile);

	// extensions
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_EXTENSIONS, 0, NULL, &size);
	char *extensions = (char *)malloc(size);
	status = clGetPlatformInfo(plt_id, CL_PLATFORM_EXTENSIONS, size, extensions, NULL);
	printf("CL_PLATFORM_EXTENSIONS:%s\n", extensions);

	// release 
	printf("\n\n");
	free(name);
	free(vendor);
	free(version);
	free(profile);
	free(extensions);
	return 0;
}


void opencl_test(cl_platform_id& platforms)
{
	int *A = NULL;
	int *B = NULL;
	int *C = NULL;
	const  int elements = 128;
	size_t datasize = sizeof(int)*elements;
	pf("len ", datasize);
	A = (int*)malloc(datasize);
	B = (int*)malloc(datasize);
	C = (int*)malloc(datasize);
	for (int i = 0; i < elements; i++)
	{
		A[i] = i;
		B[i] = i;
	}
	cl_int status;
	/*Discover and initialize the platforms*/
	/*Discover and initialize devices*/
	cl_uint numDevices = 0;
	cl_device_id* devices = NULL;
	status = clGetDeviceIDs(platforms, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);  // retrieve Device number
	printf("# of device:%d\n", numDevices);
	devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id)); // malloct memery for device
	status = clGetDeviceIDs(platforms, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL); // fill in device 
	/*Creat a context*/
	cl_context context = NULL;
	context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);
	//  context = clCreateContextFromType(NULL,CL_DEVICE_TYPE_ALL,NULL,NULL,&status);
	//  cl_device_id device_list;
	size_t  device_num;
	clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, 0, NULL, &device_num);
	printf("Size of cl_device_id:%d\n", sizeof(cl_device_id));
	printf("Num of device in Context:%d\n", device_num);
	//  device_list = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &device_list);
	/*Create a command queue*/
	cl_command_queue cmdQueue;
	cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);
	/*Create device buffers*/
	cl_mem bufferA;
	cl_mem bufferB;
	cl_mem bufferC;
	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &status);
	bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &status);
	/*Write host data to device buffers*/
	status = clEnqueueWriteBuffer(cmdQueue, bufferA, CL_FALSE, 0, datasize, A, 0, NULL, NULL);
	status = clEnqueueWriteBuffer(cmdQueue, bufferB, CL_FALSE, 0, datasize, B, 0, NULL, NULL);
	//status = clEnqueueWriteBuffer(cmdQueue,bufferC,CL_FALSE,0,datasize,C,0,NULL,NULL);
	/*Create and compile the program*/
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&programSource, NULL, &status);
	status = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);
	if (status != CL_SUCCESS)
	{
		size_t len;
		char buffer[8 * 1024];
		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
	}
	/*Create the kernel*/
	cl_kernel kernel = NULL;
	kernel = clCreateKernel(program, "vecadd", &status);
	/*Set the kernel arguments*/
	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
	status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);
	/*CONFIGURE THE WORK-ITEM STRUCTURE*/
	size_t globalWorkSize[1];
	globalWorkSize[0] = elements;
	//  size_t globalSize[1] = { elements }, localSize[1] = { 256 };
	/*Enqueue the kernel for execution*/
	status = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	/*Read the buffer output back to host*/
	clFinish(cmdQueue);
	clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, datasize, C, 0, NULL, NULL);
	printf("The calculated outcome:");
	for (int i = 0; i < elements; i++)
	{
		printf("%d ", C[i]);
	}
	printf("\n");
	bool result = true;
	printf("The right outcome:     ");
	int D[elements] = { 0 };
	for (int i = 0; i < elements; i++)
	{
		D[i] = i + i;
		printf("%d ", D[i]);
	}
	printf("\n");
	for (int i = 0; i < elements; i++)
	{
		if (C[i] != D[i])
		{
			result = false;
			break;
		}
	}
	if (result)
	{
		printf("Output is correct!\n");
	}
	else
	{
		printf("Output is incorrect!\n");
	}
	/*Release OpenCL resources*/
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(cmdQueue);
	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseContext(context);
	free(A);
	free(B);
	free(C);
	free(devices);
	//getchar();
}

int main()
{
	cl_uint num = 2;
	cl_int err;	
	err = clGetPlatformIDs(0, nullptr, &num);
	if (err != CL_SUCCESS)
	{
		cout << "get pl num" << endl;
		exit(1);
	}
	pf("platforms has ", num);
	vector<cl_platform_id> platforms(num);
	err = clGetPlatformIDs(num, &platforms[0], &num);
	if (err != CL_SUCCESS)
	{
		cout << "get plateform" << endl;
		exit(1);
	}
	//for (auto it = platforms.begin(); it != platforms.end(); it++)
	for (auto platform_info : platforms)
	{
		get_plateform_info(platform_info);
		cl_uint gpu_num = 0;
		clGetDeviceIDs(platform_info, CL_DEVICE_TYPE_GPU, 0, nullptr, &gpu_num);
		vector<cl_device_id> did(gpu_num);
		clGetDeviceIDs(platform_info, CL_DEVICE_TYPE_GPU, gpu_num, &did[0], &gpu_num);
		uint8_t device_num = 1;
		for (auto gpuinfor : did)
		{
			printf("get device %d's information:\n", device_num++);
			get_device_info(gpuinfor);
		}
		printf("\n\n\n\n\n");
		opencl_test(platform_info);
	}
	system("pause");
}