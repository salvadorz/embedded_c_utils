/**
 * @file queue.cpp
 * @author Salvador Z
 * @version 1.0
 * @brief File for define a Queue structure (FIFO)
 *
 */

/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of UTILS_C                                                *
 *                                                                             *
 *   Permission is hereby granted, free of charge, to any person obtaining a   *
 *   copy of this software and associated documentation files (the Software)   *
 *   to deal in the Software without restriction including without limitation  *
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
 *   and/or sell copies ot the Software, and to permit persons to whom the     *
 *   Software is furnished to do so, subject to the following conditions:      *
 *                                                                             *
 *   The above copyright notice and this permission notice shall be included   *
 *   in all copies or substantial portions of the Software.                    *
 *                                                                             *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   *
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARANTIES OF MERCHANTABILITY *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR      *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,     *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE        *
 *   OR OTHER DEALINGS IN THE SOFTWARE.                                        *
 ******************************************************************************/

#include <cstdint>

namespace c_utils {

template <class T> class Queue {
private:
  T             *_buff;
  bool           _full = false;
  uint16_t       _head = 0;
  uint16_t       _tail = 0;
  uint16_t const max;

public:
  explicit Queue(uint16_t size) : _buff(new T[size]), max(size) {}
  ~Queue() {
    delete[] _buff;
  }

  bool empty() const {
    return ((_tail == _head) && !_full);
  }
  // return the size of the current elements
  uint16_t size() const {
    uint16_t size = 0;
    if (!empty()) {
      size = (0 > _head - _tail) ? max + (_head - _tail) : _head - _tail;
    }
    return size;
  }

  // Inserts a new(est) element after its current last element, increases the container size by one.
  void push(T val) {
    _buff[_head] = val;
    _head       = (++_head) == max ? 0 : _head;
    if (_full) _tail = (++_tail) == max ? 0 : _tail;
    if (_tail == _head) _full = true;
  }

  // removes next (oldest) element, reduces the container size by one.
  bool pop() {
    bool is_ok = false;
    if (!empty()) {
      _tail = (++_tail) == max ? 0 : _tail;
      is_ok = true;
    }
    return is_ok;
  }

  // Inserts a new(est) element after its current last element, increases the container size by one.
  bool enqueue(T val) {
    bool is_ok = false;
    if (!_full) {
      _buff[_head] = val;
      _head       = (++_head) == max ? 0 : _head;

      if (_tail == _head) _full = true;
      is_ok = true;
    }
    return is_ok;
  }

  // Provides as a reference on the in/out element arg the next (oldest) element in the queue,
  // reduces the container by one
  bool dequeue(T &element) {
    bool is_ok = false;
    if (!empty()) {
      element = _buff[_tail];
      _tail   = (++_tail) == max ? 0 : _tail;
      _full   = false;
      is_ok   = true;
    }
    return is_ok;
  }
  // Returns a reference to the next (oldest) element in the queue.
  T front() {
    if (empty()) return T();

    T element = _buff[_tail];
    _tail     = (++_tail) == max ? 0 : _tail;
    _full     = false;

    return element;
  }
};
} // namespace