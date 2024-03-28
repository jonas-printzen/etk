#ifndef ETK_TYPES_HDR
#define ETK_TYPES_HDR

#include <stdint.h>
#include <span>
#include <string_view>

namespace etk {

using chars_t = std::string_view;

using hash32_t = uint32_t;
using hash64_t = uint64_t;

/** @brief Generic hashing function */
template <typename H>
inline constexpr H XHASH( chars_t txt ) {
  const H prime = sizeof(H) == 8 ? 0x00000100000001b3 : 0x01000193;
  H hash = sizeof(H) == 8 ? 0xcbf29ce484222325 : 0x811c9dc5;

  for( const char&c : txt ) {
    hash ^= static_cast<H>(c);
    hash *= prime;
  }

  return hash;
}

/** 32-bit string hasher
 *
 *  This inline function can be used at both compile-time to create
 *  ***switch*** - able constants and in runtime to generate hashes.
 */
inline constexpr hash32_t H32( auto &&...args ) {
  return XHASH<hash32_t>(std::forward<decltype(args)>(args)...);
}

/** 64-bit string hasher
 *
 *  This inline function can be used at both compile-time to create
 *  ***switch*** - able constants and in runtime to generate hashes.
 */
inline constexpr hash64_t H64( auto &&...args ) {
  return XHASH<hash64_t>(std::forward<decltype(args)>(args)...);
}



using data_t = std::span<uint8_t, std::dynamic_extent>;
using len_t = uint32_t;

class Pod {
public:
  using hash_t = hash32_t;  ///< For algorithms to know

  Pod( hash_t hash, len_t len ) : type(hash), len(len) {}

  /** @brief Get byte-span of encapsulated value */
  inline data_t payload() {
    return {(uint8_t*)(this+1),len};
  }

  /** @brief Get byte-span of entire pod */
  inline data_t all() {
    return {(uint8_t*)this,sizeof(type)+sizeof(len)+len};
  }

  const hash_t type;
  const len_t  len;
};


/** @brief PlainOldData - wrapper
 *
 * We wrap pod-data in a box type-tagged with a hash-value that
 * is determined at compile-time.
 */
template <hash32_t H, typename T=void>
class APod : public Pod {
public:
  using hash_t = hash32_t;  ///< For algorithms to know
  using value_type = T;

  const static constexpr hash_t TYPE=H;                ///< Type-hash
  const static constexpr len_t SIZE=sizeof(APod);      ///< Full size
  const static constexpr len_t LEN=sizeof(value_type); ///< Payload size

  /** @brief Create and initialize pod */
  APod( auto&&... ini ) : Pod(TYPE,LEN), _val(std::forward<decltype(ini)>(ini)...) {}

  /** @brief Access encapsulated value, read/write */
  inline value_type& operator * () { return _val; }
  /** @brief Access encapsulated value, read-only */
  inline const value_type& operator * () const { return _val; }

  /** @brief Access encapsulated struct, read/write */
  inline value_type* operator -> () { return &_val; }
  /** @brief Access encapsulated struct, read-only */
  inline const value_type* operator -> () const { return &_val; }

private:
  mutable value_type _val;
};


/** @brief Empty pod, type-hash only */
template <hash32_t H>
class APod<H,void> : public Pod {
public:
  using hash_t = hash32_t;  ///< For algorithms to know

  APod() : Pod(TYPE,0) {}

  const static constexpr hash_t TYPE=H;
};


} // namespace etk


#endif  // ETK_TYPES_HDR
