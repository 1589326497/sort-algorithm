#include<stdio.h>
#include<malloc.h>
#include"stack.h"

//插入排序 升序
//时间复杂度O(N^2)
//[0,end]有序，end+1位置的值插入[0,end],让[0,end+1]有序

void InsertSort(int* a,int n)  
{
	for (int i = 0; i < n - 1; i++)	//数组大小为n,如果i<n，i到最后为数组的尾数，end+1就会越界
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)	//插入的值小 向后挪 
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
	
}

/*
	希尔排序
	直接插入排序的优化
	1.先进行预排序，让数组接近有序
	2.直接插入排序
	时间复杂度O(N*logN)

*/

void ShellSort(int* a,int n)
{
	int gap=n;
	while (gap > 1)		//gap>1时都是预排序，gap=1时就是直接插入排序
	{ 
		gap /= 2; //保证最后一次为1
		for (int i = 0; i < n - gap; i++)   //把间隔为gap的多组数据同时排序
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}



/*
	堆排序
	向下调整算法 建小堆
	前提：左右子树都是小堆
	1.选出左右孩子中小的那一个
	2.与父亲比较，如果比父亲小就交换
	3.然后继续往下调，调到叶子节点就停止 
*/
#if 1
void Swap(int* p1, int* p2);
//小堆调整 向下调整
void AdjustDwon(int* a, int n,int root)
{
	
	int parent = root;
	int child = parent * 2 + 1;//默认为左孩子
	while (child < n)   //child向下调整不能超出范围，到叶子结束
	{
		if ((child + 1 < n) && a[child] > a[child+1]) //选出小的儿子,(child+1<n) 防止越界
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);//儿子与父亲交换
			parent = child;    //向下调整
			child = parent * 2 + 1;  //新父亲的儿子
		}
		else
		{
			break;   //小儿子比父亲大，跳出循环
		}

	}
}
void HeapSort(int* a, int n)  //堆排序
{
	//完全小堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)//i为最后一个叶节点的父亲,为根
	{
		AdjustDwon(a, n, i);
	}
	int end = n - 1; //end为总数
	while (end > 0)
	{
		Swap(&a[0], &a[end]); //第一个数与最后一个数交换
		AdjustDwon(a, end, 0); //向下调整
		end--;       //将交换后的尾数屏蔽，不看作堆的成员
	}

}

#endif


/*
	直接选择排序 
	时间复杂度 0（N^2）
	第一次遍历N 第二次遍历 N-2
*/
void SelectSort(int* a,int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = end;
		for (int i = begin; i <= end; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;              //保存最小值下标
			}
			if (a[i] > a[maxi])
			{
				maxi = i;			   //保存最大值下标
			}
		}
		Swap(a[begin], a[mini]); 
		if (maxi == begin)    //特殊情况begin和maxi在同一位置时，需修正,a[begin]已经与a[mini]交换 main为指向大的数
		{
			maxi = mini;   //修正maxi为指向a[main]
		}
		Swap(a[end], a[maxi]);
		begin++;
		end--;
	}
}



/*
	冒泡函数
	时间复杂度0(N^2)
	和直接插入相比 直接插入更好，插入排序是0（N^2）排序中最好的
*/
void BubbleSort(int* a, int n)
{
	for (int j = 1; j < n; j++)
	{
		int exchange=0;
		for (int i = 0; i < n- j; i++)  //一遍冒泡排序
		{
			if (a[i] > a[i + 1])
			{ 
				Swap(&a[i], &a[i + 1]);
				exchange = 1;
			}
		}
		if (exchange==0)   //已经排好了跳出循环
		{
			break;
		}

	}
	
}


/*
	快速排序
	时间复杂度0(N*logN)
	有序或逆序为最坏时间复杂度为0（N^2）
	最好情况key为中间值（不是最大，也不是最小）
*/


//三数取中间
void Swap(int* p1, int* p2);
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) >> 1;//右移一位相当于除2 
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else if (a[left] > a[right])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	else//(a[left] > a[mid])
	{
		if (a[left] < a[right])
		{
			return left;
		}
		else if (a[right] > a[mid])
		{
			return mid;
		}
		else
		{
			return right;
		}
	}
}

int  PartSort1(int* a, int left, int right)  //挖坑法单次排序
{
	//取中间数
	//int  index = GetMidIndex(a, left, right); //取中间值
	//Swap(&a[left], &a[index]); //中间值与left交换，保证key是中间值

	int begin = left, end = right;
	int pit = begin;		//选择最左边为坑
	int key = a[begin];
	while (begin < end)
	{
		while (begin < end && a[end] >= key)  //右边找小放到左边
		{
			end--;
		}
		a[pit] = a[end];   //找到小把小放到坑里
		pit = end;         //原来的位置变成新的坑
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		a[pit] = a[begin];
		pit = begin;
	}
	pit = begin;
	a[pit] = key;
	return pit;
}

int PartSort2(int* a, int left, int right)//挖坑法的变形，左右指针法单次排序
{
	int  index = GetMidIndex(a, left, right); //取中间值
	Swap(&a[left], &a[index]); //中间值与left交换，保证key是中间值

	int begin = left, end = right;
	int keyi = begin;		//选择最左边为坑
	while (begin < end)
	{
		while (begin < end && a[end]>=a[keyi]) //找小
		{
			end--;
		}
		while (begin < end&& a[begin] <= a[keyi]) //找大
		{
			begin++;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[keyi]);
	return begin;
}

int PartSort3(int* a, int left, int right)//前后指针法单次排序
{
	int  index = GetMidIndex(a, left, right); //取中间值
	Swap(&a[left], &a[index]); //中间值与left交换，保证key是中间值

	int keyi = left;
	int cur = left+1; //前指针
	int prev = left;  //后指针
	while (cur<= right)
	{
		if (a[cur] < a[keyi]&& prev !=cur)
		{
			prev++;
			Swap(&a[cur], &a[prev]);
		}
		cur++;
	}
	Swap(&a[keyi], &a[prev]);
	return prev;
}

void QuicSort(int* a, int left, int right) //坑排序
{
	if (left >= right)  //left等于right时停止递归
	{
		return;
	}
	int pit = PartSort3(a, left, right);
	
	//[left,right]
	//[left,pit-1] pit [pit+1,right]两个区间递归
	if (pit - 1 - left+1 > 10) //区间大于10个数，递归
	{
		QuicSort(a, left, pit - 1);
		
	}
	else
	{
		//小区间优化
		InsertSort(a + left, pit - 1 - left + 1);//a + left为数组开始位置
	}
	if (right - (pit + 1) + 1 > 10)
	{
		QuicSort(a, pit + 1, right);
	}
	else
	{
		InsertSort(a + pit + 1, right - (pit + 1) + 1);
	}
}


//非递归 快速排序
//如果栈帧深度太深，递归可能会导致栈溢出
//递归改非递归 1，直接改循环  2，借助数据结构的栈进行模拟
void QuickSortNonR(int* a, int n)
{
	ST st;
	StackInit(&st);
	StackPush(&st, n - 1);
	StackPush(&st,0);

	while (!StackEmpty(&st))
	{
		int left = StackTop(&st);
		StackPop(&st);
		int right = StackTop(&st);
		StackPop(&st);

		int keyIndex = PartSort1(a, left, right);
		//[left,keyIndex-1] keyIndex [keyIndex+1,right]
		
		if (keyIndex + 1 < right) //keyIndex + 1 < right说明区间的值大于不止一个
		{
			StackPush(&st, right); 
			StackPush(&st, keyIndex + 1);  //右区间入栈
		}
		if (left < keyIndex - 1)
		{
			StackPush(&st, keyIndex - 1);
			StackPush(&st, left);		   //左区间入栈
		}
	}

	StackDestory(&st);
}




/*
	归并排序
	归并排序，也叫外排序，可以对外存排序
	时间复杂度o(N*logN)
*/
#if 1
void _MergeSort(int* a, int left, int right,int* tmp) //子函数
{
	if (left >= right)  //left=right时重合，只有一个数
		return;
	int mid = (left + right) >> 1;
	//假设[left,mid][mid+1,right]有序开始递归
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	//归并
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2) //两段begin有一个到尾就结束
	{
		if (a[begin1] < a[begin2])  //两段开始比较
		{
			tmp[index++] = a[begin1++]; //小的放入数组
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)  //元素个数长的那一组在转移数据
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	for (int i = left; i <= right; i++)	//将临时数组的数据拷贝到a[]中
	{
		a[i] = tmp[i];
	}
}

void MergeSort(int* a, int n)
{
	int* tmp =(int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);
	tmp = NULL;
}
 
//归并非递归版
//问题当数组为基数时会崩溃
//当左区间存在，右区间可能不存在

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;//归并每组数据的个数 
	while (gap<n)
	{
		for (int i = 0; i < n; i += 2 * gap)//gap为1一一归，gap为2两两归
		{
			//[i,i+gap-1][i+gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//归并过程中右半区间可能不存在
			if (begin2>=n)
			{
				break; //结束循环
			}
			//右半区间存在但右半空间算多了
			if (end2 >= n)
			{
				end2 = n - 1;//end修正到n-1
			}
			int index = i;
			while (begin1 <= end1 && begin2 <= end2) //两段begin有一个到尾就结束
			{
				if (a[begin1] < a[begin2])  //两段开始比较
				{
					tmp[index++] = a[begin1++]; //小的放入数组
				}
				else
				{
					tmp[index++] = a[begin2++];
				}
			}
			while (begin1 <= end1)  //元素个数长的那一组在转移数据
			{
				tmp[index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = a[begin2++];
			}
			//将临时数组的数据拷贝到a[]中
			for (int j = 0; j <= end2; j++)	//归并一部分拷一部分
			{
				a[j] = tmp[j];
			}
		}
		gap *= 2;
	}
	free(tmp);
}

#endif


/*
	计数排序
	时间复杂度o(N+range),适用范围只能是整形
*/
void CountSort(int* a, int n)
{
	int max = a[0];
	int min = a[0];
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	memset(count, 0, sizeof(int) * range);//数组初始化为0

	//统计次数
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;   //相对位置计数
	}
	//排序
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]--)  //次数减减
		{
			a[j++] = i + min;
		}
	}

	free(count);
	count = NULL;

}





void Swap(int* p1,int* p2) //两数交换
{
	*p1 = *p1 ^ *p2;                                                 
	*p2 = *p1 ^ *p2;
	*p1 = *p1 ^ *p2;
}
void PrintArray(int* a, int n) //打印数组
{
	for (int i = 0; i < n; i++)
	{                                                     
		printf("%d ", a[i]);
	}
	printf("\n");
}
void TestSort()  //测试案例
{
	int a[] = { 3,4,6,7,2, 9,8 };
	ShellSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main()
{
	TestSort();
	return 0;
}
