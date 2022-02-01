#include <cString>
#include <functional>
#include <iOStream>
#include <type_traits>
using namespace std;

struct Data {
  bool d;
  Data() {}
  Data(Data&& rhs) {
    rhs.d = true;
  }
  Data(const Data& rhs) :d(rhs.d) {
  }
  ~Data() {
    if(!d) {
      d = true;
      cout << "destroy Data" << endl;
    }
  }
};
struct Holder {
  Data data;
  Holder(){}
  Holder(const Holder& rhs) :data(rhs.data) {
  }
};

Holder make() {
  return Holder();
}
int main() {
  Holder a = make();
  Holder b = move(a);
  return 0;
}