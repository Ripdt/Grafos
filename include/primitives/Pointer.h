#ifndef _POINTER_H
#define _POINTER_H

template <typename T>
class Pointer
{
public:
  Pointer() = default;
  Pointer(const Pointer<T>& other);
  Pointer(T* _obj);
  Pointer(const T& src);
  ~Pointer();

  void operator=(Pointer<T>& other);
  void operator=(T* other);

  T* operator->() const;
  T* getRaw() const;
  T& operator*() const;

  bool operator==(T* other);
private:

  class ReferenceCounter
  {
  public:
    ReferenceCounter() = default;

    void add() { counter++; }

    int release() {
      counter--;
      return counter;
    }

  private:
    int counter = 1;
  };

  void Release();

  T* obj = nullptr;
  ReferenceCounter* rc = new ReferenceCounter();
};



//-----------------------------------------------------------------------------------

template<typename T>
inline Pointer<T>::Pointer(
    const Pointer<T>& other
) :
  obj(other.obj),
  rc(other.rc)
{
  rc->add();
}

//-----------------------------------------------------------------------------------

template<typename T>
Pointer<T>::Pointer(
    T* _obj
) : 
  obj(_obj) 
{
}

//-----------------------------------------------------------------------------------

template<typename T>
Pointer<T>::Pointer(
    const T& src
) : 
  obj(new T(src)) 
{
}

//-----------------------------------------------------------------------------------

template<typename T>
inline Pointer<T>::~Pointer() 
{
  Release();
}

//-----------------------------------------------------------------------------------

template <class T> 
void Pointer<T>::Release()
{
  if (rc->release() == 0) {
    delete obj;
    delete rc;
  }
}

//-----------------------------------------------------------------------------------

template<typename T>
T* Pointer<T>::operator->() const 
{
  return obj;
}

//-----------------------------------------------------------------------------------

template<typename T>
T& Pointer<T>::operator*() const 
{
  return *obj;
}

//-----------------------------------------------------------------------------------

template<typename T>
inline bool Pointer<T>::operator==(
    T* other
)
{
  return this.obj == other.obj;
}

//-----------------------------------------------------------------------------------

template<typename T>
inline void Pointer<T>::operator=(
    Pointer<T>& other
)
{
  this->obj = other.obj;
  this->rc = other.rc;

  rc->add();
}

//-----------------------------------------------------------------------------------

template <class T> 
void Pointer<T>::operator=(
  T* _object
)
{
  if (obj != _object) {
    Release();

    obj = _object;
    if (obj != nullptr) {
      obj->IncrementNRef();
    }
  }
}

//-----------------------------------------------------------------------------------

template<typename T>
T* Pointer<T>::getRaw() const 
{
  return obj;
}

//-----------------------------------------------------------------------------------

#endif