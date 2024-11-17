#pragma once
#include "common.cpp"
using namespace dalt;
#include "math.cpp"
using A2 = Array<int, 2>;
struct Rect {
  A2 lr;
  A2 bt;
  int level;
  int id;
};


void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  using Pt = Array<int, 3>;
  Vec<Pt> end0(N), end1(N);
  int maxVal = 0;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < 3; j++) {
      in >> end0[i][j];
      Chmax(maxVal, end0[i][j]);
    }
    for(int j = 0; j < 3; j++) {
      in >> end1[i][j];
      Chmax(maxVal, end1[i][j]);
    }
  }

  Vec<int> ans(N);
  int B = 1000;



  for(int i = 0; i < 3; i++) {
    Vec<Rect> rects(2 * N);
    rects.clear();
    for(int j = 0; j < N; j++) {
      Vec<int> plane(4);
      plane.clear();
      for(int k = 0; k < 3; k++) {
        if(i == k) {
          continue;
        }
        plane.push_back(end0[j][k]);
        plane.push_back(end1[j][k]);
      }  
      rects.push_back(Rect {
        .lr = {plane[0], plane[1]},
        .bt = {plane[2], plane[3]},
        .level = end0[j][i],
        .id = j
      });
      rects.push_back(rects.back());
      rects.back().level = end1[j][i];
    }
    Sort(All(rects), [&](var &a, var &b) {
      return a.level < b.level;
    });

    Vec<int> no_intersect(2 * N);
    for(int i = 0; i < 2 * N; i++) {
      int l = i;
      int r = i;
      while(r + 1 < 2 * N && rects[l].level == rects[r + 1].level) {
        r++;
        continue;
      }
      i = r;
      int m = r - l + 1;
      if(m <= B) {
        for(int j = l; j <= r; j++) {
          for(int k = j + 1; k <= r; k++) {
            if(rects[j].lr[1] <= rects[k].lr[0] || rects[k].lr[1] <= rects[j].lr[0]
            || rects[j].bt[1] <= rects[k].bt[0] || rects[k].bt[1] <= rects[j].bt[0]) {
              no_intersect[j]++;
              no_intersect[k]++;
            }
          }
        }
      } else {
        Vec<Vec<int>> lr(2, Vec<int>(maxVal + 1));
        Vec<Vec<int>> bt(2, Vec<int>(maxVal + 1));
        var corners = MDVecDef<int, 4>::Make(2, 2, maxVal + 1, maxVal + 1);
        for(int j = l; j <= r; j++) {
          lr[0][rects[j].lr[0]]++;
          lr[1][rects[j].lr[1]]++;
          bt[0][rects[j].bt[0]]++;
          bt[1][rects[j].bt[1]]++;
        }
        for(int j = 0; j <= )
      } 
    }
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