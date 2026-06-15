#include <iostream>
#include <cstring>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class Item
{
public:
   char name[50];
   int price;
   char** attrName;
   char** attrValue;
   int attrCount;

   Item()
   {
       name[0] = '\0';
       price = 0;
       attrName = nullptr;
       attrValue = nullptr;
       attrCount = 0;
   }
};

class Cart
{
public:
   Item* items;
   int itemCount;

   Cart()
   {
       items = nullptr;
       itemCount = 0;
   }
};

int totalCartValue(Cart& cart)
{
   int sum = 0;
   for (int i = 0; i < cart.itemCount; i++)
   {
       sum += cart.items[i].price;
   }
   return sum;
}

float avgCartValue(Cart& cart)
{
   if (cart.itemCount == 0)
   {
       return 0;
   }
   return (float)totalCartValue(cart) / cart.itemCount;
}

void clearCart(Cart& cart)
{
   delete[] cart.items;
   cart.items = nullptr;
   cart.itemCount = 0;
}

void addItem(Cart& cart, const char name[], int price)
{
   Item* newArr = new Item[cart.itemCount + 1];

   for (int i = 0; i < cart.itemCount; i++)
   {
       newArr[i] = cart.items[i];
   }

   strcpy(newArr[cart.itemCount].name, name);
   newArr[cart.itemCount].price = price;
   newArr[cart.itemCount].attrName = nullptr;
   newArr[cart.itemCount].attrValue = nullptr;
   newArr[cart.itemCount].attrCount = 0;

   delete[] cart.items;
   cart.items = newArr;
   cart.itemCount++;
}

void removeItem(Cart& cart, int index)
{
   index--;

   if (index < 0 || index >= cart.itemCount)
   {
       return;
   }

   Item* newArr = new Item[cart.itemCount - 1];
   int x = 0;

   for (int i = 0; i < cart.itemCount; i++)
   {
       if (i != index)
       {
           newArr[x] = cart.items[i];
           x++;
       }
   }

   delete[] cart.items;
   cart.items = newArr;
   cart.itemCount--;
}

void addAttribute(Cart& cart, int index, const char attrN[], const char attrV[])
{
   index--;

   if (index < 0 || index >= cart.itemCount)
   {
       return;
   }

   Item& it = cart.items[index];
   int old = it.attrCount;

   char** newNames = new char* [old + 1];
   char** newVals = new char* [old + 1];

   for (int i = 0; i < old; i++)
   {
       newNames[i] = it.attrName[i];
       newVals[i] = it.attrValue[i];
   }

   newNames[old] = new char[strlen(attrN) + 1];
   strcpy(newNames[old], attrN);

   newVals[old] = new char[strlen(attrV) + 1];
   strcpy(newVals[old], attrV);

   delete[] it.attrName;
   delete[] it.attrValue;

   it.attrName = newNames;
   it.attrValue = newVals;
   it.attrCount++;
}

void removeAttribute(Cart& cart, int index, const char attrN[])
{
   index--;

   if (index < 0 || index >= cart.itemCount)
   {
       return;
   }

   Item& it = cart.items[index];
   int pos = -1;

   for (int i = 0; i < it.attrCount; i++)
   {
       if (strcmp(it.attrName[i], attrN) == 0)
       {
           pos = i;
           break;
       }
   }

   if (pos == -1)
   {
       return;
   }

   char** newNames = new char* [it.attrCount - 1];
   char** newVals = new char* [it.attrCount - 1];
   int x = 0;

   for (int i = 0; i < it.attrCount; i++)
   {
       if (i != pos)
       {
           newNames[x] = it.attrName[i];
           newVals[x] = it.attrValue[i];
           x++;
       }
   }

   delete[] it.attrName[pos];
   delete[] it.attrValue[pos];
   delete[] it.attrName;
   delete[] it.attrValue;

   it.attrName = newNames;
   it.attrValue = newVals;
   it.attrCount--;
}

void sortCartByPrice(Cart& cart)
{
   for (int i = 0; i < cart.itemCount - 1; i++)
   {
       for (int j = 0; j < cart.itemCount - 1 - i; j++)
       {
           if (cart.items[j].price > cart.items[j + 1].price)
           {
               swap(cart.items[j], cart.items[j + 1]);
           }
       }
   }
}

void getItemInfo(Cart& cart, int index)
{
   index--;

   if (index < 0 || index >= cart.itemCount)
   {
       return;
   }

   Item& it = cart.items[index];

   cout << "\nName: " << it.name << "\n";
   cout << "Price: " << it.price << "\n";
   cout << "Attributes:\n";

   for (int i = 0; i < it.attrCount; i++)
   {
       cout << "  - " << it.attrName[i] << ": " << it.attrValue[i] << "\n";
   }
}

void filterByAttribute(Cart& cart, const char attrName[], const char value[])
{
   cout << "\nFiltered Items:\n";

   for (int i = 0; i < cart.itemCount; i++)
   {
       for (int j = 0; j < cart.items[i].attrCount; j++)
       {
           if (strcmp(cart.items[i].attrName[j], attrName) != 0)
           {
               continue;
           }

           if (strcmp(value, "-1") == 0 || strcmp(cart.items[i].attrValue[j], value) == 0)
           {
               cout << cart.items[i].name
                   << " (Price: " << cart.items[i].price << ")\n";
           }
       }
   }
}

int main()
{
   Cart cart;
   int ch;

   do
   {
       cout << "1. Add an item\n";
       cout << "2. Remove an item\n";
       cout << "3. Add an attribute\n";
       cout << "4. Remove an attribute\n";
       cout << "5. Show item info\n";
       cout << "6. Clear cart\n";
       cout << "7. Sort cart by price\n";
       cout << "8. Total cart value\n";
       cout << "9. Average cart value\n";
       cout << "10. Filter by attribute\n";
       cout << "Enter 0 to exit\n";
       cout << "Enter choice: ";

       cin >> ch;

       if (ch == 1)
       {
           char name[50];
           int price;

           cout << "Enter item name: ";
           cin.ignore();
           cin.getline(name, 50);

           cout << "Enter price: ";
           cin >> price;

           addItem(cart, name, price);
       }
       else if (ch == 2)
       {
           int n;
           cout << "Enter item number: ";
           cin >> n;
           removeItem(cart, n);
       }
       else if (ch == 3)
       {
           int i;
           char an[50], av[50];

           cout << "Item index: ";
           cin >> i;
           cout << "Attribute name: ";
           cin >> an;
           cout << "Attribute value: ";
           cin >> av;

           addAttribute(cart, i, an, av);
       }
       else if (ch == 4)
       {
           int i;
           char an[50];

           cout << "Item index: ";
           cin >> i;
           cout << "Attribute name to remove: ";
           cin >> an;

           removeAttribute(cart, i, an);
       }
       else if (ch == 5)
       {
           int i;
           cout << "Item index: ";
           cin >> i;
           getItemInfo(cart, i);
       }
       else if (ch == 6)
       {
           clearCart(cart);
           cout << "Cart cleared\n";
       }
       else if (ch == 7)
       {
           sortCartByPrice(cart);
           cout << "Sorted\n";
       }
       else if (ch == 8)
       {
           cout << "Total: " << totalCartValue(cart) << "\n";
       }
       else if (ch == 9)
       {
           cout << "Average: " << avgCartValue(cart) << "\n";
       }
       else if (ch == 10)
       {
           char an[50], val[50];

           cout << "Attribute name: ";
           cin >> an;
           cout << "Value (-1 for all): ";
           cin >> val;

           filterByAttribute(cart, an, val);
       }

   } while (ch != 0);

   clearCart(cart);
   return 0;
}
