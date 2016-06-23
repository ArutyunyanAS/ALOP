#include <iostream>
#include <string>
using namespace std;
namespace lab2{
    class Printer;
}
class item{
    private:
       string name;
       int _count;
       float price;
    public:
    static int objCount;
        item() {
            name = "";
            _count = 0;
            price = 0;
        }
        item (string _name, int __count, float _price){
            name = _name;
            _count = __count;
            price = _price;
            objCount += 1;
        }
        item (item& src){
            name = src.name;
            _count = src._count;
            price = src.price;
        }
        item (item&& src){
            name = src.name;
            _count = src._count;
            price = src.price;
       }
       ~item(){
       }

       item& operator = (item&& src){
           name = src.name;
           _count  = src._count;
           price = src.price;
           cout << "moved" << endl;
           return *this;
       }
       item& operator = (const item& src){
           name = src.name;
           _count  = src._count;
           price = src.price;
           cout << "ordinary" << endl;
           return *this;
       }
       float totalPrice(int profit){
           return price * ((float) profit / 100 + 1) * _count;
       }
       void printParams(void){
           cout << "--Item--" << endl;
           cout << "Name: " << name << endl
           << "Count:" << _count << endl
           << "Price:" << price << endl;
       }
       friend lab2::Printer;
       friend class Printer;
       friend void printSmth(int);
 };
 namespace lab2{
 class Printer{
     public:
        void print(const item& src){
           cout << "Item (from friendly Printer c:" << endl;
           cout << "Name: " << src.name << endl
           << "Count:" << src._count << endl
           << "Price:" << src.price << endl;
        }
 };
 }
 void printSmth(int a){
     cout << a;
 }
 int item::objCount = 0;
 int main()
 {
     int itemsNumber;
     item *itemsArray;
     float sumTotalPrice = 0;
     int profit = 0;
     string name;
     int _count;
     float price;
     item a, b;
     a = b;
     a = std::move(b);
     cout << "Number of items: ";
     cin >> itemsNumber;
     itemsArray = new item[itemsNumber];
     for (int i = 0; i < itemsNumber; i++){
         cout << "Name: ";
         cin >> name;
         cout << "Count:";
         cin >> _count;
         cout << "Price:";
         cin >> price ;
         cout << "------------" << endl;
         itemsArray[i] = item (name, _count, price);
     }
     cout << "Profit: ";
     cin >> profit;
     cout << endl;
     for (int i = 0; i < itemsNumber; i++){
         itemsArray[i].printParams();
     }
     for (int i = 0; i < itemsNumber; i++){
         sumTotalPrice += itemsArray[i].totalPrice(profit);
     }
     cout << "--Summary total price: " << sumTotalPrice << endl;
     cout << "--objCount = " << item::objCount << endl;
     delete []itemsArray;
     return 0;
 }
