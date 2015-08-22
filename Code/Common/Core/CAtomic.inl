// Filename: CAtomic.inl
// Copyright 2015 Gael Huber

ZOOFARI_BEGIN_NAMESPACE(zoofari)
ZOOFARI_BEGIN_NAMESPACE(common)
ZOOFARI_BEGIN_NAMESPACE(core)

template <typename T>
CAtomic<T>::CAtomic()
: TBase()
{
}

template <typename T>
CAtomic<T>::CAtomic(T const inValue)
: TBase(inValue)
{
}

template <typename T>
CAtomic<T> & CAtomic<T>::operator=(T const inValue)
{
    Store(inValue);
    return *this;
}

ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()
ZOOFARI_END_NAMESPACE()