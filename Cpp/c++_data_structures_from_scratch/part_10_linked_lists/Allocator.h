#ifndef PART_10_LINKED_LISTS_ALLOCATOR_H
#define PART_10_LINKED_LISTS_ALLOCATOR_H

#include <limits>
#include <new>

namespace dss {
    template<class T>
    class Allocator {
    public:
        typedef const T *const_pointer;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef T &reference;
        typedef int difference_type;
        typedef unsigned int size_type;
        typedef T value_type;

        size_type max_size() const;

        const_pointer address(const_reference object) const;

        pointer address(reference object) const;

        pointer allocate(size_type totalObjects) const;

        void deallocate(pointer p) const;

        void construct(pointer p, const_reference sourceObject) const;

        void destroy(pointer p) const;
    };

    template<class T>
    inline typename Allocator<T>::size_type Allocator<T>::max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    template<class T>
    inline typename Allocator<T>::const_pointer Allocator<T>::address(
            const_reference object) const {
        return &object;
    }

    template<class T>
    inline typename Allocator<T>::pointer Allocator<T>::address(
            reference object) const {
        return &object;
    }

    template<class T>
    inline typename Allocator<T>::pointer Allocator<T>::allocate(
            size_type totalObjects) const {
        return static_cast<T *>(operator new(sizeof(T) * totalObjects));
    }

    template<class T>
    inline void Allocator<T>::deallocate(pointer p) const {
        operator delete(p);
    }

    template<class T>
    inline void Allocator<T>::construct(pointer p,
                                        const_reference sourceObject) const {
        new(p) T(sourceObject);
    }

    template<class T>
    inline void Allocator<T>::destroy(pointer p) const {
        p->~T();
    }
};

#endif //PART_10_LINKED_LISTS_ALLOCATOR_H
