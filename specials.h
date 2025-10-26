// specials.h; Hsin-ih Tu; 2025.10.24;
// Specialization and non-fundamental (string) type handling

#include <string>
#include <type_traits>

// helper to coerce to "NULL"
// question, is there some kind of std::string constant that means "invalid" or "undefined"
//           because the type isn't a pointer, we can't rely on nullptr.
template <typename T>
T safeNull() {
   if (!std::is_fundamental<T>()) {
      return T();
      // check for string type, and use C string to coerce
      // if constexpr(std::is_same_v<decltype(T), std::string>)
      // const char *nothing = nullptr;
      // return T(nothing);
      ////return NULL;
   } else {
      return T(NULL);
   }
}

// compile-time definition to allow destructor to handle the non-fundamental data type (std::string)
// items
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type resolveString(
   const T &value) {
   return value;  // T is std:string, raw value is desired
}

// compile-time definition to allow destructor to handle the non-fundamental data type (std::string)
// items
template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value, std::string>::type resolveString(
   const T &value) {
   return std::to_string(value);  // T is not std:string
}
