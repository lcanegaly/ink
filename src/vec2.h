#pragma once

// A basic 2 component vector type
template<typename T>
struct Type_Vec2 {
  Type_Vec2(T x, T y): x{x}, y{y}{}
  Type_Vec2(): x{0}, y{0}{}

  Type_Vec2 operator-(const Type_Vec2& other){
    return Type_Vec2{x - other.x, y - other.y};
  }  
  void operator=(const Type_Vec2& other) {
    x = other.x;
    y = other.y;
  }
  T x;
  T y;
};

// Floating point and Int vector types
typedef double FloatType;
typedef Type_Vec2<FloatType> Vec2;

typedef int IntType;
typedef Type_Vec2<IntType> IVec2;
