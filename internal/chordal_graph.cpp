#pragma once
#include "optional.cpp"
namespace dalt
{
    namespace graph
    {
        // return perfect elimination sequence or NIL if g isn't a chordal_graph
        Optional<Vec<int>> ChordalGraph(const Vec<TreeSet<int>> &g)
        {
            int n = Size(g);
            if (n == 0)
            {
                return Vec<int>();
            }
            Vec<int> deg(n);
            Vec<bool> visited(n, false);
            Vec<int> seq;
            Vec<int> rank(n);
            seq.reserve(n);
            Vec<Deque<int>> dq(n + 1);
            for (int i = 0; i < n; i++)
            {
                dq[0].push_back(i);
            }
            int cur = 0;
            while (true)
            {
                while (cur >= 0 && dq[cur].empty())
                {
                    cur--;
                }
                if (cur < 0)
                {
                    break;
                }
                int head = dq[cur].front();
                dq[cur].pop_front();
                if (visited[head])
                {
                    continue;
                }
                visited[head] = true;
                seq.push_back(head);
                for (int x : g[head])
                {
                    deg[x]++;
                    dq[deg[x]].push_back(x);
                }
                cur++;
            }
            Reverse(All(seq));
            Assert(Size(seq) == n);
            for(int i = 0; i < n; i++) {
                rank[seq[i]] = i;
            }
            for (var x : seq)
            {
                int y = -1;
                for (var to : g[x])
                {
                    if (rank[to] <= rank[x])
                    {
                        continue;
                    }
                    if (y == -1 || rank[y] > rank[to])
                    {
                        y = to;
                    }
                }
                for (var to : g[x])
                {
                    if (rank[to] <= rank[y])
                    {
                        continue;
                    }
                    if (g[y].find(to) == g[y].end())
                    {
                        DebugFmtln("Whiteness(%d, %d, %d)", x, y, to);
                        return {};
                    }
                }
            }
            return seq;
        }
    }
}