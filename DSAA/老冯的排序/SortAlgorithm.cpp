#include "iostream.h"
#include "stdio.h"

void print( int*, int );
////////////////////////////////////////////////////////////////////
// 最大公约数
int GCD( int m, int n )
{
	if (n==0) return m;

	return GCD( n, m%n );
}

int GCD1( int m, int n )
{
	int r=0;
	while ( n != 0 )
	{
		r = m%n;
		m = n;
		n = r;
	}
	return m;
}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void swap(int *a, int *b ) // 我把他的这个改成了用引用的，我有印象^_^ (@.@)~
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
///////////////////////////////////////////////////////////////////////
// Bubble
void Bubble( int *const a, int n )
{
	//a[0..n-1]
	int i, j;
	for ( i=0; i<n-1; i++ ) // i < n-1 (即:10个数只循环9趟)
		for ( j=0; j<n-1-i; j++ ) // j< n-1-i (即:10个数只作9-i次交换)
		{
			if ( a[j] > a[j+1] ) // 调整> 变成 由大到小
			{
				swap( &a[j], &a[j+1] );
			}			
		}
}
////////////////////////////////////////////////////////////////////
// Quick Sort
// a[0..n-1]
int Partition( int *const a, int low, int high )
{
	// n为待排序元素的个数
	int rc = a[low];
	int pivot = a[low];
	while ( low < high )
	{
		while ( low<high && a[high]<=pivot ) --high; // 调整>= 变成 反向排序
		a[low] = a[high];

		while ( low<high && a[low]>=pivot ) ++low; // 调整<= 变成 反向排序
		a[high] = a[low];
	}
	a[low] = rc;

	return low;
}

void QSort( int *const a, int low, int high )
{
	// n为待排序元素的个数
	if ( low < high )
	{
		int pivot = Partition( a, low, high ); // cout << "Pivot:" << pivot << '\t';
		QSort( a, low, pivot-1 );
		QSort( a, pivot+1, high );
	}
}

void QuickSort( int *const a, int n )
{
	QSort( a, 0, n-1 );
}
////////////////////////////////////////////////////////////////////
// Selection Sort
// a[0..n-1]
void SelectSort( int *const a, int n )
{
	int i, j, k;
	for ( i=0; i<n-1; i++ ) // 选择第 i 小的记录，并交换到位
	{
		j = i;
		for ( k=i+1; k<n-1; k++ ) // 在a[i..n-1]中选择关键字最小的记录
		{
			if ( a[k] < a[j] ) j = k; // "<"变">"变为 反向排序
		}
		if ( i!=j ) 
		{
			swap( &a[i], &a[j] ); //与第 i 个记录互换
		}
	}
}
////////////////////////////////////////////////////////////////////
// Heap Sort
void HeapAdjust( int *const a, int s, int m )
{
	// 已知a[s..m]中，除了a[s]之外，均满足堆定义
	// 本函数调整a[s]，使其成为一个大顶堆
	int i=0;
	int rc = a[s];
	for ( i=2*s; i<=m; i*=2 ) // 沿key值较大的孩子节点向下筛选
	{
		// 小顶堆, 将下面两个语句的>好更改后，变为大顶堆
		if ( i<m && (a[i]>a[i+1]) ) i++; // j为关键字较小的记录的下标
		if ( rc <=a[i] ) break; 
		a[i/2] = a[i]; //节点j 上提,放在其的父节点上
	}
	a[i/2] = rc; // 插入
}

void BuildHeap( int *const a, int n )
{
	// a[0..n-1]建成堆
	// 从数组最后一个元素开始向前建立堆
	int i=0;

	for ( i=n-2; i>=0; i-- )
	{
		HeapAdjust( a, i, n-1 );
	}
}

void HeapSort( int *const a, int n )
{
	// a[0..n-1]
	int i=0;
	BuildHeap( a, n );
	
	swap( &a[0], &a[n-1] ); // 互换"堆顶"和"堆底"的记录
	for ( i=n-2; i>=0; i-- )
	{
		HeapAdjust( a, 0, i ); // 从根开始调整，将 a[1..i] 重新调整为大顶堆
		swap( &a[0], &a[i] ); // 互换"堆顶"和当前的"堆底"，使已有序的记录沉积在底部
	}
}
////////////////////////////////////////////////////////////////////
// Shell Sort
/*
void ShellInsert( int *a, int dlta, int n )
{
	int i=0, j=0, k=0, rc=0;
	for ( i=dlta+1; i<n; i++ )
	{
		if ( a[i] < a[i-dlta] )
		{
			rc = a[i]; a[i] = a[i-dlta];
			for ( j=i-2*dlta; j>0 && rc<a[j]; j-=dlta )
				a[j+dlta] = a[j];
			a[j+dlta] = rc;
		}
	}
}

void ShellSort( int *a, int n )
{
	int k=0;
	int dlta[]={5,3,1};
	for ( k=0; k<n; k++ )
	{
		ShellInsert( a, dlta[k], n );
	}
}
*/
////////////////////////////////////////////////////////////////////
/*
// Merging Sort
//void Merge( int )
void MSort( int  )
void MergeSort( int *const a, int n )
{
	MSort( a, a, 0, n-1 );
}
*/
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

int main()
{
	int a[] = { 56,49,65,97,100,76,60,13,300,27 };
	int n=sizeof(a)/sizeof(int);
	cout<<n<<" numbers:"<<endl;
	print( a, n );
	cout<<"--------------------------------------"<<endl;

	// Bubble Sort:
	cout<<"Bubble:"<<endl; Bubble( a, n );
	print( a, n );
	// Quick Sort:
	cout<<"Quick Sort:"<<endl; QuickSort( a, n );
	print( a, n );
	// Select Sort:
	cout<<"Select Sort:"<<endl; SelectSort( a, n );
	print( a, n );
	// Heap Sort:
	cout<<"Heap Sort:"<<endl; HeapSort( a, n );
	print( a, n );
	// Shell sort:
	//cout<<"Shell Sort"<<endl; ShellSort(a,n);
	//print( a, n );

	cout<<endl<<"---------------------------------------"<<endl;
	cout << "GCD:" << endl;
	cout<< GCD(a[0],a[1]) <<endl;
	cout<< GCD1(a[0],a[1])<<endl;

	char *buf = new char[10];
	char *p = new (buf+10) char[10];
	char *p1 = buf;
	for ( int iiii=0; iiii<20; iiii++)
	{
		*p1 = iiii;
		p1++;
	}
	p1 = p;
	for ( iiii=0; iiii<20; iiii++)
	{
		cout<< *p1 << '\t';
		p1++;
	}
	cout<<endl;

	delete [] buf;
	delete [] p;
	buf = NULL;
	p=NULL;

	return 0;
}

void print( int *const a, int n )
{
	int i=0;
	while ( i<n )
	{
		cout << a[i] << '\t';
		i++;
	}
	cout<<endl;
}