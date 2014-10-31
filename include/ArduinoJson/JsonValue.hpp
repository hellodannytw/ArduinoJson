// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include <stddef.h>

#include "Internals/JsonValueContent.hpp"
#include "Internals/JsonValueType.hpp"

namespace ArduinoJson {

class JsonArray;
class JsonObject;

namespace Internals {
class JsonWriter;
}

class JsonValue {
 public:
  JsonValue() : _type(Internals::JSON_UNDEFINED) {}

  void set(bool value);
  void set(const char *value);
  void set(double value, int decimals = 2);
  void set(int value) { set(static_cast<long>(value)); }
  void set(long value);
  void set(JsonArray &array);
  void set(JsonObject &object);

  template <typename T>
  JsonValue &operator=(T value) {
    set(value);
    return *this;
  }

  JsonValue &operator=(JsonArray &array) {
    set(array);
    return *this;
  }

  JsonValue &operator=(JsonObject &object) {
    set(object);
    return *this;
  }

  operator bool() const;
  operator const char *() const;
  operator double() const;
  operator long() const;
  operator int() const { return operator long(); }
  operator JsonArray &() const;
  operator JsonObject &() const;

  JsonArray &asArray() { return static_cast<JsonArray &>(*this); };
  JsonObject &asObject() { return static_cast<JsonObject &>(*this); };

  template <typename T>
  T as() {
    return static_cast<T>(*this);
  }

  static JsonValue &invalid() { return _invalid; }

  bool success() { return _type != Internals::JSON_INVALID; }

  void writeTo(Internals::JsonWriter &writer) const;

 private:
  JsonValue(Internals::JsonValueType type) : _type(type) {}

  Internals::JsonValueType _type;
  Internals::JsonValueContent _content;
  static JsonValue _invalid;
};
}
