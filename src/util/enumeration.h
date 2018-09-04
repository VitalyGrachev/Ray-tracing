#ifndef RAY_TRACING_ENUMERATION_H
#define RAY_TRACING_ENUMERATION_H

template <class Iterator>
struct Enumeration {
    using iterator_type = Iterator;

    Iterator first;
    Iterator last;
};

#endif //RAY_TRACING_ENUMERATION_H
