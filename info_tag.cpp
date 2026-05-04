// https://github.com/NotLinux18/cp-library/blob/main/info_tag.cpp
struct AddTag{
    long long x = 0;
    AddTag(long long _x = 0):x(_x){}
    void apply(const AddTag& o){x += o.x;}
};

struct SetTag{
    bool has = 0;
    long long x = 0;
    SetTag(){}
    SetTag(long long _x):has(1),x(_x){}
    void apply(const SetTag& o){if(o.has)has = 1, x = o.x;}
};

struct AddSetTag{
    bool has = 0;
    long long set = 0, add = 0;
    AddSetTag(){}
    static AddSetTag Add(long long x){AddSetTag t; t.add = x; return t;}
    static AddSetTag Set(long long x){AddSetTag t; t.has = 1; t.set = x; return t;}
    void apply(const AddSetTag& o){
        if(o.has)has = 1, set = o.set, add = o.add;
        else add += o.add;
    }
};

struct SumInfo{
    long long x, len;
    SumInfo():x(0),len(0){}
    SumInfo(long long _x):x(_x),len(1){}
    SumInfo(long long _x, long long _len):x(_x),len(_len){}
    void apply(const AddTag& t){x += t.x * len;}
    void apply(const SetTag& t){if(t.has)x = t.x * len;}
    void apply(const AddSetTag& t){if(t.has)x = t.set * len; x += t.add * len;}
};
SumInfo merge(const SumInfo& a, const SumInfo& b){
    return SumInfo(a.x + b.x, a.len + b.len);
}

struct MaxInfo{
    long long x = -INF;
    MaxInfo(long long _x = -INF):x(_x){}
    void apply(const AddTag& t){x += t.x;}
    void apply(const SetTag& t){if(t.has)x = t.x;}
    void apply(const AddSetTag& t){if(t.has)x = t.set; x += t.add;}
};
MaxInfo merge(const MaxInfo& a, const MaxInfo& b){
    return MaxInfo(max(a.x, b.x));
}
struct MinInfo{
    long long x = INF;
    MinInfo(long long _x = INF):x(_x){}
    void apply(const AddTag& t){x += t.x;}
    void apply(const SetTag& t){if(t.has)x = t.x;}
    void apply(const AddSetTag& t){if(t.has)x = t.set; x += t.add;}
};
MinInfo merge(const MinInfo& a, const MinInfo& b){
    return MinInfo(min(a.x, b.x));
};
/*
Use with segtrees:

SumInfo -> query .x gives sum
MaxInfo -> query .x gives max
MinInfo -> query .x gives min

AddTag(x)          -> range add x
SetTag(x)          -> range set x
AddSetTag::Add(x)  -> range add x
AddSetTag::Set(x)  -> range set x

Lazy_Segt<SumInfo, AddTag> st;       // range add, range sum
Lazy_Segt<MaxInfo, SetTag> st;       // range set, range max
Lazy_Segt<MinInfo, AddSetTag> st;    // range add/set, range min
*/