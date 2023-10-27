#include <cstddef>

template <typename T>
struct Random
{
    T hold;
    Random() : hold(1) {}
    Random(T seed) : hold(seed){};
    void setseed(T seed) { hold = seed; }
    T operator()() { return hold = hold * 214013 + 2531011; }
};

template <typename T>
struct Hash
{
    size_t operator()(const T &x) const { return 0; /*std::hash(x);*/ };
};
#include <string>
template <>
struct Hash<std::string>
{
    size_t operator()(const std::string &s) const
    {
        size_t h = 0;
        // for (auto &&c : s)
        //     h = h * 131 + c;
        for (const char *p = s.c_str(); *p; p++)
            h = h * 131 + *p;
        return h;
    }
};
template <typename T>
struct Equal
{
    bool operator()(const T &lhs, const T &rhs) const { return lhs == rhs; }
};

#include <ctime>
#include <list>
template <typename Key, typename Val, int SIZE = int(1e6), typename Hash = ::Hash<Key>, typename Equal = ::Equal<Key>>
class FixedHashMap
{
    struct value_type
    {
        const Key key;
        Val val;
    };

    size_t a, b;
    size_t sz = 0;
    std::list<value_type> bucket[SIZE];

    size_t universal_hash(const Key &key) const
    {
        static constexpr int p = 998244353;
        static Hash hash;
        auto h = hash(key);            // original hash value
        return (a * h + b) % p % SIZE; // transform
    }
    Equal equal;

public:
    FixedHashMap()
    {
        Random<size_t> rand(time(nullptr));
        a = rand(), b = rand();
    }
    FixedHashMap(size_t _a, size_t _b) : a(_a), b(_b) {}

    size_t size() const { return sz; }
    auto insert(const value_type &x)
    {
        size_t h = universal_hash(x.key);
        bucket[h].push_front(x);
        sz++;
        return bucket[h].begin();
    }
    // auto insert(const value_type &x)
    // {
    //     (*this)[x.key] = x.val;
    // }
    auto find(const Key &key) const
    {
        size_t h = universal_hash(key);
        auto it = bucket[h].begin();
        while (it != bucket[h].end() && !equal(it->key, key))
            ++it;
        if (it == bucket[h].end())
            throw;
        return it;
    }
    Val &operator[](const Key &key)
    {
        size_t h = universal_hash(key);
        // printf("* hash = %zu\n", h);
        auto it = bucket[h].begin();
        while (it != bucket[h].end() && !equal(it->key, key))
            ++it;
        if (it != bucket[h].end())
            return it->val;
        bucket[h].push_front(value_type{key, Val()});
        sz++;
        return bucket[h].begin()->val;
    }
};

FixedHashMap<std::string, int, int(10000 / 0.7)> hm;
#include <iostream>
int main()
{
    // hm.insert({"hello", 100});
    // printf("%d %d\n", hm["hello"], hm["world"]);

    using namespace std;
    int n;
    cin >> n;
    for (string s; n--;)
        cin >> s, hm[s]++;
    printf("%d", hm.size());
    // for (auto [s, i] : hm.bucket[bucket_number])
    // {
    //     cout << "#\t" << s << ' ' << i << '\n';
    // }
}

// You can compare with the following code.
#if 0
#include <unordered_map>
#include <iostream>
#include <string>
int main(){
    using namespace std;
    unordered_map<string,int> m;
    int n;
    cin >> n;
    for (string s; n--;)
        cin >> s, m[s]++;
    printf("%d", m.size());
}

#endif