#pragma once
#define const_ref(T) const T &
#define mut_ref(T) T &
#define let auto
#define Size(T) int((T).size())
#define All(data) data.begin(), data.end()
#define MakeUnique(data) data.resize(std::unique(All(data)) - data.begin())
#define MakeAttribute(struct_name, Type, attr_name)                            \
  struct struct_name {                                                         \
    Type attr_name;                                                            \
    mut_ref(Type) get_##attr_name() { return attr_name; }                      \
    const_ref(Type) get_##attr_name() const { return attr_name; }              \
  };
#define MakeTemplateAttribute(struct_name, attr_name)                          \
  template <class T> struct struct_name {                                      \
    T attr_name;                                                               \
    mut_ref(T) get_##attr_name() { return attr_name; }                         \
    const_ref(T) get_##attr_name() const { return attr_name; }                 \
  };

#define DefaultEqAndNeqImpl(name)                                              \
  bool operator==(const name &a, const name &b) {                              \
    return std::memcmp(&a, &b, sizeof(name)) == 0;                             \
  }                                                                            \
  bool operator!=(const name &a, const name &b) { return !(a == b); }
#define IsType(Type, param, ret_type)                                          \
  template <typename OnlyWhenArg = param>                                      \
  typename enable_if_t<                                                        \
      is_same_v<OnlyWhenArg, param> && is_same_v<OnlyWhenArg, Type>, ret_type>
#define MakeAnnotation(name)                                                   \
  template <class T> struct is_##name { static const bool value = false; };    \
  template <class T> inline constexpr bool is_##name##_v = is_##name<T>::value;
#define AssignAnnotation(cls, annotation)                                      \
  template <> struct is_##annotation<cls> { static const bool value = true; };
