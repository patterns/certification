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


// compile-time definition so item (std::string) can be freed
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, int>::type deinitItem(
   T &&value) {
   std::string empty;
   value.clear();
   value.resize(0);
   value.swap(empty);

   return 0;  // T is std::string
}

// compile-time definition so item (NOT std::string) can be ignored
template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value, int>::type deinitItem(
   T &&value) {
   return 0;  // T is NOT std::string
}


// compile-time definition so destructor handles the non-fundamental data type
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type resolveString(
   const T &value) {
   return value;  // T is std:string, raw value is desired
}

// compile-time definition so destructor handles the fundamental data types
template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value, std::string>::type resolveString(
   const T &value) {
   return std::to_string(value);  // T is not std:string
}
