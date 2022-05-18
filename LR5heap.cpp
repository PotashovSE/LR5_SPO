#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <conio.h>
#include <random>
#include <fstream>
#include <math.h>

#define MAX (24 * 1024)

using namespace std;


int main()
{
	char str[1];
    cout << "Start\n";

    //Пункт 1
    cout << "Press any key to continue...\n"<<"1. \n";
	_getch();
    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE, 0, MAX);
    if (heap != NULL)
    {
        cout << "completed...\n\n";
    }
    else{
       return EXIT_FAILURE;
    }

    //Пункт 2
    cout << "Press any key to continue...\n" <<"2. \n";
	_getch();

    uniform_int_distribution<size_t> block_size(32, 1024);
    mt19937 gen(random_device{}());

	size_t sz_b = block_size(gen);
    while (HeapAlloc(heap, 0, sz_b != NULL))
    {
        sz_b = block_size(gen);
    }
	cout << "completed...\n\n";

    //Пункт 3
	cout << "Press any key to continue...\n"<<"3. \n";
	_getch();

	size_t cbData=0;
	size_t cbOver=0;
	PROCESS_HEAP_ENTRY Entry{};

    while (HeapWalk(heap, &Entry)!= NULL)
    {
        if ((Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY))
        {
            cbOver += Entry.cbOverhead;
            cbData += Entry.cbData;
        }
    }

    cout <<"\n Total amount of data stored: " << cbData << "\n" <<
            "\n Total overhead costs:        " << cbOver << "\n" <<
            "\n Difference:                  " << MAX - cbData-cbOver << "\n";
	cout << "\ncompleted...\n\n";

    //Пункт 4
	cout << "Press any key to continue...\n"<<"4. \n";
	_getch();

    uniform_int_distribution<> rand(1, 3);
    Entry.lpData = NULL;
    void *p = NULL; //указатель на память (безтиповый)
    while (HeapWalk(heap, &Entry))
    {
        if (Entry.wFlags == PROCESS_HEAP_ENTRY_BUSY)
        {
            if (p != NULL)
            {
                HeapFree(heap, 0, p);
            }
            if (rand(gen)!=1)
            {
               p = NULL;
            }
            else
            {
                p = Entry.lpData;
            }
        }
    }
	cout << "completed...\n\n";

    //Пункт 5
	cout << "Press any key to continue...\n"<<"5. \n";
	_getch();

	cbData = 0;
	cbOver = 0;
	size_t freeData  = 0; // суммарный свободный объём
	size_t maxData = 0; // наибольший объем свободного блока
	Entry.lpData = NULL;

    while (HeapWalk(heap, &Entry)!= NULL)
    {
        if ((Entry.wFlags == PROCESS_HEAP_ENTRY_BUSY))
        {
            cbOver += Entry.cbOverhead;
            cbData += Entry.cbData;
        }
        		if (Entry.wFlags == NULL)
		{
			if (maxData < Entry.cbData)
			{
				maxData = Entry.cbData;
			}
			freeData += Entry.cbData;

		}

    }

    cout <<"\n Total amount of data stored: " << cbData << "\n" <<
            "\n Total overhead costs:        " << cbOver << "\n" <<
            "\n Difference:                  " << MAX - cbData-cbOver << "\n";
    cout<<"\n Total free volume: " << freeData << "\n\n Max free block size: " << maxData << "\n";
	cout << "\ncompleted...\n\n";

    //Пункт 6
	cout << "Press any key to continue...\n"<<"6.\n\n";
	_getch();

    size_t Alloc = maxData - 16;
    p = HeapAlloc(heap, 0, Alloc);
    if (p!= NULL)
    {
        cout<<"Bytes allocation: " << Alloc << "bytes\n\n";
        if (HeapFree(heap, 0, p))
        {
            cout << "Successfully allocation\n\n";
        }
        else
        {
            cout << "Unsuccessfully allocation\n\n";
            return 0;
        }
    }

    Alloc = freeData - 16;
    p = HeapAlloc(heap, 0, Alloc);
    if (p != NULL)
    {
        cout << "Bytes allocation: " << Alloc << " bytes\n\n";
        if (HeapFree(heap, 0, p))
            cout << "Successfully allocation for Heap\n\n";
        else
        {
            cout << "Unsuccessfully allocation for Heap\n\n";
            return 0;
        }
    }
    else
        cout << "ERROR"<< GetLastError;
        cout << "\nError bytes allocation: " << Alloc << "\n";
	cout << "completed...\n\n";

    //Пункт 7
	cout << "Press any key to continue...\n"<<"7.\n";
	_getch();

    HeapDestroy(heap);
	cout << "\ncompleted...\n\n";

    //Пункт 8
	cout << "Press any key to continue...\n"<<"8.\n\n";
	_getch();

    auto new_heap = HeapCreate(HEAP_NO_SERIALIZE, 0, MAX);
    Alloc = 1;
    while (HeapAlloc(new_heap, 0, Alloc)!= NULL)
        Alloc++;

    Entry.lpData = NULL;
    while (HeapWalk(new_heap, &Entry) != NULL)
    {
		if (Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
		{
            cout << Entry.cbData << "    " << (int) Entry.cbOverhead << "\n";
		}
    }

	cout << "completed...\n\n" << "Press any key to exit...";
	_getch();

	cout << "The end of the program";

    return 0;
}


