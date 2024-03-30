#ifndef ETK_RING_HDR
#define ETK_RING_HDR

#include <etk/types.hpp>
#include <string.h>
#include <array>

namespace etk {

/** @addtogroup CORE
 * @{
 */

/** @brief  Self-contained, fixed size ring-buffer
 *
 * This is used for fixed size queues of POD-data. By assuming
 * there are no constructor or destructor we can simplify the
 * handling of mixed-type data-blocks.
 *
 */
template <uint32_t SZ, uint32_t PSZ=32>
struct RingBuff {
  using size_type = uint32_t;   ///< Ring-index.
  using payload_t = uint8_t[PSZ];

  static inline constexpr size_type size() noexcept { return SZ; }

  /** @brief Peek at head in queue
   *
   * @return Pointer to head-value or nullptr
   */
  template <typename T>
  inline const T* head() const noexcept {
    static_assert(std::is_standard_layout_v<T> == true);
    if( !empty() ) {
      return (const T*)&_data[_read];
    } else {
      return (const T*)nullptr;
    }
  }

  /** @brief Push POD 
   *
   * This method will push a pod-element into the ring.
   *
   * @param pod  Any POD-data that fit's.
   * @return If the ring is full, returns false!
   */
  template <typename T>
  inline bool push( const T&pod ) noexcept {
    static_assert( sizeof(T)<=PSZ, "POD won't fit!" );
    static_assert(std::is_standard_layout_v<T> == true);
    if( !full() ) {
      ::memcpy( &_data[_write], &pod, sizeof(pod) );
      wskip();
      return true;
    } else {
      return false;
    }
  }

  /** @brief Pop oldest entry 
   *
   * Copy the oldest element, and drop
   *
   * @param out_elem  A reference to element to update
   * @return True if there was something to pop, else false.
   */
  template <typename T>
  inline bool pop( T &out_elem ) noexcept {
    if( !empty() ) {
      ::memcpy( &out_elem, &_data[_read], sizeof(out_elem) );
      rskip();
      return true;
    }
    return false;
  }

  /** @brief Drop oldest entry 
   *
   * This will simply drop the oldest POD.
   *
   * @return True if there was something to drop, else false.
   */
  inline bool pop() noexcept {
    if( !empty() ) {
      rskip();
      return true;
    }
    return false;
  }

  /** @brief Get number of elements in ring */
  inline size_type count() const noexcept {
    return (_read<=_write?_write:_write+(size()+1)) - _read;
  }

  /** @brief Return 'true' if ring-list is empty! */
  inline bool empty() const noexcept { return _read == _write; }

  /** @brief Return 'true' if ring-list is full! */
  inline bool full() const noexcept { return (_write+1)%(size()+1) == _read; }

  /** @brief Reset to empty ring-buffer */
  void reset() noexcept { _read = _write = 0; }

protected:
  /** @brief Forward the read-index */
  inline void rskip() noexcept { _read = (1+_read) % (size()+1); }

  /** @brief Forward the write-index */
  inline void wskip() noexcept { _write=(1+_write)%(size()+1); }

private:
  mutable size_type _write=0;
  mutable size_type _read=0;

  std::array<payload_t,SZ+1> _data;
};



/**
 * @}
 */

} // namespace etk


#endif  // ETK_RING_HDR
