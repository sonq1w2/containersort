



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MEASURE_TIME	// to measure execution time
// from GJANG: not sure if the time measurement code works with Windows
// If it works, execution time will be printed.
// Otherwise, comment out the line "#define MEASURE_TIME" and compile again.

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// definition of CONTAINER unit
/////////////////////////////////////////////////////////////////////
#define CONTAINER_SIZE	512

struct CONTAINER {
  int key;
  float  fval[CONTAINER_SIZE];
  double dval[CONTAINER_SIZE];
};

/////////////////////////////////////////////////////////////////////
// generate container
// fill fval and dval with key
/////////////////////////////////////////////////////////////////////
void generatecontainer(struct CONTAINER *c, int key)
{
  int i;
  c->key = key;
  for (i=0; i<CONTAINER_SIZE; i++) {
    c->fval[i] = (float)key;
    c->dval[i] = (double)key;
  }
}

/////////////////////////////////////////////////////////////////////
// check the container
// assumption: all the fval and dval array items be the same as key
// because checking all the elements takes too much time
// randomly choose an index, and compare fval[i] and dval[i] with key,
// returns -1 if they are the same as key
// and returns that index if any of them different
/////////////////////////////////////////////////////////////////////
int validate_container_item(const struct CONTAINER *c)
{
  int i;
  i = (random()%CONTAINER_SIZE);
  if ( c->key != (int)c->fval[i]) { return i; }
  else if ( c->key != (int)c->dval[i]) { return i; }
  else return -1;
}

/////////////////////////////////////////////////////////////////////
// use the functions below to copy and swap CONTAINERs
/////////////////////////////////////////////////////////////////////
void copycontainer(const struct CONTAINER *src, struct CONTAINER *dst)
{
  int i;
  for (i=0; i<CONTAINER_SIZE; i++) dst->fval[i] = src->fval[i];
  for (i=0; i<CONTAINER_SIZE; i++) dst->dval[i] = src->dval[i];
  dst->key = src->key;
}

void swap_container(struct CONTAINER *c1, struct CONTAINER *c2)
{
if (c1==c2) return;

  struct CONTAINER tmp;
  copycontainer(c1,&tmp);
  copycontainer(c2,c1);
  copycontainer(&tmp,c2);
}


/////////////////////////////////////////////////////////////////////
// print key values only
/////////////////////////////////////////////////////////////////////
void print_container_array(const struct CONTAINER C[], int N)
{
  int i;
  for (i=0; i<N; i++) fprintf(stdout, "%d\n", C[i].key);
}


void swap(int* a, int* b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
 
void quicksortWithindex(int* array,int* array2, int start, int end){
 
    if(start>=end) return;
 
    int mid=(start+end)/2;
    int pivot=array[mid];
 
    swap(&array[start],&array[mid]);
 	swap(&array2[start],&array2[mid]);
    int p=start+1,q=end;
 
    while(1){
        while(array[p]<=pivot){ p++; }
        while(array[q]>pivot){ q--; }
 
        if(p>q) break;
 
        swap(&array[p],&array[q]);
	swap(&array2[p],&array2[q]);
    }
 
    swap(&array[start],&array[q]);
 	swap(&array2[start],&array2[q]);
    quicksortWithindex(array,array2,start,q-1);
    quicksortWithindex(array,array2,q+1,end);
 
}



/////////////////////////////////////////////////////////////////////
// midterm problem 3
/////////////////////////////////////////////////////////////////////
int main()
{
  int i, N,a;
  int val;
  int check;

  // CONTAINER storage
  struct CONTAINER *C;
struct CONTAINER tmp;
int tmp2;
  // index arrays for sorting by keys
  int *K;	// array for key values
  int *I;	// array for indexes
  int *J;	// hint: array for inverted indexes

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;

  start = clock();
#endif

  // 0. read input 
  fscanf(stdin, "%d", &N);

  // allocate containers and read key values
  C = (struct CONTAINER*) malloc(sizeof(struct CONTAINER)*N);
  for (i=0; i<N; i++) {
    if ( fscanf(stdin, "%d", &val) != 1 ) {
      fprintf(stderr, "cannot read integer from standard input.\n");
      free(C);
      exit(0);
    }
    else { generatecontainer(C+i,val); }
  }

  // allocate spaces for indexes
  K = (int*)malloc(sizeof(int)*N);
  I = (int*)malloc(sizeof(int)*N);
  J = (int*)malloc(sizeof(int)*N);

 for (i=0;i<N;i++){
	K[i]=C[i].key;
	I[i]=i;
	J[i]=i;
	}

	quicksortWithindex(K,I,0,N-1);
	quicksortWithindex(I,J,0,N-1);



	
for (i=0;i<N;i++){
	while (J[i]!=i){
		tmp2=J[J[i]];
		tmp=C[J[i]];
		C[J[i]]=C[i];
		J[J[i]]=J[i];
		J[i]=tmp2;
		C[i]=tmp;}

}

  // 1. sort keys with index
  //  (output) K: sorted key value array
  //  (output) I: index generated by sorting, such that K[i] == C[I[i]].key
  //  (output) J: inverted index, such that K[J[i]] == C[i].key
  //              (the inverted index set J may not be necessary
  //              depending on your method)

  // 2. re-order containers by I or J

  /////////////////////////////////////////////////////////////////////
  // end of ***FILL***
  /////////////////////////////////////////////////////////////////////

  // check if the container items are all correct
  for (i=0, check=0; i<N; i++) {
    val = validate_container_item(C+i);
    if ( val >= 0 ) {
      fprintf(stderr,"validation failed at C[%d]: %d %.1f %.1lf\n",
	  i, C[i].key, C[i].fval[val], C[i].dval[val]);
    }
    else check++;
  }
  if ( check != N ) {
    fprintf(stderr,
	"Check failed: %d/%d (%.1f%%) container items are not valid\n",
	N-check,N,(double)(N-check)/(double)N);
  }

  // print sorted key values
 print_container_array(C,N);

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,">> Execution time: %.5f seconds\n",cpu_time_used);
#endif

  // free memory
  free(K);
  free(I);
  free(J);
  free(C);

  return 0;
}

