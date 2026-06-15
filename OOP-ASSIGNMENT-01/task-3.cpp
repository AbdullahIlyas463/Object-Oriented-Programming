#include <iostream>
using namespace std;

int main() 
{
   int rows, cols;

   cout << "Enter number of rows: ";
   cin >> rows;
   while (rows < 0)
   {
       cout << "Invalid.\nEnter again : ";
       cin >> rows;
   }
   cout << "Enter number of columns: ";
   cin >> cols;
   while (cols < 0)
   {
       cout << "Invalid.\nEnter again : ";
       cin >> cols;
   }

   int** warehouse = new int* [rows];
   for (int i = 0; i < rows; i++) {
       *(warehouse+i) = new int[cols];
   }

   cout << "Enter elements:"<<endl;
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           cin >> *(*(warehouse + i) + j);
       }
   }

   cout << "Actual 2-d array:"<<endl;
   for (int i = 0; i < rows; i++) 
   {
       for (int j = 0; j < cols; j++) 
           cout<< *(*(warehouse+i)+j)<<" ";
       cout << endl;
   }

   int* itemCount = new int[rows];

   for (int i = 0; i < rows; i++) 
   {
       *(itemCount+i) = 0;
       for (int j = 0; j < cols; j++) 
       {
           if (*(*(warehouse + i) + j) != 0) 
           {
              ( *(itemCount + i))++;
           }
       }
   }


   int** compactList = new int* [rows];

   for (int i = 0; i < rows; i++) {
       *(compactList+i) = new int[*(itemCount+i)];
       int index = 0;

       for (int j = 0; j < cols; j++) {
           if (*(*(warehouse + i) + j) != 0) {
               compactList[i][index++] = *(*(warehouse + i) + j);
           }
       }
   }

 
   cout << "\nCompact Pick List:\n";
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < itemCount[i]; j++) {
           cout << compactList[i][j] << " ";
       }
       cout << endl;
   }

 
   for (int i = 0; i < rows; i++) {
       delete[] *(warehouse+i);
       delete[] *(compactList+i);
   }
   delete[] warehouse;
   delete[] compactList;
   delete[] itemCount;

   return 0;
}