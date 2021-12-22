#include <inc/lib.h>

// malloc()
//	This function use FIRST FIT strategy to allocate space in heap
//  with the given size and return void pointer to the start of the allocated space

//	To do this, we need to switch to the kernel, allocate the required space
//	in Page File then switch back to the user again.
//
//	We can use sys_allocateMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls allocateMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the allocateMem function is empty, make sure to implement it.

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
#define USER_HEAP_SIZE (USER_HEAP_MAX - USER_HEAP_START) / PAGE_SIZE

struct free_space
{
	uint32 address;
	bool present;
} free_spaces[USER_HEAP_SIZE + 1];

struct allocated
{
	uint32 address;
	uint32 pages;
	uint32 index;
} allocated_spaces[USER_HEAP_SIZE + 1];

//int free_index = 0;
int allocation_counter = 0;
uint32 alloc_index;

uint32 best_fit(uint32 size)
{
	uint32 best_address = -1;
	uint32 best_allocation_size = USER_HEAP_SIZE + 1;
	uint32 tmp_address = -1;
	uint32 tmp_index = -1;
	alloc_index = -1;
	uint32 consecutive = 0;

	size = ROUNDUP(size, PAGE_SIZE);
	uint32 required_pages = size / PAGE_SIZE;

	for (int start = 0; start < USER_HEAP_SIZE; start++)
	{
		if (free_spaces[start].present)
		{
			if (consecutive >= required_pages && best_allocation_size > consecutive)
			{
				best_allocation_size = consecutive;
				best_address = tmp_address;
				alloc_index = tmp_index;
			}

			tmp_address = -1;
			tmp_index = -1;
			consecutive = 0;
			continue;
		}

		if (!consecutive)
		{
			tmp_address = (start * PAGE_SIZE) + USER_HEAP_START;
			tmp_index = start;
		}
		consecutive++;

	}

	if (consecutive >= required_pages && best_allocation_size > consecutive)
	{
		best_address = tmp_address;
		alloc_index = tmp_index;
	}

	return best_address;
}

void* malloc(uint32 size)
{

	//TODO: [PROJECT 2021 - [2] User Heap] malloc() [User Side]
	// Write your code here, remove the panic and write your code
	//panic("malloc() is not implemented yet...!!");


	//This function should find the space of the required range
	//using the BEST FIT strategy

	//refer to the project presentation and documentation for details
	uint32 best_address = best_fit(size);
	size = ROUNDUP(size, PAGE_SIZE);
	uint32 required_pages = size / PAGE_SIZE;

	if (best_address == -1)
	{
		return NULL;
	}

	sys_allocateMem(best_address, size);

	for (int i = 0, alloc = alloc_index; i < required_pages; i++, alloc++)
	{
		free_spaces[alloc].present = 1;
		free_spaces[alloc].address = best_address;
	}

	allocated_spaces[allocation_counter].address = best_address;
	allocated_spaces[allocation_counter].index = alloc_index;
	allocated_spaces[allocation_counter].pages = required_pages;
	allocation_counter++;

	return (void*) best_address;
}

// free():
//	This function frees the allocation of the given virtual_address
//	To do this, we need to switch to the kernel, free the pages AND "EMPTY" PAGE TABLES
//	from page file and main memory then switch back to the user again.
//
//	We can use sys_freeMem(uint32 virtual_address, uint32 size); which
//		switches to the kernel mode, calls freeMem(struct Env* e, uint32 virtual_address, uint32 size) in
//		"memory_manager.c", then switch back to the user mode here
//	the freeMem function is empty, make sure to implement it.

void free(void* virtual_address)
{
	//TODO: [PROJECT 2021 - [2] User Heap] free() [User Side]
	// Write your code here, remove the panic and write your code
	panic("free() is not implemented yet...!!");

	//you should get the size of the given allocation using its address

	//refer to the project presentation and documentation for details
}

//==================================================================================//
//================================ OTHER FUNCTIONS =================================//
//==================================================================================//

void* smalloc(char *sharedVarName, uint32 size, uint8 isWritable)
{
	panic("this function is not required...!!");
	return 0;
}

void* sget(int32 ownerEnvID, char *sharedVarName)
{
	panic("this function is not required...!!");
	return 0;
}

void sfree(void* virtual_address)
{
	panic("this function is not required...!!");
}

void *realloc(void *virtual_address, uint32 new_size)
{
	panic("this function is not required...!!");
	return 0;
}

void expand(uint32 newSize)
{
	panic("this function is not required...!!");
}
void shrink(uint32 newSize)
{
	panic("this function is not required...!!");
}

void freeHeap(void* virtual_address)
{
	panic("this function is not required...!!");
}
