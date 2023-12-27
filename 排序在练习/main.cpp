/*
	��������ϰ 2023/4/16�տ�ʼ��2023/4/22�����
*/
#include<iostream>
#include<stack>
using namespace std;
//ֱ�Ӳ�������  ����
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
//ϣ������
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


//��ѵ������µ���
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

//������ 
void AdjustSort(int* a, int n)
{
	int end = n - 1;
	//��ȫ���
	for (int i = (end - 1) / 2; i >= 0; i--) 
	{
		AdjustDown(a,n, i);
	}
	//ѡ������
	while (end>0)
	{
		swap(a[0], a[end]);
		AdjustDown(a, end, 0);
		end -= 1;
	}
}

//ֱ��ѡ������ ����
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
		if (begin == min)    //�������begin��min��ͬһλ��ʱ��������,a[begin]�Ѿ���a[max]���� mainΪָ��С����
		{
			min = max;   //����minΪָ��a[max]
		}
		swap(a[min], a[end]);
		begin++;
		end--;
	}
}

//ð������
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

//����ȡ��
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
	��������
*/

//�ڿӷ� ����
int partSort1(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right); //����ȡ��
	swap(a[mid], a[left]);	//a[mid]��a[left]����

	int key = left;
	int pivot = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && !(a[end] < a[key]))//��С
		{
			end--;
		}
		//a[pivot] = a[end];
		swap(a[pivot], a[end]);
		pivot = end;
		while (begin < end && !(a[begin] > a[key]))//�Ҵ�
		{
			begin++;
		}
		//a[pivot] = a[begin];
		swap(a[pivot], a[begin]);
		pivot = begin;
	}
	//begin=end	ʱ
	//pivot = begin;
	//a[pivot] = key;
	return pivot;
}

//�ڿӷ� ��������ָ�뷨
int partSort2(int* a, int left, int right)
{

	int mid = GetMidIndex(a, left, right); //����ȡ��
	swap(a[mid], a[left]);	//a[mid]��a[left]����
	int begin = left;
	int end = right;
	int key = left;
	while (begin < end)
	{
		while (begin < end && a[end] >= a[key])//��С
		{
			end--;
		}
		while (begin < end && a[begin] <= a[key])//�Ҵ�
		{
			begin++;
		}
		swap(a[begin], a[end]);
	}
	//begin=end ����С���Ҵ������������ʱһ����keyС
	swap(a[begin], a[key]);
	return begin;

}

//�ڿӷ� ����ǰ��ָ�뷨
//cur�ں� cur��С ÿ��������keyС��ֵ��ͣ������prev++ ����prev��cur��ֵ���cur>rightʱ��prev��key����
int partSort3(int* a, int left, int right)
{
	int mid = GetMidIndex(a, left, right); //����ȡ��
	swap(a[mid], a[left]);	//a[mid]��a[left]����
	int key = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < a[key] && ++prev!=cur) //��С������ǰ�����++prev=cur������ָ���ص�����Ҫ����
		{
			swap(a[prev], a[cur]);
		}
		cur++;
	}
	swap(a[prev], a[key]);
	return prev;
}


//������ ����
void QuickSort(int* a, int left, int right)
{
	if (left >= right) //left==rightʱ Ϊ����
	{
		return;
	}
	int KeyIndex = partSort3(a, left, right);


	//���εݹ� С�����Ż�
	//[left,KeyIndex-1] KeyIndex [KeyIndex+1,right]
	if (KeyIndex - 1 - left + 1 > 10) //����10����
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
	�ǵݹ�Ŀ�������
	�ݹ�ᴴ��ջ֡���ܻᵼ��ջ���
	�ݹ�ķǵݹ飺1��ֱ�Ӹ�ѭ��		 2���������ݽṹջģ��ݹ����
*/
void QuickSortNonR(int* a, int left, int right)
{
	stack<int> s; //ջ����
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
	�鲢���� ���� O(NlogN)
	�鲢����Ҳ��������
	����10��G��������Ӳ������Ҫ��������ţ�
	��10G���ݷֳ�10��1G�������ںϲ�
*/
void _MergeSort(int* a, int left, int right,int*temp)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	//[left,mid][mid+1,right]����
	_MergeSort(a, left, mid, temp);
	_MergeSort(a, mid + 1, right, temp);

	//���ʱ���������
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
	//��û�����������ʣ�µ�Ԫ�ؿ�����temp��
	while (begin1 <= mid)
	{
		temp[Index++] = a[begin1++];
	}
	while (begin2 <= right)
	{
		temp[Index++] = a[begin2++];
	}
	//����ʱ���鿽����a������
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
	�鲢�ķǵݹ�
*/

void MergeSortNonR(int* a, int left, int right)
{
	int size = right - left + 1;
	int* temp = new int[size];
	int gap = 1;//ÿ�����ݵĸ���
	while (gap < size)
	{
		
		for (int i = 0; i < size; i += 2 * gap)
		{
			//[i,i+ gap-1] [i+ gap,i+2*gap-1]
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			int Index = i;

			//�鲢�������Ұ�������ܲ�����
			if (begin2 >= size)
			{
				break; //����ѭ��
			}
			//�Ұ�������ڵ��Ұ�ռ������
			if (end2 >= size)
			{
				end2 = size - 1;//end������n-1
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
			//��û�����������ʣ�µ�Ԫ�ؿ�����temp��
			while (begin1 <= end1)
			{
				temp[Index++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				temp[Index++] = a[begin2++];
			}
			//����ʱ���鿽����a������
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
	��������
	123 45 12 9 88 43
	���ηֱ�ȡ���ǵĸ�λ��ʮλ����λ...����
	��ֻ�ܶ������ţ�ûɶ���壩
*/
/*
	�������� (�ǱȽ�����)
	ʱ�临�Ӷȣ�O(N+range)
	ͳ��ÿ�������ֵĸ���
	ʹ�ô����Ϳ��������ˣ�ԭ�����ƹ�ϣ��
*/
void CountSort(int* a, int left, int right)
{
	int size = right - left + 1;
	int max = a[0];
	int min = a[0];
	for (int i = 0; i < size; i++)//ѡ������������С����
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
	int* num = new int[range](); //newһ��ռ丳Ĭ��ֵ

	//ͳ��ÿ�������ֵĸ���
	for (int i = 0; i < size; i++)
	{
		num[a[i] - min]++;	//a[i]��ƫ����min
	}
	int j = 0;
	//���ݴ�����������
	for (int i = 0; i < range; i++)
	{
		while (num[i]--)
		{
			a[j++] = i + min; //��ֵʱ����ƫ����min
		}
	}
}


//��ӡ����
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