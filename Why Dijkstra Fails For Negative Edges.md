
# Why dijkstra Fails for negative edges :

```
https://www.youtube.com/watch?v=R3g2SSlyY_0
```

# what measures that can be taken for dijkstra to works for negative edges to.

## If we find the minimum weight edge and add this weight to all edges, so that they become non-negative; will the dijkstra works?
**Answer: NO**

Consider this graph:

```
       1              1
1 -----------> 2 ----------> 3 
\                         / 
 \  4                 1  /  
   \                  / 
     \             / 
       \>   4    </  
```

Current distance from source 1, to all other is dist[2] = 1 (1 -> 2), dist[3] = 2 (1 -> 2 -> 3), dist[4] = 3 (1 -> 2 -> 3 -> 4).

**If we increase weight of all edges by a constant value, lets say 1, will the relative distance (include edges) remained same?**

```
       2              2
1 -----------> 2 ----------> 3
\                         /
 \  5                 2  /  
   \                  /
     \             /
       \>   4    </  
```

Now distance from source 1, to all other is dist[2] = 2 (1 -> 2), dist[3] = 4 (1 -> 2 -> 3), dist[4] = 5 (1 -> 4).
**Look dist[4] has changed its relative order**


<br>
<br>

## Reweight each edges of the graph like w'(u, v) = w(u, v) + potential[u] – potential[v], using Bellman-Ford to eliminate negative weights, then apply Dijkstra's algorithm to find the shortest paths from source to all other vertex.

<br>
**It will works: The question is where we can use it?**
**Answer: Jonson's algorithm for all pair shortest path**

## Jonson's algorithm for all pair shortest path:
**Step 1: Adjust negative edges using bellman-ford.**
**Step 2: Run dijkstra for each vertex to find all pair shortest path**

```
This is better than floyed-warshall O(V^3). As it's complexity is O(V2log V + VE)
```



# By the way, it will not work if negative cycle exists. 



