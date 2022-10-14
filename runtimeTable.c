#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

const char DATA_FILE_NAME[] = "TestData.txt";

typedef struct functionRuntimes
{
    char *szName;             //name of the function being tested
    double **arrRuntimes;         //run times
    double *arrAvg;            //average runtime
    int iNumRepeats;       //number of times to repeat each test size
    int iNumTestCaseSizes;   //number of test case sizes
    int *arrTestSizes;     //array containing the test case sizes
} functionRuntimes;

//Functions used to test the runtimes
functionRuntimes timeAlgorithm( char*, int, int, int[], void (*f)(FILE *) );
FILE *generateTestInput( int, int, int );
void computeAvg( functionRuntimes fRT );
void printRuntimeTable( functionRuntimes fRT );
void freeFunctionRuntimes( functionRuntimes fRT );

//Functions whose runtime will be tested (and helper functions)
void insertionSortInitial( FILE* input );
void insertionSort( int* points, int low, int high );
void quickSortOptInitial( FILE* input );
void quickSortOpt( int* points, int low, int high );
int partition( int* points, int low, int high );

void mysteryRuntime1( FILE* input );
void mysteryRuntime2( FILE* input );
void mysteryRuntime3( FILE* input );

/*
 * Provided code - DO NOT CHANGE THIS METHOD OTHER THAN TO ADD YOUR NAME AND YOUR PARTNER'S NAME
 * (if you make alterations for the sake of testing be sure to revert them before submission)
 */
int main( int argc, char *argv[] )
{
    functionRuntimes fRT;

    int sizes1[] = { 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};

    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("Alex Lemire\n");
    printf("Xander Wilson\n\n");

    srand(time(0));

    fRT = timeAlgorithm("Insertion Sort", 6, 5, sizes1, insertionSortInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("quicksort (uses insertion sort when sorting <30 numbers)", 12, 8, sizes1, quickSortOptInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 1", 3, 6, sizes1, mysteryRuntime1 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 2", 3, 5, sizes1, mysteryRuntime2 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 3", 3, 8, sizes1, mysteryRuntime3 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    return 0;
}

/*************************************** Functions to have their runtimes tested *********************************************/

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime1( FILE* input )
{
    int temp;
    int size;
    int n;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)	//O(n), iterates through file and fills array. -X
    {
        array[i] = temp;
        i++;
    }

    for( i=0; i<size; i++ )								//from 0 to size, O(n). -X
    {
        for( n=size-1; n>1; n/=1.01 )					//to my understanding, since its dividing every loop its log. this sounds really weird, but i think its log base 1.01 of n, so logn. that would make the whole loop nlogn. -X
        {
            array[n-1] = array[n];
        } //agreed, this on is strange, but i agree with the result, it almost looks like it's reverse engineered from a Masters Theoeum equation or something odd, i cant imagine the specific use case for this algo -A
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime2( FILE* input )
{
    int temp;
    int size;
    int i=0, j=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)	//O(n), fills array. -X
    {
        array[i] = temp;
        i++;
    }//fills to size, so O(n) -A

    i=0;
    while( j<size )										//looks like O(n²). j increments after i iterates through the entire array, the loop runs until j = n. AKA i goes from 0->n, n times. -X
    {
        array[j] = array[i];

        i++;
        if( i>=size )
        {
            j++;
            i=0;
        }
    }// inner and outer loop's both run n times, so O(n^2) -A

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime3( FILE* input )
{
    int temp;
    int size;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size) //O(n), populates array. -X
    {
        array[i] = temp;
        i++;
    }

    while( size>1 )
    {
        size = size/2;									//classic log2(n) material right here lol -X
        array[size/2] = array[size];    //at least we got an easy one -A
    }

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSortInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc( size*sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    insertionSort( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i])
        {
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSort( int* points, int low, int high )
{
    int i, j;
    double temp;

    for( i = low+1; i <= high; i++)
    {
        for( j = i; j > low && points[j]<points[j-1]; j--)
        {
            temp = points[j];
            points[j] = points[j-1];
            points[j-1] = temp;
        }
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOptInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc(size * sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    quickSortOpt( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i]){
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOpt( int* points, int low, int high )
{
    if( high < low+30 )
    {
        insertionSort( points, low, high );
    }
    else
    {
        int pivot = partition( points, low, high );

        quickSortOpt( points, low, pivot-1 );
        quickSortOpt( points, pivot+1, high );
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
int partition( int* points, int low, int high )
{
    int pivot = rand() % (high - low + 1) + low;
    int pivotValue = points[pivot];
    int i = low+1;
    int j = high;
    int temp;

    points[pivot] = points[low];
    points[low] = pivotValue;

    while( i<j )
    {
        while( i<=high && points[i] <= pivotValue )
        {
            i++;
        }
        while( j>=low && points[j] > pivotValue )
        {
            j--;
        }
        if(i<j)  //swap out of order elements
        {
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
        }
    }
    if( i<=high && points[i] <= pivotValue )
    {
        i++;
    }

    points[low] = points[i-1];
    points[i-1] = pivotValue;

    return i-1;
}

/*************************************** Functions for finding and printing runtime *********************************************/

/*
TODO: Give your asymptotic estimates for the runtimes of the following 3 functions:

mysteryRuntime1:  O( nlogn )
mysteryRuntime2:  O( n² )
mysteryRuntime3:  O( logn )
*/

/* TO BE COMPLETED BY YOU
 * Fill in the missing parts of the code (see TODOs below)
 */
functionRuntimes timeAlgorithm( char *szName, int iNumRepeats, int iNumTestCaseSizes, int arrTestSizes[], void (*f)(FILE *) )
{
    /* Call and calculate the runtime of the provided function f */
    clock_t start, end;
    int i, j;
    FILE *testData;

    //create functionRuntimes variable to return
    functionRuntimes fRT;

    //TODO: copy passed data into the fRT variable.  Specifically do the following:
	
    /* fill szName in fRT with the variable szName */
	  fRT.szName = (char*) calloc((strlen(szName) + 1), sizeof(char));
	  strcpy(fRT.szName, szName);
	
    /* fill iNumRepeats in fRT with the variable iNumRepeats */
	  fRT.iNumRepeats = iNumRepeats;
	
    /* fill iNumTestCaseSizes in fRT with the variable iNumTestCaseSizes */
	  fRT.iNumTestCaseSizes = iNumTestCaseSizes;
	
    /* malloc space for arrTestSizes in fRT to hold iNumTestCaseSizes number of ints */
	  fRT.arrTestSizes = (int*) calloc(iNumTestCaseSizes, sizeof(int));
	
    /* fill arrTestSizes in fRT with the variable arrTestSizes (hint: use a loop) */
	  for(i = 0; i < iNumTestCaseSizes; i++)
  		fRT.arrTestSizes[i] = arrTestSizes[i];

    //TODO: malloc an array with iNumTestCaseSizes variables of type double* (on next line)
    fRT.arrRuntimes = (double**) calloc(iNumTestCaseSizes, sizeof(double*));
	
    for( i=0; i< iNumTestCaseSizes; i++ )
    {
        //TODO: malloc an array with iNumRepeats variables of type double (on next line)
        fRT.arrRuntimes[i] = (double*) calloc(iNumRepeats, sizeof(double));

        for( j=0; j<iNumRepeats; j++ )
        {
            //Generate test data for the function f
            testData = generateTestInput( 0, arrTestSizes[i], arrTestSizes[i] );

            //Run f on the generated test data
            start = clock();
            f(testData);
            end = clock();
            fclose(testData);

            //Enter the elapsed number of seconds into the arrRuntimes array for fRT
            //TODO: uncomment the next line line after you've malloc-ed memory for fRT.arrRuntimes
            fRT.arrRuntimes[i][j] = (double)(end - start) / CLOCKS_PER_SEC;
        }
    }

    //TODO: on the next line, calloc space for fRT.arrAvg (you'll need to store iNumTestCaseSizes variables of type double)
    fRT.arrAvg = (double*) calloc(iNumTestCaseSizes, sizeof(double));
    //TODO: Calculate the average runtimes (i.e. call computeAvg here)
	  computeAvg(fRT);
    return fRT;
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
FILE *generateTestInput( int min, int max, int size )
{
    int i;
    FILE *data = fopen( DATA_FILE_NAME, "w" );

    if( data==NULL )
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }

    //add size to start of file
    fprintf( data, "%d ", size );
    //Fill the file with random data
    for( i=0; i<size; i++ )
    {
        fprintf( data, "%d ", rand()%(max-min+1)+min );
    }
    fclose(data);

    data = fopen( DATA_FILE_NAME, "r" );
    if( data==NULL )
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }
    return data;
}

/* TODO: TO BE COMPLETED BY YOU
 * Calculate and insert the average runtime for each set of test data into fRT
 */
void computeAvg( functionRuntimes fRT )
{	
	int i,j;
	double sum = 0;
	
	for(i = 0; i < fRT.iNumTestCaseSizes; i++)
  {	
		for(j = 0; j < fRT.iNumRepeats; j++)
    {	
			sum += fRT.arrRuntimes[i][j];	
		}
		fRT.arrAvg[i] = sum / fRT.iNumRepeats;
		sum = 0;
	}
}

/* TODO: TO BE COMPLETED BY YOU
 * Print the information in fRT as a 2d table.  Display 3 digits after the decimal point.  You can assume all of the runtimes are <= 99.999 seconds.
 * The number of repeats will be <= 14.
 *
 * The columns should each line up.  Using printf to create minimum width sizes for your printed variables should make this easier.
 */
void printRuntimeTable( functionRuntimes fRT ){
	
	int i,j;
	
	printf("%s\n", fRT.szName);
	
	printf("Test size\t");
	
	for(i = 0; i < fRT.iNumRepeats; i++)
		printf("Test #%-2d\t", i + 1);
	
	printf("Average\t\tIncrease\n");
	
	for(i = 0; i < fRT.iNumTestCaseSizes; i++)
  {	
		printf("%-9d\t", fRT.arrTestSizes[i]);
		
		for(j = 0; j < fRT.iNumRepeats; j++)
			printf("%-8.3lf\t", fRT.arrRuntimes[i][j]);
		
		printf("%-7.3lf\t\t", fRT.arrAvg[i]);
		
		if (i > 0) printf("%-8.3lf\n", fRT.arrAvg[i] / fRT.arrAvg[i-1]);
		else printf("N/A\n");
	}
	
	printf("\n\n");
}

/* TODO: TO BE COMPLETED BY YOU
 * Free all of the dynamically allocated memory in fRT
 */
void freeFunctionRuntimes( functionRuntimes fRT ){
	int i = 0;
 
	free(fRT.szName);
  free(fRT.arrAvg);
  
  for( i=0; i< fRT.iNumTestCaseSizes; i++)
    free(fRT.arrRuntimes[i]);
	free(fRT.arrRuntimes);

	free(fRT.arrTestSizes);
}