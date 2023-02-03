#pragma once
#include "../segtree.cpp"
#include "../number.cpp"
namespace dalt {
namespace adhoc {
template<class T>
T AreaOfUnionRect(const Vec<T> &L, const Vec<T> &R, const Vec<T> &D, const Vec<T> &U) {
    int N = Size(L);
    Assert(N == Size(R));
    Assert(N == Size(D));
    Assert(N == Size(U));
    Vec<int> sort_by_l(N);
    Vec<int> sort_by_r(N);
    Vec<int> all;
    all.reserve(2 * N);
    for(int i = 0; i < N; i++) {
        sort_by_l[i] = i;
        sort_by_r[i] = i;
        all.push_back(U[i]);
        all.push_back(D[i]);
    }
    Sort(All(sort_by_l), [&](var a, var b) {
        return L[a] < L[b];
    });
    Sort(All(sort_by_r), [&](var a, var b) {
        return R[a] < R[b];
    });
    MakeUniqueAndSort(all);
    using namespace sbt;
    
    struct UnionOfRectID {};
    using SBTR = SelfBalanceTreeRegistry<Pair<T, int>, T, 0, UnionOfRectID>;
    using ST = SegTree<SBTR>;
    ST::Register(MakePair(T(), 0), T(), [&](var &a , var &b) {
        int min_cnt = Min(a.second, b.second);
        T sum = 0;
        if(a.second == min_cnt) {
            sum += a.first;
        }
        if(b.second == min_cnt) {
            sum += b.first;
        }
        return MakePair(sum, min_cnt);
    }, [&](var &a, var &b) {
        return MakePair(a.first, a.second + b);
    }, [&](var &a, var &b) {
        return a + b;
    });
    int M = Size(all);
    ST st(M - 1, [&](int i) {
        return MakePair(all[i + 1] - all[i], 0);
    });
    T total = all.back() - all.front();
    var covered_line = [&]() {
        var sum = st.query(0, M - 1);
        if(sum.second > 0) {
            return total;
        }
        //DebugFmtln("%lld - %lld", total, sum.first);
        return total - sum.first;
    };
    var binary_search = [&](T x) {
        return LowerBound(All(all), x) - all.begin();
    };
    var update = [&](T l, T r, int x) {
        int l_index = binary_search(l);
        int r_index = binary_search(r);
        st.update(l_index, r_index - 1, x);
    };

    var l_iter = sort_by_l.begin();
    var r_iter = sort_by_r.begin();
    T left = T();
    T ans = T();
    while(l_iter != sort_by_l.end() || r_iter != sort_by_r.end()) {
        T event = r_iter == sort_by_r.end() || l_iter != sort_by_l.end() && L[*l_iter] <= R[*r_iter] ? 
            L[*l_iter] : R[*r_iter];
        ans += (event - left) * covered_line();
        //DebugFmtln("[%lld, %lld) x %lld, processed (%d, %d)", left, event, covered_line(), l_iter - sort_by_l.begin(), r_iter - sort_by_r.begin());
        left = event;
        if(l_iter != sort_by_l.end() && L[*l_iter] == event) {
            update(D[*l_iter], U[*l_iter], 1);
            ++l_iter;
        } else {
            update(D[*r_iter], U[*r_iter], -1);
            ++r_iter;
        }
    }
    return ans;
}
}
}