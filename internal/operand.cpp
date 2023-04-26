#pragma once
#include "common.cpp"
namespace dalt
{
    template <class T, i64 ID = 0>
    struct Operand
    {
        using Self = Operand<T, ID>;
        T value;
        static Adder<T> add_op;
        static Adder<T> sub_op;
        static Adder<T> mul_op;
        static Adder<T> div_op;
        static Comparator<T> comp_op;
        static T default_val;
        explicit operator T()
        {
            return value;
        }
        Operand(T _v) : value(_v) {}
        Operand() : value(default_val) {}
        Self operator+(const_ref(Self) x)
        {
            return Self(add_op(value, x.value));
        }
        Self operator-(const_ref(Self) x)
        {
            return Self(sub_op(value, x.value));
        }
        Self operator*(const_ref(Self) x)
        {
            return Self(mul_op(value, x.value));
        }
        Self operator/(const_ref(Self) x)
        {
            return Self(div_op(value, x.value));
        }
        bool operator==(const_ref(Self) x)
        {
            return value == x.value;
        }
        bool operator!=(const_ref(Self) x)
        {
            return !(*this == x);
        }
        ImplArithmeticAssignOperation(Self);
        bool operator<(const_ref(Self) x)
        {
            return comp_op(value, x.value);
        }
        ImplDefaultComparision(Self);
        friend OStream &operator<<(OStream &os, const_ref(Self) x)
        {
            return os << x.value;
        }
        friend IStream &operator>>(IStream &os, Self &x)
        {
            return os >> x.value;
        }
    };
    template <class T, i64 ID>
    T Operand<T, ID>::default_val = T();
    template <class T, i64 ID>
    Adder<T> Operand<T, ID>::add_op;
    template <class T, i64 ID>
    Adder<T> Operand<T, ID>::sub_op;
    template <class T, i64 ID>
    Adder<T> Operand<T, ID>::mul_op;
    template <class T, i64 ID>
    Adder<T> Operand<T, ID>::div_op;
}