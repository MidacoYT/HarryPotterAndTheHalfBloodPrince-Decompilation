struct Pair { unsigned a,b; bool eq(Pair* rhs); }; bool Pair::eq(Pair* rhs) { return a == rhs->a && b == rhs->b; }
