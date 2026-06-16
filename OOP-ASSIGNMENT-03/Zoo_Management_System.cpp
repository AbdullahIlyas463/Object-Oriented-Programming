#include<iostream>
using namespace std;

int myStrLen(const char* str)
{
   if (str == NULL) return 0;
   int i = 0;
   while (*(str + i) != '\0') i++;
   return i;
}

char* copyStr(const char* str)
{
   if (str == NULL) return NULL;
   int len = myStrLen(str);
   char* temp = new char[len + 1];
   for (int i = 0; i < len; i++) *(temp + i) = *(str + i);
   *(temp + len) = '\0';
   return temp;
}

int myStrCmp(const char* a, const char* b)
{
   if (a == NULL || b == NULL) return -1;
   int i = 0;
   while (*(a + i) != '\0' && *(b + i) != '\0')
   {
       if (*(a + i) != *(b + i)) return *(a + i) - *(b + i);
       i++;
   }
   return *(a + i) - *(b + i);
}


class Address {
   char* street; char* city; char* country;
public:
   Address(const char* s = "", const char* c = "", const char* co = "")
   {
       street = copyStr(s); city = copyStr(c); country = copyStr(co);
   }

   Address(const Address& other)
   {
       street = copyStr(other.street);
       city = copyStr(other.city);
       country = copyStr(other.country);
   }

   Address& operator=(const Address& other)
   {
       if (this != &other)
       {
           delete[] street; delete[] city; delete[] country;
           street = copyStr(other.street);
           city = copyStr(other.city);
           country = copyStr(other.country);
       }
       return *this;
   }

   ~Address()
   {
       delete[] street; delete[] city; delete[] country;
   }

   void display() const
   {
       cout << "Address: " << street << ", " << city << ", " << country << endl;
   }
};


class Ticket {
   char* id;
   char* type;

public:
   Ticket(const char* i = "", const char* t = "")
   {
       id = copyStr(i);
       type = copyStr(t);
   }


   Ticket(const Ticket& other)
   {
       id = copyStr(other.id);
       type = copyStr(other.type);
   }


   Ticket& operator=(const Ticket& other)
   {
       if (this != &other)
       {
           delete[] id;
           delete[] type;

           id = copyStr(other.id);
           type = copyStr(other.type);
       }
       return *this;
   }

   ~Ticket()
   {
       delete[] id;
       delete[] type;
   }

   void display() const
   {
       cout << "Ticket: " << id << " | Type: " << type << endl;
   }
};

class Animal {
   char* species; char* name; int age;
public:
   Animal(const char* s, const char* n, int a)
   {
       species = copyStr(s); name = copyStr(n); age = a;
   }
   ~Animal() { delete[] species; delete[] name; }

   char* getName() const { return name; }

   void display() const
   {
       cout << "Animal: " << species << " (" << name << ", Age: " << age << ")" << endl;
   }
};

class Enclosure {
   char* name;
   Animal** animals;
   int count;
public:
   Enclosure(const char* n)
   {
       name = copyStr(n); animals = NULL; count = 0;
   }

   ~Enclosure()
   {
       for (int i = 0; i < count; i++) delete* (animals + i);
       delete[] animals; delete[] name;
   }

   void addAnimal(const char* s, const char* n, int a)
   {
       Animal** temp = new Animal * [count + 1];
       for (int i = 0; i < count; i++) *(temp + i) = *(animals + i);

       *(temp + count) = new Animal(s, n, a);

       delete[] animals; animals = temp; count++;
   }

   Animal* getAnimal(const char* n)
   {
       for (int i = 0; i < count; i++)
       {
           if (myStrCmp((*(animals + i))->getName(), n) == 0)
               return *(animals + i);
       }
       return NULL;
   }

   void display() const
   {
       cout << "Enclosure: " << name << endl;
       for (int i = 0; i < count; i++) (*(animals + i))->display();
   }
};

class Zookeeper {
   char* name; char* id; Address address;
public:
   Zookeeper(const char* n, const char* i, const Address& a) : address(a)
   {
       name = copyStr(n); id = copyStr(i);
   }
   ~Zookeeper() { delete[] name; delete[] id; }

   void display() const
   {
       cout << "Zookeeper created: " << name << " [ID: " << id << "]" << endl;
       address.display();
   }
};

class Visitor {
   char* name; Ticket ticket;
   Animal** visited; int count;
public:
   Visitor(const char* n, const Ticket& t) : ticket(t)
   {
       name = copyStr(n); visited = NULL; count = 0;
       cout << "Visitor created: " << name << endl;
       ticket.display();
   }

   ~Visitor()
   {
       delete[] visited; delete[] name;
   }

   void visitAnimal(Animal* a)
   {
       if (a == NULL) { cout << "Animal not found" << endl; return; }

       for (int i = 0; i < count; i++)
       {
           if (*(visited + i) == a)
           {
               cout << "Error: already visited this animal" << endl;
               return;
           }
       }

       Animal** temp = new Animal * [count + 1];
       for (int i = 0; i < count; i++) *(temp + i) = *(visited + i);

       *(temp + count) = a;
       delete[] visited; visited = temp; count++;

       cout << name << " visits " << a->getName() << endl;
   }

   void leaveAnimal(const char* n)
   {
       int index = -1;
       for (int i = 0; i < count; i++)
       {
           if (myStrCmp((*(visited + i))->getName(), n) == 0)
               index = i;
       }

       if (index == -1)
       {
           cout << "Error: animal not found in visit list" << endl;
           return;
       }

       for (int i = index; i < count - 1; i++)
           *(visited + i) = *(visited + i + 1);

       count--;
       cout << name << " left " << n << endl;
   }
};


class Zoo {
   char* name;
   Enclosure** enclosures; int eCount;
   Visitor** visitors; int vCount;
public:
   Zoo(const char* n)
   {
       name = copyStr(n);
       enclosures = NULL; visitors = NULL;
       eCount = vCount = 0;
   }

   ~Zoo()
   {
       cout << "Destroying Zoo " << name << " ..." << endl;
       for (int i = 0; i < eCount; i++) delete* (enclosures + i);
       delete[] enclosures;
       delete[] visitors;
       delete[] name;
   }

   void addEnclosure(const char* n)
   {
       Enclosure** temp = new Enclosure * [eCount + 1];
       for (int i = 0; i < eCount; i++) *(temp + i) = *(enclosures + i);

       *(temp + eCount) = new Enclosure(n);
       delete[] enclosures; enclosures = temp; eCount++;
   }

   Enclosure* getEnclosure(int i)
   {
       if (i < 0 || i >= eCount) return NULL;
       return *(enclosures + i);
   }

   void registerVisitor(Visitor* v)
   {
       for (int i = 0; i < vCount; i++)
       {
           if (*(visitors + i) == v)
           {
               cout << "Error: duplicate visitor" << endl;
               return;
           }
       }

       Visitor** temp = new Visitor * [vCount + 1];
       for (int i = 0; i < vCount; i++) *(temp + i) = *(visitors + i);

       *(temp + vCount) = v;
       delete[] visitors; visitors = temp; vCount++;
   }

   void removeVisitor(Visitor* v)
   {
       int index = -1;
       for (int i = 0; i < vCount; i++)
       {
           if (*(visitors + i) == v) index = i;
       }

       if (index == -1)
       {
           cout << "Error: visitor not found" << endl;
           return;
       }

       for (int i = index; i < vCount - 1; i++)
           *(visitors + i) = *(visitors + i + 1);

       vCount--;
   }

   void display() const
   {
       cout << "Zoo: " << name << endl;
       for (int i = 0; i < eCount; i++) (*(enclosures + i))->display();
   }
};

int main()
{
   Address addr("12-Garden Lane", "Lahore", "Pakistan");
   Zookeeper zk("Ali Khan", "ZK-101", addr);
   zk.display();

   Zoo zoo("Lahore Safari Park");
   zoo.addEnclosure("meow meow meow meow");

   Enclosure* e = zoo.getEnclosure(0);
   if (e != NULL)
   {
       e->addAnimal("Lion", "Sheruu", 7);
   }

   Ticket t("T-202", "Adult");
   Visitor v("Abdullah Ilyas", t);

   zoo.registerVisitor(&v);

   Animal* a = e->getAnimal("Sheruu");
   v.visitAnimal(a);

   zoo.display();

   return 0;
}