#pragma once
#include "common.cpp"
#include "fenwick_tree.cpp"
namespace dalt {
namespace adhoc {
template <class D, class V>
Vec<V> PrefixSum3DSparse(Vec<Tuple<D, D, D, V>> pts) {
  if(Size(pts) == 0) {
    return Vec<V>();
  }

  struct Event {
    int id;
    D x;
    D y;
    int z;
    V v;
    V s;
  };

  int n = Size(pts);
  Vec<D> all_z(n);
  for (int i = 0; i < n; i++) {
    all_z[i] = std::get<2>(pts[i]);
  }
  Sort(All(all_z));
  MakeUnique(all_z);
  Vec<Event> discrete_pts(n);
  for (int i = 0; i < n; i++) {
    discrete_pts[i].x =
        std::get<0>(pts[i]);
    discrete_pts[i].y =
        std::get<1>(pts[i]);
    discrete_pts[i].z =
        LowerBound(All(all_z), std::get<2>(pts[i])) - all_z.begin();
    discrete_pts[i].v = std::get<3>(pts[i]);
  }
  Vec<Event*> events(n);
  for (int i = 0; i < n; i++) {
    events[i] = &discrete_pts[i];
  }
  Sort(All(events), [&](auto a, auto b) {
    return MakeTuple(a->x, a->y, a->z, a->id) <
           MakeTuple(b->x, b->y, b->z, b->id);
  });
  auto sort_by_y = [&](auto a, auto b) { return a->y < b->y; };
  FenwickTree<V> fwt(n);
  Vec<Event*> buffer(n);
  auto dac = [&](auto &dac, int l, int r) -> void {
    if(l == r) {
      events[l]->s = events[l]->s + events[l]->v;
      return;
    }
    int m = (l + r) / 2;
    dac(dac, l, m);
    dac(dac, m + 1, r);
    //Sort(events.begin() + l, events.begin() + m + 1, sort_by_y);
    //Sort(events.begin() + m + 1, events.begin() + r + 1, sort_by_y);
    int iter_l = l;
    int iter_r = m + 1;
    while (iter_l <= m || iter_r <= r) {
      if (iter_l <= m &&
          (iter_r > r || events[iter_l]->y <= events[iter_r]->y)) {
        fwt.update(events[iter_l]->z, events[iter_l]->v);
        iter_l++;
      } else {
        events[iter_r]->s = events[iter_r]->s + fwt.query(events[iter_r]->z);
        iter_r++;
      }
    }
    for (int i = l; i <= m; i++) {
      fwt.update(events[i]->z, -events[i]->v);
    }
    //sort by y here
    iter_l = l;
    iter_r = m + 1;
    int wpos = l;
    while (iter_l <= m || iter_r <= r) {
      if (iter_l <= m &&
          (iter_r > r || events[iter_l]->y <= events[iter_r]->y)) {
        buffer[wpos++] = events[iter_l];
        iter_l++;
      } else {
        buffer[wpos++] = events[iter_r];
        iter_r++;
      }
    }
    for(int i = l; i <= r; i++) {
      events[i] = buffer[i];
    }
  };
  dac(dac, 0, n - 1);
  Vec<V> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = discrete_pts[i].s;
  }
  return ans;
}
}  // namespace adhoc
}  // namespace dalt