#include<stdio.h>
#include<malloc.h>
#include"stack.h"

//�������� ����
//ʱ�临�Ӷ�O(N^2)
//[0,end]����end+1λ�õ�ֵ����[0,end],��[0,end+1]����

void InsertSort(int* a,int n)  
{
	for (int i = 0; i < n - 1; i++)	//�����СΪn,���i<n��i�����Ϊ�����β����end+1�ͻ�Խ��
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)	//�����ֵС ���Ų 
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
	ϣ������
	ֱ�Ӳ���������Ż�
	1.�Ƚ���Ԥ����������ӽ�����
	2.ֱ�Ӳ�������
	ʱ�临�Ӷ�O(N*logN)

*/

void ShellSort(int* a,int n)
{
	int gap=n;
	while (gap > 1)		//gap>1ʱ����Ԥ����gap=1ʱ����ֱ�Ӳ�������
	{ 
		gap /= 2; //��֤���һ��Ϊ1
		for (int i = 0; i < n - gap; i++)   //�Ѽ��Ϊgap�Ķ�������ͬʱ����
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
	������
	���µ����㷨 ��С��
	ǰ�᣺������������С��
	1.ѡ�����Һ�����С����һ��
	2.�븸�ױȽϣ�����ȸ���С�ͽ���
	3.Ȼ��������µ�������Ҷ�ӽڵ��ֹͣ 
*/
#if 1
void Swap(int* p1, int* p2);
//С�ѵ��� ���µ���
void AdjustDwon(int* a, int n,int root)
{
	
	int parent = root;
	int child = parent * 2 + 1;//Ĭ��Ϊ����
	while (child < n)   //child���µ������ܳ�����Χ����Ҷ�ӽ���
	{
		if ((child + 1 < n) && a[child] > a[child+1]) //ѡ��С�Ķ���,(child+1<n) ��ֹԽ��
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);//�����븸�׽���
			parent = child;    //���µ���
			child = parent * 2 + 1;  //�¸��׵Ķ���
		}
		else
		{
			break;   //С���ӱȸ��״�����ѭ��
		}

	}
}
void HeapSort(int* a, int n)  //������
{
	//��ȫС��
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)//iΪ���һ��Ҷ�ڵ�ĸ���,Ϊ��
	{
		AdjustDwon(a, n, i);
	}
	int end = n - 1; //endΪ����
	while (end > 0)
	{
		Swap(&a[0], &a[end]); //��һ���������һ��������
		AdjustDwon(a, end, 0); //���µ���
		end--;       //���������β�����Σ��������ѵĳ�Ա
	}

}

#endif


/*
	ֱ��ѡ������ 
	ʱ�临�Ӷ� 0��N^2��
	��һ�α���N �ڶ��α��� N-2
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
				mini = i;              //������Сֵ�±�
			}
			if (a[i] > a[maxi])
			{
				maxi = i;			   //�������ֵ�±�
			}
		}
		Swap(a[begin], a[mini]); 
		if (maxi == begin)    //�������begin��maxi��ͬһλ��ʱ��������,a[begin]�Ѿ���a[mini]���� mainΪָ������
		{
			maxi = mini;   //����maxiΪָ��a[main]
		}
		Swap(a[end], a[maxi]);
		begin++;
		end--;
	}
}



/*
	ð�ݺ���
	ʱ�临�Ӷ�0(N^2)
	��ֱ�Ӳ������ ֱ�Ӳ�����ã�����������0��N^2����������õ�
*/
void BubbleSort(int* a, int n)
{
	for (int j = 1; j < n; j++)
	{
		int exchange=0;
		for (int i = 0; i < n- j; i++)  //һ��ð������
		{
			if (a[i] > a[i + 1])
			{ 
				Swap(&a[i], &a[i + 1]);
				exchange = 1;
			}
		}
		if (exchange==0)   //�Ѿ��ź�������ѭ��
		{
			break;
		}

	}
	
}


/*
	��������
	ʱ�临�Ӷ�0(N*logN)
	���������Ϊ�ʱ�临�Ӷ�Ϊ0��N^2��
	������keyΪ�м�ֵ���������Ҳ������С��
*/


//����ȡ�м�
void Swap(int* p1, int* p2);
int GetMidIndex(int* a, int left, int right)
{
	int mid = (left + right) >> 1;//����һλ�൱�ڳ�2 
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

int  PartSort1(int* a, int left, int right)  //�ڿӷ���������
{
	//ȡ�м���
	//int  index = GetMidIndex(a, left, right); //ȡ�м�ֵ
	//Swap(&a[left], &a[index]); //�м�ֵ��left��������֤key���м�ֵ

	int begin = left, end = right;
	int pit = begin;		//ѡ�������Ϊ��
	int key = a[begin];
	while (begin < end)
	{
		while (begin < end && a[end] >= key)  //�ұ���С�ŵ����
		{
			end--;
		}
		a[pit] = a[end];   //�ҵ�С��С�ŵ�����
		pit = end;         //ԭ����λ�ñ���µĿ�
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

int PartSort2(int* a, int left, int right)//�ڿӷ��ı��Σ�����ָ�뷨��������
{
	int  index = GetMidIndex(a, left, right); //ȡ�м�ֵ
	Swap(&a[left], &a[index]); //�м�ֵ��left��������֤key���м�ֵ

	int begin = left, end = right;
	int keyi = begin;		//ѡ�������Ϊ��
	while (begin < end)
	{
		while (begin < end && a[end]>=a[keyi]) //��С
		{
			end--;
		}
		while (begin < end&& a[begin] <= a[keyi]) //�Ҵ�
		{
			begin++;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[keyi]);
	return begin;
}

int PartSort3(int* a, int left, int right)//ǰ��ָ�뷨��������
{
	int  index = GetMidIndex(a, left, right); //ȡ�м�ֵ
	Swap(&a[left], &a[index]); //�м�ֵ��left��������֤key���м�ֵ

	int keyi = left;
	int cur = left+1; //ǰָ��
	int prev = left;  //��ָ��
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

void QuicSort(int* a, int left, int right) //������
{
	if (left >= right)  //left����rightʱֹͣ�ݹ�
	{
		return;
	}
	int pit = PartSort3(a, left, right);
	
	//[left,right]
	//[left,pit-1] pit [pit+1,right]��������ݹ�
	if (pit - 1 - left+1 > 10) //�������10�������ݹ�
	{
		QuicSort(a, left, pit - 1);
		
	}
	else
	{
		//С�����Ż�
		InsertSort(a + left, pit - 1 - left + 1);//a + leftΪ���鿪ʼλ��
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


//�ǵݹ� ��������
//���ջ֡���̫��ݹ���ܻᵼ��ջ���
//�ݹ�ķǵݹ� 1��ֱ�Ӹ�ѭ��  2���������ݽṹ��ջ����ģ��
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
		
		if (keyIndex + 1 < right) //keyIndex + 1 < right˵�������ֵ���ڲ�ֹһ��
		{
			StackPush(&st, right); 
			StackPush(&st, keyIndex + 1);  //��������ջ
		}
		if (left < keyIndex - 1)
		{
			StackPush(&st, keyIndex - 1);
			StackPush(&st, left);		   //��������ջ
		}
	}

	StackDestory(&st);
}




/*
	�鲢����
	�鲢����Ҳ�������򣬿��Զ��������
	ʱ�临�Ӷ�o(N*logN)
*/
#if 1
void _MergeSort(int* a, int left, int right,int* tmp) //�Ӻ���
{
	if (left >= right)  //left=rightʱ�غϣ�ֻ��һ����
		return;
	int mid = (left + right) >> 1;
	//����[left,mid][mid+1,right]����ʼ�ݹ�
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	//�鲢
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2) //����begin��һ����β�ͽ���
	{
		if (a[begin1] < a[begin2])  //���ο�ʼ�Ƚ�
		{
			tmp[index++] = a[begin1++]; //С�ķ�������
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)  //Ԫ�ظ���������һ����ת������
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	for (int i = left; i <= right; i++)	//����ʱ��������ݿ�����a[]��
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
 
//�鲢�ǵݹ��
//���⵱����Ϊ����ʱ�����
//����������ڣ���������ܲ�����

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;//�鲢ÿ�����ݵĸ��� 
	while (gap<n)
	{
		for (int i = 0; i < n; i += 2 * gap)//gapΪ1һһ�飬gapΪ2������
		{
			//[i,i+gap-1][i+gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//�鲢�������Ұ�������ܲ�����
			if (begin2>=n)
			{
				break; //����ѭ��
			}
			//�Ұ�������ڵ��Ұ�ռ������
			if (end2 >= n)
			{
				end2 = n - 1;//end������n-1
			}
			int index = i;
			while (begin1 <= end1 && begin2 <= end2) //����begin��һ����β�ͽ���
			{
				if (a[begin1] < a[begin2])  //���ο�ʼ�Ƚ�
				{
					tmp[index++] = a[begin1++]; //С�ķ�������
				}
				else
				{
					tmp[index++] = a[begin2++];
				}
			}
			while (begin1 <= end1)  //Ԫ�ظ���������һ����ת������
			{
				tmp[index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = a[begin2++];
			}
			//����ʱ��������ݿ�����a[]��
			for (int j = 0; j <= end2; j++)	//�鲢һ���ֿ�һ����
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
	��������
	ʱ�临�Ӷ�o(N+range),���÷�Χֻ��������
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
	memset(count, 0, sizeof(int) * range);//�����ʼ��Ϊ0

	//ͳ�ƴ���
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;   //���λ�ü���
	}
	//����
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (count[i]--)  //��������
		{
			a[j++] = i + min;
		}
	}

	free(count);
	count = NULL;

}





void Swap(int* p1,int* p2) //��������
{
	*p1 = *p1 ^ *p2;                                                 
	*p2 = *p1 ^ *p2;
	*p1 = *p1 ^ *p2;
}
void PrintArray(int* a, int n) //��ӡ����
{
	for (int i = 0; i < n; i++)
	{                                                     
		printf("%d ", a[i]);
	}
	printf("\n");
}
void TestSort()  //���԰���
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
