/*
	排序在练习 2023/4/16日开始至2023/4/22日完成
*/
#include<iostream>
#include<stack>
using namespace std;
//直接插入排序  升序
void InsretSort(int* a,int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int temp = a[i + 1];
		while (end >= 0)
		{
			if (a[end] > temp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = temp;
	}
}
//希尔排序
void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap >1)
	{
		gap /= 2;
		for (int i = 0; i < n- gap; i++)
		{
			int end = i;
			int temp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > temp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = temp;
		}
	}
}


//大堆调整向下调整
void AdjustDown(int* a, int n,int root)
{
	int parent = root;
	int son = parent * 2 + 1;
	while (son<n)
	{
		if ((son + 1)<n && a[son] < a[son + 1])
		{
			son += 1;
		}
		if (a[son] > a[parent])
		{
			swap(a[son], a[parent]);
			parent = son;
			son = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//堆排序 
void AdjustSort(int* a, int n)
{
	int end = n - 1;
	//完全大堆
	for (int i = (end - 1) / 2; i >= 0; i--) 
	{
		AdjustDown(a,n, i);
	}
	//选择排序
	while (end>0)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end, 0);
		end -= 1;
	}
}

//直接选择排序 降序
void SelectSort(int* a, int n)
{
	int begin = 0;
	int end = n - 1;
	while (begin< end)
	{
		int max = begin;
		int min = end;
		for (int i = begin; i <= end; i++)
		{
			if (a[i] > a[max])
			{
				max = i;
			}
			if (a[i] < a[min])
			{
				min = i;
			}
		}
		swap(a[max], a[begin]);
		if (begin == min)    //特殊情况begin和min在同一位置时，需修正,a[begin]已经与a[max]交换 main为指向小的数
		{
			min = max;   //修正min为指向a[max]
		}
		swap(a[min], a[end]);
		begin++;
		end--;
	}
}

//冒泡排序
void BubbleSort(int* a, int n)
{
	int end = n - 1;
	while (end > 0)
	{
		for (int i = 0; i < end; i++)
		{
			if (a[i] > a[i + 1])
			{
				swap(a[i], a[i + 1]);
			}
		}
		end--;
	}
}

//三数取中
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) >> 2;
	if (a[left] < a[right])
	{
		if (a[mid] < a[left])
		{
			return left;
		}
		else if (a[mid] > a[left] && a[mid] < a[right])
		{
			return mid;
		}
		else
		{
			return right;
		}
	}
	else
	{
		if (a[mid] < a[right])
		{
			return right;
		}
		else if (a[mid] > a[right] && a[mid] < a[left])
		{
			return mid;
		}
		else
		{
			return left;
		}
	}
}


/*
	快速排序
*/

//挖坑法 单趟
int partSort1(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right); //三数取中
	swap(a[mid], a[left]);	//a[mid]和a[left]交换

	int key = left;
	int pivot = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && !(a[end] < a[key]))//找小
		{
			end--;
		}
		//a[pivot] = a[end];
		swap(a[pivot], a[end]);
		pivot = end;
		while (begin < end && !(a[begin] > a[key]))//找大
		{
			begin++;
		}
		//a[pivot] = a[begin];
		swap(a[pivot], a[begin]);
		pivot = begin;
	}
	//begin=end	时
	//pivot = begin;
	//a[pivot] = key;
	return pivot;
}

//挖坑法 变形左右指针法
int partSort2(int* a, int left, int right)
{

	int mid = GetMidIndex(a, left, right); //三数取中
	swap(a[mid], a[left]);	//a[mid]和a[left]交换
	int begin = left;
	int end = right;
	int key = left;
	while (begin < end)
	{
		while (begin < end && a[end] >= a[key])//找小
		{
			end--;
		}
		while (begin < end && a[begin] <= a[key])//找大
		{
			begin++;
		}
		swap(a[begin], a[end]);
	}
	//begin=end 先找小后找大所以最后相遇时一定比key小
	swap(a[begin], a[key]);
	return begin;

}

//挖坑法 变形前后指针法
//cur在后 cur找小 每次遇到比key小的值就停下来，prev++ 交换prev和cur的值最后cur>right时把prev和key交换
int partSort3(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right); //三数取中
	swap(a[mid], a[left]);	//a[mid]和a[left]交换
	int key = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < a[key] && ++prev!=cur) //把小的数往前移如果++prev=cur那两个指针重叠不需要交换
		{
			swap(a[prev], a[cur]);
		}
		cur++;
	}
	swap(a[prev], a[key]);
	return prev;
}


//坑排序 升序
void QuickSort(int* a, int left, int right)
{
	if (left >= right) //left==right时 为有序
	{
		return;
	}
	int KeyIndex = partSort3(a, left, right);


	//分治递归 小区间优化
	//[left,KeyIndex-1] KeyIndex [KeyIndex+1,right]
	if (KeyIndex - 1 - left + 1 > 10) //大于10个数
	{
		QuickSort(a, left, KeyIndex - 1);
	}
	else
	{
		InsretSort(a + left, KeyIndex - 1 - left + 1);
	}
	if (right - (KeyIndex + 1) + 1 > 10)
	{
		QuickSort(a, KeyIndex + 1, right);
	}
	else
	{
		InsretSort(a + KeyIndex + 1, right - (KeyIndex + 1) + 1);
	}
}

/*
	非递归的快速排序
	递归会创建栈帧可能会导致栈溢出
	递归改非递归：1，直接改循环		 2，借助数据结构栈模拟递归过程
*/
void QuickSortNonR(int* a, int left, int right)
{
	stack<int> s; //栈容器
	s.push(right);
	s.push(left);
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();
		int Index = partSort1(a,left,right);
		//[left,Index-1] Index [Index+1,right]
		if (right > Index+1)
		{
			s.push(right);
			s.push(Index + 1);
		}
		if (left < Index-1)
		{
			s.push(Index - 1);
			s.push(left);
		}
	}
}

/*
	归并排序 升序 O(NlogN)
	归并排序也叫外排序
	假设10个G的数据在硬盘中需要排序，如何排？
	把10G数据分成10个1G的排完在合并
*/
void _MergeSort(int* a, int left, int right,int*temp)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	//[left,mid][mid+1,right]有序
	_MergeSort(a, left, mid, temp);
	_MergeSort(a, mid + 1, right, temp);

	//归的时候进行排序
	int begin1 = left;
	int begin2 = mid + 1;
	int Index = left;
	while (begin1 <= mid && begin2 <= right)
	{
		if (a[begin1] < a[begin2])
		{
			temp[Index++] = a[begin1++];
		}
		else
		{
			temp[Index++] = a[begin2++];
		}
	}
	//把没有走完的数组剩下的元素拷贝到temp中
	while (begin1 <= mid)
	{
		temp[Index++] = a[begin1++];
	}
	while (begin2 <= right)
	{
		temp[Index++] = a[begin2++];
	}
	//把临时数组拷贝到a数组中
	for (int i = left; i <= right; i++)
	{
		a[i] = temp[i];
	}
}
void MergeSort(int* a, int left, int right)
{
	int* temp = new int[right - left + 1];
	_MergeSort(a, left, right, temp);
	delete [] temp;
}

/*
	归并的非递归
*/

void MergeSortNonR(int* a, int left, int right)
{
	int size = right - left + 1;
	int* temp = new int[size];
	int gap = 1;//每组数据的个数
	while (gap < size)
	{
		
		for (int i = 0; i < size; i += 2 * gap)
		{
			//[i,i+ gap-1] [i+ gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			int Index = i;

			//归并过程中右半区间可能不存在
			if (begin2 >= size)
			{
				break; //结束循环
			}
			//右半区间存在但右半空间算多了
			if (end2 >= size)
			{
				end2 = size - 1;//end修正到n-1
			}

			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					temp[Index++] = a[begin1++];
				}
				else
				{
					temp[Index++] = a[begin2++];
				}
			}
			//把没有走完的数组剩下的元素拷贝到temp中
			while (begin1 <= end1)
			{
				temp[Index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				temp[Index++] = a[begin2++];
			}
			//把临时数组拷贝到a数组中
			for (int j = i; j <= end2; j++)
			{
				a[j] = temp[j];
			}
		}
		gap *= 2;
	}
	delete[] temp;
}

/*
	基数排序
	123 45 12 9 88 43
	依次分别取他们的个位，十位，百位...排序
	（只能对整数排，没啥意义）
*/
/*
	计数排序 (非比较排序)
	时间复杂度：O(N+range)
	统计每个数出现的个数
	使用次数就可以排序了（原理类似哈希表）
*/
void CountSort(int* a, int left, int right)
{
	int size = right - left + 1;
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < size; i++)//选出最大的数和最小的数
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
	int range = max - min+1;
	int* num = new int[range](); //new一块空间赋默认值

	//统计每个数出现的个数
	for (int i = 0; i < size; i++)
	{
		num[a[i] - min]++;	//a[i]减偏移量min
	}
	int j = 0;
	//根据次数进行排序
	for (int i = 0; i < range; i++)
	{
		while (num[i]--)
		{
			a[j++] = i + min; //赋值时加上偏移量min
		}
	}
}


//打印数组
void Print(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void text()
{
	int a[] = { 1,7,5,3,8,2,3,17,23,13 };
	int size = sizeof(a)/sizeof(a[0]);
	//ShellSort(a, size);
	MergeSort(a, 0, size - 1);
	Print(a, size);
}
int main()
{
	text();
	return 0;
}