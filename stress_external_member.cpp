#include "solver.cpp"
namespace stress {
void StressSolve(IStream &in, OStream &out) {
  int t;
  in >> t;
  int N, Q;
  in >> N >> Q;
  Vec<int> P(N);
  Vec<int> A(N);
  in >> P >> A;
  int K = 0;
  Vec<int> total;
  for(int x : A) {
    if(x == 0) {
      K++;
    } else {
      total.push_back(x);
    }
  }
  Vec<int> val(K);
  in >> val;
  total.insert(total.end(), All(val));
  MakeUniqueAndSort(total);
  if(Size(total) != N) {
    out << "NO";
    return;
  }
  Sort(All(val));
  do {
    Vec<int> seq;
    var iter = val.begin();
    for(int x : A) {
      if(x == 0) {
        seq.push_back(*iter);
        ++iter;
      } else { 
        seq.push_back(x);
      }
    }
    bool ok = true;
    for(int i = 0; i < N && ok; i++) {
      for(int j = i; j < N && ok; j++) {
        int mp = MaxElement(P.begin() + i, P.begin() + j + 1) - P.begin();
        int ma = MaxElement(seq.begin() + i, seq.begin() + j + 1) - seq.begin();
        if(mp != ma) {
          ok = false;
        }
      }
    }
    if(ok) {
      Debug(seq);
      out << "YES";
      return;
    }
  }while(std::next_permutation(All(val)));
  out << "NO";
}

void StressGenerate(int test_id, std::mt19937 &mt, OStream &out) {
  out << "1\n";
  int N = random_choice(2, 10, mt);
  out << N << ' ' << 1 << '\n';
  Vec<int> P(N);
  for(int i = 0; i < N; i++) {
    P[i] = i + 1;
  }
  Shuffle(All(P), mt);
  for(var x : P) {
    out << x << ' ';
  }
  out << '\n';
  Vec<int> A(N);
  for(int i = 0; i < N; i++) {
    A[i] = random_choice<int>(1, 100, mt);
  }
  int zero = random_choice(2, N, mt);
  Shuffle(All(P), mt);
  for(int i = 0; i < zero; i++) {
    A[P[i] - 1] = 0;
  }
  for(var x : A) {
    out << x << ' ';
  }
  out << '\n';
  for(int i = 0; i < zero - 1; i++) {
    out << random_choice(1, 100, mt) << ' ';
  }
  out << '\n';
  out << random_choice(1, 100, mt);
}

String StressMatch(IStream &input, IStream &ai, IStream &bi) {
  String x, y;
  bool succ_x, succ_y;
  while (true) {
    succ_x = !(ai >> x).fail();
    succ_y = !(bi >> y).fail();
    if (!succ_x || !succ_y) {
      if (succ_x == succ_y) {
        return "";
      } else {
        return "different output format";
      }
    }
    if (x != y) {
      return "mismatch: " + x + " | " + y;
    }
  }
}
}