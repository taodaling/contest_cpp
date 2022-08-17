#pragma once
#include "common.cpp"
#include "binary.cpp"
using namespace dalt;

void SolveOne(int test_id, IStream &in, OStream &out) {
  using Card = Pair<char, char>;
  Vec<Card> cards(14);
  for(int i = 0; i < 14; i++) {
    in >> cards[i].first >> cards[i].second;
  }
  Sort(All(cards));
  Vec<bool> can_be_triple(1 << 14);
  for(int i = 0; i < 14; i++) {
    for(int j = i + 1; j < 14; j++) {
      if (cards[i] == cards[j] || cards[i].second == cards[j].second &&
                                      cards[j].first - cards[i].first <= 2 &&
                                      1 <= cards[j].first - cards[i].first) {
        can_be_triple[(1 << i) | (1 << j)] = true;
      }
      for(int k = j + 1; k < 14; k++) {
        if(cards[i] == cards[k] || cards[i].second == cards[j].second && cards[i].second == cards[k].second 
        && cards[i].first + 1 == cards[j].first && cards[j].first + 1 == cards[k].first) {
          can_be_triple[(1 << i) | (1 << j) | (1 << k)] = true;
        }
      }
    }
  }
  MDVec<int, 3> dp(1 << 14, MDVec<int, 2>(2, Vec<int>(2, -1)));
  auto get_dp = [&](auto &dfs, int state, int can_pair, int can_replace) -> int{
    if(state == 0) {
      return 1;
    }
    var &item = dp[state][can_pair][can_replace];
    if(item == -1) {
      item = 0;
      if(can_pair) {
        for(int i = 0; i < 14; i++) {
          if(!KthBit(state, i)) {
            continue;
          }
          for(int j = i + 1; j < 14; j++) {
            if(!KthBit(state, j)) {
              continue;
            }
            int next_can_replace = can_replace;
            if(cards[i] != cards[j]) {
              next_can_replace--;
            }
            if(next_can_replace < 0) {
              continue;
            }
            if (dfs(dfs, state ^ (1 << i) ^ (1 << j), false, next_can_replace)) {
              item = 1;
            }
          }
        }
      }
      for(int i = 0; i < 14; i++) {
        if(!KthBit(state, i)) {
          continue;
        }
        for(int j = i + 1; j < 14; j++) {
          if (!KthBit(state, j)) {
            continue;
          }
          if(!can_be_triple[(1 << i) | (1 << j)]) {
            continue;
          }
          for(int k = 0; k < 14; k++) {
            if (k == i || k == j || !KthBit(state, k)) {
              continue;
            }
            int next_can_replace = can_replace;
            if(!can_be_triple[(1 << i) | (1 << j) | (1 << k)]) {
              next_can_replace--;
            }
            if(next_can_replace < 0) {
              continue;
            }
            if(dfs(dfs, state ^ (1 << i) ^ (1 << j) ^ (1 << k), can_pair, next_can_replace)) {
              item = true;
            }
          }
        }
      }
      DebugRun({
        Vec<Str> data;
        for(int i = 0; i < 14; i++) {
          if(KthBit(state, i)) {
            data.push_back(Str() + cards[i].first + cards[i].second);
          }
        }
        if(Size(data) < 5)
        Stderr << data << "-" << can_pair << "-" << can_replace << "=" << item << std::endl;
      });
    }
    return item;
  };
  if(get_dp(get_dp, (1 << 14) - 1, 1, 0)) {
    out << "Tsumo";
  } else if(get_dp(get_dp, (1 << 14) - 1, 1, 1)) {
    out << "Tenpai";
  } else {
    out << "Noten";
  }

}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}