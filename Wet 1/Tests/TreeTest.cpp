#include "../AVLTree.h"
#include "../testing.h"
#include <ctime>
#include <iostream>

using namespace std;
class intCompare {
public:
	intCompare() {}
	~intCompare() {}
	bool operator()(int a, int b)
	{
		if (a < b)
			return true;
		return false;
	}
};
bool InOrderTest() {
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree.getSize());
	int i = 5;
	tree.insert(i);
	i = 3;
	tree.insert(i);
	i = 1;
	tree.insert(i);
	i = 4;
	tree.insert(i);
	i = 20;
	tree.insert(i);
	i = 23;
	tree.insert(i);
	int* inOrderArray = (tree.inOrder());
	ASSERT_EQUALS(6, tree.getSize());
	ASSERT_EQUALS(1, inOrderArray[0]);
	ASSERT_EQUALS(3, inOrderArray[1]);
	ASSERT_EQUALS(4, inOrderArray[2]);
	ASSERT_EQUALS(5, inOrderArray[3]);
	ASSERT_EQUALS(20, inOrderArray[4]);
	ASSERT_EQUALS(23, inOrderArray[5]);

	delete[](inOrderArray);
	return true;
}

bool InsertTest() {

	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree.getSize());
	int i = 5;
	tree.insert(i);

	int* first = (tree.inOrder());
	ASSERT_EQUALS(1, tree.getSize());
	ASSERT_EQUALS(i, *first);
	delete[](first);
	i = 3;
	tree.insert(i);

	int* second = (tree.inOrder());
	ASSERT_EQUALS(2, tree.getSize());
	ASSERT_EQUALS(i, second[0]);
	ASSERT_EQUALS(5, second[1]);

	i = 1;
	tree.insert(i);

	int* third = (tree.inOrder());
	ASSERT_EQUALS(3, tree.getSize());
	ASSERT_EQUALS(1, third[0]);
	ASSERT_EQUALS(3, third[1]);
	ASSERT_EQUALS(5, third[2]);

	i = 4;
	tree.insert(i);

	int* fourth = (tree.inOrder());
	ASSERT_EQUALS(4, tree.getSize());
	ASSERT_EQUALS(1, fourth[0]);
	ASSERT_EQUALS(3, fourth[1]);
	ASSERT_EQUALS(4, fourth[2]);
	ASSERT_EQUALS(5, fourth[3]);

	i = 20;
	tree.insert(i);

	int* fifth = (tree.inOrder());
	ASSERT_EQUALS(5, tree.getSize());
	ASSERT_EQUALS(1, fifth[0]);
	ASSERT_EQUALS(3, fifth[1]);
	ASSERT_EQUALS(4, fifth[2]);
	ASSERT_EQUALS(5, fifth[3]);
	ASSERT_EQUALS(20, fifth[4]);

	i = 23;
	tree.insert(i);
	int* sixth = (tree.inOrder());
	ASSERT_EQUALS(6, tree.getSize());
	ASSERT_EQUALS(1, sixth[0]);
	ASSERT_EQUALS(3, sixth[1]);
	ASSERT_EQUALS(4, sixth[2]);
	ASSERT_EQUALS(5, sixth[3]);
	ASSERT_EQUALS(20, sixth[4]);
	ASSERT_EQUALS(23, sixth[5]);

	delete[](second);
	delete[](third);
	delete[](fourth);
	delete[](fifth);
	delete[](sixth);


	return true;

}


bool FindTest() {
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree.getSize());
	int i = 5;
	tree.insert(i);
	i = 3;
	tree.insert(i);
	i = 1;
	tree.insert(i);
	i = 4;
	tree.insert(i);
	i = 20;
	tree.insert(i);
	i = 23;
	tree.insert(i);
	avlNode<int, intCompare>* node;
	ASSERT_EQUALS(6, tree.getSize());
	i = 1;
	node = tree.find(i);
	ASSERT_EQUALS(1, node->getData());
	i = 3;
	ASSERT_EQUALS(3, tree.find(i)->getData());
	i = 4;
	ASSERT_EQUALS(4, tree.find(i)->getData());
	i = 5;
	ASSERT_EQUALS(5, tree.find(i)->getData());
	i = 20;
	ASSERT_EQUALS(20, tree.find(i)->getData());
	i = 23;
	ASSERT_EQUALS(23, tree.find(i)->getData());
	i = 60;
	ASSERT_EQUALS(true, tree.find(i) == NULL);
	return true;
}


bool removeTest() {
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree.getSize());
	for (int i = 1; i <= 15; i++) {
		tree.insert(i);
		ASSERT_EQUALS(i, tree.getSize());
	}
	int* arr0 = tree.inOrder();
	for (int i = 0; i < 15; i++) {
		ASSERT_EQUALS(i + 1, arr0[i]);
	}

	int x = 13;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(14, tree.getSize());
	int* arr = tree.inOrder();
	for (int i = 0; i < 12; i++) {
		ASSERT_EQUALS(i + 1, arr[i]);
	}
	ASSERT_EQUALS(14, arr[12]);
	ASSERT_EQUALS(15, arr[13]);

	x = 10;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(13, tree.getSize());
	int* arr2 = tree.inOrder();
	for (int i = 0; i < 9; i++) {
		ASSERT_EQUALS(i + 1, arr2[i]);
	}
	ASSERT_EQUALS(11, arr2[9]);
	ASSERT_EQUALS(12, arr2[10]);
	ASSERT_EQUALS(14, arr2[11]);
	ASSERT_EQUALS(15, arr2[12]);

	x = 14;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(12, tree.getSize());
	int* arr3 = tree.inOrder();
	for (int i = 0; i < 9; i++) {
		ASSERT_EQUALS(i + 1, arr3[i]);
	}
	ASSERT_EQUALS(11, arr3[9]);
	ASSERT_EQUALS(12, arr3[10]);
	ASSERT_EQUALS(15, arr3[11]);

	x = 15;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(11, tree.getSize());
	int* arr4 = tree.inOrder();
	for (int i = 0; i < 9; i++) {
		ASSERT_EQUALS(i + 1, arr4[i]);
	}
	ASSERT_EQUALS(11, arr4[9]);
	ASSERT_EQUALS(12, arr4[10]);

	x = 11;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(10, tree.getSize());
	int* arr5 = tree.inOrder();
	for (int i = 0; i < 9; i++) {
		ASSERT_EQUALS(i + 1, arr5[i]);
	}
	ASSERT_EQUALS(12, arr5[9]);

	x = 12;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(9, tree.getSize());
	int* arr6 = tree.inOrder();
	for (int i = 0; i < 9; i++) {
		ASSERT_EQUALS(i + 1, arr6[i]);
	}

	x = 4;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(8, tree.getSize());
	int* arr7 = tree.inOrder();
	ASSERT_EQUALS(1, arr7[0]);
	ASSERT_EQUALS(2, arr7[1]);
	ASSERT_EQUALS(3, arr7[2]);
	ASSERT_EQUALS(5, arr7[3]);
	ASSERT_EQUALS(6, arr7[4]);
	ASSERT_EQUALS(7, arr7[5]);
	ASSERT_EQUALS(8, arr7[6]);
	ASSERT_EQUALS(9, arr7[7]);

	x = 5;
	cout << "removing " << x << "\n";
	cout << "----------------------\n";
	tree.remove(x);
	ASSERT_EQUALS(7, tree.getSize());
	int* arr8 = tree.inOrder();
	ASSERT_EQUALS(1, arr8[0]);
	ASSERT_EQUALS(2, arr8[1]);
	ASSERT_EQUALS(3, arr8[2]);
	ASSERT_EQUALS(6, arr8[3]);
	ASSERT_EQUALS(7, arr8[4]);
	ASSERT_EQUALS(8, arr8[5]);
	ASSERT_EQUALS(9, arr8[6]);

	avlTree<int, intCompare> tree2 = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree2.getSize());
	int vals[12] = { 50, 25, 75, 15, 40, 60, 80, 35, 55, 65, 90, 62 };
	int valsOrder[12] = { 15, 25, 35, 40, 50, 55, 60, 62, 65, 75, 80, 90 };
	int valsOrder2[11] = { 25, 35, 40, 50, 55, 60, 62, 65, 75, 80, 90 };
	for (int i = 0; i < 12; i++) {
		tree2.insert(vals[i]);
	}
	int* tree2InOrder = tree2.inOrder();
	for (int i = 0; i < 12; i++) {
		int x = tree2InOrder[i];
		int y = valsOrder[i];
		ASSERT_EQUALS(x, y);
	}

	x = 15;
	tree2.remove(x);
	int* tree2InOrder2 = tree2.inOrder();
	for (int i = 0; i < 11; i++) {
		int x = tree2InOrder2[i];
		int y = valsOrder2[i];
		ASSERT_EQUALS(x, y);
	}
	delete[](arr);
	delete[](arr0);
	delete[](arr2);
	delete[](arr3);
	delete[](arr4);
	delete[](arr5);
	delete[](arr6);
	delete[](arr7);
	delete[](arr8);
	delete[](tree2InOrder);
	delete[](tree2InOrder2);
	return true;
}

bool clearTest() {
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(0, tree.getSize());
	for (int i = 1; i <= 15; i++) {
		tree.insert(i);
		ASSERT_EQUALS(i, tree.getSize());
	}
	tree.clear();
	ASSERT_EQUALS(0, tree.getSize());

	return true;
}

bool isSorted(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			return false;
		}
	}
	return true;
}

bool BigInsertTest()
{
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(true, tree.isEmpty());
	int num = 999999;
	bool* isInsereted = new bool[num];
	for (int i = 0; i < num; i++)
	{
		isInsereted[i] = false;
	}

	for (int i = 0; i < num; i++)
	{
		int numToInsert = i;
		bool expected = !isInsereted[numToInsert];
		bool actual = tree.insert(numToInsert);
		ASSERT_EQUALS(expected, actual);
		if (actual)
		{
			isInsereted[numToInsert] = true;
		}
		if (i + 3 < num)
		{
			numToInsert = i + 3;
			expected = !isInsereted[numToInsert];
			actual = tree.insert(numToInsert);
			ASSERT_EQUALS(expected, actual);
			if (actual)
			{
				isInsereted[numToInsert] = true;
			}
		}

		if (i - 4 > 0)
		{
			numToInsert = i - 4;
			expected = !isInsereted[numToInsert];
			actual = tree.insert(numToInsert);
			ASSERT_EQUALS(expected, actual);
			if (actual)
			{
				isInsereted[numToInsert] = true;
			}
		}
		if (i % 7 > 0)
		{
			numToInsert = i % 7;
			expected = !isInsereted[numToInsert];
			actual = tree.insert(numToInsert);
			ASSERT_EQUALS(expected, actual);
			if (actual)
			{
				isInsereted[numToInsert] = true;
			}
		}





	}
	int* array = tree.inOrder();
	bool isSort = isSorted(array, tree.getSize());
	ASSERT_EQUALS(true, isSort);

	delete[] array;
	delete[] isInsereted;

	return true;
}


bool BigRemoveTest()
{
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	ASSERT_EQUALS(true, tree.isEmpty());
	int num = 100000;
	bool* isInsereted = new bool[num];
	for (int i = 0; i < num; i++)
	{
		isInsereted[i] = false;
	}

	for (int i = 0; i < num; i++)
	{
		int numToInsert = i;
		bool expected = !isInsereted[numToInsert];
		bool actual = tree.insert(numToInsert);
		ASSERT_EQUALS(expected, actual);
		if (actual)
		{
			isInsereted[numToInsert] = true;
		}


	}
	int* array = tree.inOrder();
	bool isSort = isSorted(array, tree.getSize());
	ASSERT_EQUALS(true, isSort);

	int numToRemove = rand() % num;
	cout << "Going to remove: " << numToRemove << " nodes from the tree" << endl;
	for (int i = 0; i < numToRemove; i++)
	{
		int randomToRemove = rand() % numToRemove;
		bool expected = isInsereted[randomToRemove];
		bool actual = tree.remove(randomToRemove);
		ASSERT_EQUALS(expected, actual);
		if (actual)
		{
			isInsereted[randomToRemove] = false;
		}
	}

	int* array2 = tree.inOrder();
	bool isSort2 = isSorted(array2, tree.getSize());
	ASSERT_EQUALS(true, isSort2);

	delete[] array;
	delete[] array2;
	delete[] isInsereted;

	return true;
}

bool BuildEmptyTest()
{
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	tree.buildEmpty(25);
	ASSERT_EQUALS(25, tree.getSize());

	return true;
}
bool BuildEmptyAndInorderInsertTest()
{
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	tree.buildEmpty(8);
	ASSERT_EQUALS(8, tree.getSize());
	int array1[8] = { 0,1,2,3,4,5,6,7 };
	int index = 0;
	tree.inOrderInsert(array1, &index);
	int* array2 = tree.inOrder();
	for (int i = 0; i < tree.getSize(); i++)
		ASSERT_EQUALS(i, array2[i]);
	delete[] array2;

	int num = 8;
	tree.insert(num);
	num = 9;
	tree.insert(num);

	int* array3 = tree.inOrder();
	for (int i = 0; i < tree.getSize(); i++)
		ASSERT_EQUALS(i, array3[i]);
	delete[] array3;


	return true;
}

bool InsertClearBuildEmptyAndInorderInsertTest()
{
	avlTree<int, intCompare> tree = avlTree<int, intCompare>();
	int i = 3;
	tree.insert(i);
	i = 4;
	tree.insert(i);
	i = 1;
	tree.insert(i);
	i = 2;
	tree.insert(i);
	i = 32;
	tree.insert(i);
	i = 10;
	tree.insert(i);
	ASSERT_EQUALS(6, tree.getSize());
	tree.clear();
	ASSERT_EQUALS(0, tree.getSize());

	tree.buildEmpty(7);
	ASSERT_EQUALS(7, tree.getSize());
	int array1[7] = { 0,1,2,3,4,5,6 };
	int index = 0;
	tree.inOrderInsert(array1, &index);
	int* array2 = tree.inOrder();
	for (int i = 0; i < 7; i++)
		ASSERT_EQUALS(i, array2[i]);

	delete[] array2;

	return true;
}
int main()
{
	srand(time(0));
	RUN_TEST(InOrderTest);
	RUN_TEST(InsertTest);
	RUN_TEST(FindTest);
	RUN_TEST(removeTest);
	RUN_TEST(clearTest);
	RUN_TEST(BuildEmptyTest);
	RUN_TEST(BuildEmptyAndInorderInsertTest);
	RUN_TEST(InsertClearBuildEmptyAndInorderInsertTest);
	RUN_TEST(BigInsertTest);
	RUN_TEST(BigRemoveTest);
	return 0;
}
