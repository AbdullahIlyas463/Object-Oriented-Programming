#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

string trimSpaces(string s)
{
   int start = 0, end = s.length() - 1;
   while (start <= end && s[start] == ' ')
       start++;
   while (end >= start && s[end] == ' ')
       end--;
   string trimmed = "";
   for (int i = start; i <= end; i++)
   {
       trimmed += s[i];
   }
   return trimmed;
}

void splitComma(char* line, string arr[], int maxFields)
{
   string temp = "";
   int idx = 0;
   for (int i = 0; line[i] != '\0'; i++) 
   {
       if (line[i] == ',' && idx < maxFields - 1) 
       {
           arr[idx++] = trimSpaces(temp);
           temp = "";
       }
       else {
           temp += line[i];
       }
   }
   arr[idx] = trimSpaces(temp);
   while (idx < maxFields) arr[idx++] = "";
}



int toInt(string s)
{
   int x = 0;
   for (int i = 0; s[i] != '\0'; i++) {
       if (s[i] >= '0' && s[i] <= '9')
           x = x * 10 + (s[i] - '0');
       else
           return 0;
   }
   return x;
}

bool matchWord(string full, string key)
{
   for (int i = 0; key[i] != '\0'; i++)
   {
       if (full[i] != key[i])
           return false;
   }
   return true;
}

void sortMenu(string** menu, int rows)
{
   for (int i = 0; i < rows - 1; i++) {
       for (int j = 0; j < rows - 1 - i; j++) {
           bool swapNeeded = false;
           string cuisine1 = menu[j][1];
           string cuisine2 = menu[j + 1][1];
           string rest1 = menu[j][4];
           string rest2 = menu[j + 1][4];
           string cat1 = menu[j][0];
           string cat2 = menu[j + 1][0];
           int price1 = toInt(menu[j][3]);
           int price2 = toInt(menu[j + 1][3]);

           if (cuisine1 > cuisine2)
               swapNeeded = true;
           else if (cuisine1 == cuisine2 && rest1 > rest2)
               swapNeeded = true;
           else if (cuisine1 == cuisine2 && rest1 == rest2 && cat1 > cat2)
               swapNeeded = true;
           else if (cuisine1 == cuisine2 && rest1 == rest2 && cat1 == cat2 && price1 > price2)
               swapNeeded = true;
           if (swapNeeded) {
               for (int k = 0; k < 8; k++) {
                   swap(menu[j][k], menu[j + 1][k]);
               }
           }
       }
   }
}

void printMenu(string** menu, int rows)
{
   cout << "Sorted menu\n";
   for (int i = 0; i < rows; i++) {
       cout << menu[i][0] << " | " << menu[i][1] << " | "
           << menu[i][2] << " | " << menu[i][3] << " | "
           << menu[i][4] << " | " << menu[i][5] << " | "
           << menu[i][6] << endl;
   }
}

void searchCuisine(string** menu, int rows, string key)
{
   cout << "Search for: " << key << endl;
   for (int i = 0; i < rows; i++) {
       if (matchWord(menu[i][1], key))
       {
           cout << menu[i][0] << " | " << menu[i][1] << " | "
               << menu[i][2] << " | " << menu[i][3] << " | "
               << menu[i][4] << " | " << menu[i][5] << " | "
               << menu[i][6] << endl;
       }
   }
}

void exportToFile(string** menu, int rows)
{
   ofstream out("output.txt");
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < 7; j++) {
           out << menu[i][j];
           out << ", ";
       }
       out << "\n";
   }
   out.close();
   cout << "\nOutput written\n";
}

int main()
{
   ifstream fin("Q1.txt");
   if (!fin) {
       cout << "File not found!\n";
       return 0;
   }
   char fileData[100][100];
   int rowCount = 0;

   while (!fin.eof())
   {
       fin.getline(fileData[rowCount], 100);
       if (strlen(fileData[rowCount]) > 1)
       {
           rowCount++;
       }
   }
   fin.close();

   string** menu = new string * [rowCount];
   for (int i = 0; i < rowCount; i++)
   {
       menu[i] = new string[8];
   }
   for (int i = 0; i < rowCount; i++)
   {
       string fields[7];
       splitComma(fileData[i], fields, 7);
       for (int j = 0; j < 7; j++)
       {
           menu[i][j] = fields[j];
       }
       menu[i][7] = "\0";
   }
   sortMenu(menu, rowCount);
   printMenu(menu, rowCount);
   string cuisine;
   cout << "Enter cuisine you want to search: ";
   cin >> cuisine;
   searchCuisine(menu, rowCount, cuisine);
   exportToFile(menu, rowCount);
   for (int i = 0; i < rowCount; i++)
       delete[] menu[i];
   delete[] menu;

   return 0;
}