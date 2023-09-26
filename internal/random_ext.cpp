#include "common.cpp"
#include "hashmap.cpp"
namespace dalt {
Vec<int> RandomSubset(int N, int K, std::mt19937 rng = rng) {
  if (K * 2 >= N) {
    Vec<int> item(N);
    for (int i = 0; i < N; i++) {
      item[i] = i;
    }
    Shuffle(All(item), rng);
    item.resize(K);
    return item;
  }
  hash::HashMap<int, bool> map(K);
  while(map.get_size() < K) {
    int next = random_choice<int>(0, N - 1, rng);
    map[next] = true;
  }
  Vec<int> keys;
  keys.reserve(K);
  for(var &kv : map) {
    keys.push_back(kv.first);
  }
  return keys;
}
Vec<int> RandomPartition(int N, int K, std::mt19937 rng = rng) {
  Assert(K >= 1);
  int total = N + K - 1;
  var points = RandomSubset(total, K - 1, rng);
  Vec<int> ans;
  ans.reserve(K);
  int last = -1;
  Sort(All(points));
  for(int pt : points) {
    ans.push_back(pt - last - 1);
    last = pt;
  }
  ans.push_back(total - last);
  return ans;
}
}