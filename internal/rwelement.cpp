#pragma 
#include "common.cpp"
#include "nil.cpp"
namespace dalt {
  template<class FORWARD, class T, class METADATA = Nil>
  struct RWElement {
    using Self = RWElement<FORWARD, T, METADATA>;
    FORWARD *forward;
    METADATA metadata;
    RWElement(FORWARD *_forward, const METADATA& _metadata): forward(_forward), metadata(_metadata) {
    }
    operator T() {
      return forward->read(metadata);
    }
    Self &operator=(const T& val) {
      forward->write(metadata, val);
      return *this;
    }
  };
}