#pragma once

template <typename T>
class Nullable
{
public:
  bool hasValue;
  T value;
  Nullable()
  {
    hasValue = false;
  }
  Nullable(T value)
  {
    hasValue = true;
    value = value;
  }
};