#ifndef OBJECT_H
#define OBJECT_H

//快速新建 object 的属性
#define PROPERTY_CREATE_H(TYPE, M)                                      \
private:                                                                \
    TYPE _##M;                                                          \
public:                                                                 \
    void set##M(const TYPE &value)  { _##M = value; }                   \
    TYPE get##M() const { return _##M; }


#endif // OBJECT_H
