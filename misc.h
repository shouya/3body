#ifndef __MISC_H__
#define __MISC_H__

template <class T>
void swap(T& a, T& b) {
    T t = b;
    b = a; a = t;
}

#endif /* __MISC_H__ */
