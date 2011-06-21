#ifndef _RR_V8_HANDLE_
#define _RR_V8_HANDLE_

#include <v8.h>
#include "ruby.h"

/**
* Holds a reference to a V8 heap object. This serves as the base
* class for all of the low-level proxies that reference into V8
*/
struct v8_handle  {

  struct Payload {
    Payload(v8::Handle<void> object);
    virtual ~Payload();
    void release();
    v8::Persistent<void> handle;
  };

  v8_handle(v8::Handle<void> object);
  virtual ~v8_handle();

  Payload* payload;
  bool dead;
  VALUE weakref_callback;
  VALUE weakref_callback_parameters;
};

void rr_init_handle();

v8_handle* rr_v8_handle_raw(VALUE value);

template <class T> v8::Persistent<T>& rr_v8_handle(VALUE value) {
  return (v8::Persistent<T>&)(rr_v8_handle_raw(value)->payload->handle);
}
VALUE rr_v8_handle_new(VALUE rbclass, v8::Handle<void> handle);
VALUE rr_v8_handle_class();

#endif
