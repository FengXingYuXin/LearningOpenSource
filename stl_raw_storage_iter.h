/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 * You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_RAW_STORAGE_ITERATOR_H
#define __SGI_STL_INTERNAL_RAW_STORAGE_ITERATOR_H

__STL_BEGIN_NAMESPACE
//In C++, the operator new allocates memory for an object and then creates 
//an object at that location by calling a constructor. Occasionally, however, 
//it is useful to separate those two operations. [1] If i is an iterator that 
//points to a region of uninitialized memory, then you can use construct to 
//create an object in the location pointed to by i. Raw_storage_iterator is 
//an adaptor that makes this procedure more convenient. If r is a raw_storage_iterator, 
//then it has some underlying iterator i. The expression *r = x is 
//equivalent to construct(&*i, x).

//Regular iterators operate on a certain type of objects, which have already 
//been constructed. A raw_storage_iterator wraps one of these regular iterators 
//into a special output iterator which constructs objects at the location 
//being pointed before being written.

//一个迭代器配接器
//raw_storage_iterator:用来在未初始化的内存上进行相应的操作
//example:copy(begin(),end(),raw_storage_iterator<int*,int>(_start)):
//在_start指向的原始内存上以(begin(),end())为初始值进行复制
template <class _ForwardIterator, class _Tp>
class raw_storage_iterator {
protected:
  _ForwardIterator _M_iter;
public:
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  explicit raw_storage_iterator(_ForwardIterator __x) : _M_iter(__x) {}
  raw_storage_iterator& operator*() { return *this; }
  raw_storage_iterator& operator=(const _Tp& __element) {
    construct(&*_M_iter, __element);
    return *this;
  }        
  raw_storage_iterator<_ForwardIterator, _Tp>& operator++() {
    ++_M_iter;
    return *this;
  }
  raw_storage_iterator<_ForwardIterator, _Tp> operator++(int) {
    raw_storage_iterator<_ForwardIterator, _Tp> __tmp = *this;
    ++_M_iter;
    return __tmp;
  }
};

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

template <class _ForwardIterator, class _Tp>
inline output_iterator_tag
iterator_category(const raw_storage_iterator<_ForwardIterator, _Tp>&)
{
  return output_iterator_tag();
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_RAW_STORAGE_ITERATOR_H */

// Local Variables:
// mode:C++
// End:
