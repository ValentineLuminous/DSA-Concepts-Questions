/*
 Understanding Binary Lifting for Finding the K-th Ancestor of a Node

Suppose we want to find the **k-th ancestor** of a node in a tree.

### Brute Force Approach

One straightforward idea is to store the **immediate parent** of every node. Then, to find the k-th ancestor of a node, we repeatedly move to its parent `k` times.

For example:

```text
node → parent → grandparent → ...
```

After moving up `k` times, the node we reach is the answer.

Although this approach works, it becomes inefficient when:

* `k` is very large, or
* We have to answer a large number of queries (for example, `10^5` queries).

In the worst case, each query takes **O(k)** time, which is not feasible for large constraints.

---

## A Better Approach: Binary Lifting

Instead of moving **one step at a time**, we can make larger jumps.

Let's say we want to find the **7-th ancestor** of a node.

The binary representation of `7` is:

7 = 111₂ = 2⁰ + 2¹ + 2²




This means that instead of taking 7 individual steps, we can jump:

* `2⁰` steps upward,
* then `2¹` steps upward,
* then `2²` steps upward.

So, we reach the 7-th ancestor in only **3 jumps**.

In general, any number `k` can be represented as a sum of powers of 2, and we can use those powers to efficiently move upward in the tree.

---

## What Do We Need to Store?

For every node, we precompute and store:

```text
2⁰-th ancestor  (immediate parent)
2¹-th ancestor
2²-th ancestor
2³-th ancestor
...
```

In other words,

```text
binLift[node][i] = 2ⁱ-th ancestor of node
```

Once this table is built, answering a query becomes very fast.

---

## Building the Binary Lifting Table

We already know the immediate parent of every node.

Therefore,

```text
binLift[node][0] = immediate parent of node
```

For the root node, this value is `-1`.

Now, observe the following pattern:

```text
2¹ = 2 × 2⁰
2² = 2 × 2¹
2³ = 2 × 2²
...
2ᵏ = 2 × 2ᵏ⁻¹
```

This gives us the recurrence relation:

```cpp
binLift[node][i] =
    binLift[ binLift[node][i - 1] ][ i - 1 ];
```

### Intuition

Suppose we want to find the `2¹`-th ancestor of node `5`.

We can:

1. Move to the `2⁰`-th ancestor of node `5` (its parent).
2. From there, again move to its `2⁰`-th ancestor.

So,

```cpp
binLift[5][1] = binLift[ binLift[5][0] ][0];
```

Similarly, to find the `2²`-th ancestor, we combine two `2¹` jumps, and so on.

---

## Important Observation

If at any point,

```text
2⁰-th ancestor = -1
or
2¹-th ancestor = -1
or
2ⁱ-th ancestor = -1
```

then all larger ancestors will also be `-1`.

Once we move beyond the root of the tree, there are no more ancestors to consider.

---

## Answering Queries

To find the k-th ancestor of a node:

1. Look at the binary representation of `k`.
2. For every bit that is set (`1`), jump upward by the corresponding power of 2.

For example:

```text
k = 13

13 = 1101₂
   = 2⁰ + 2² + 2³
```

So we perform:

```text
1-step jump
4-step jump
8-step jump
```

and reach the 13-th ancestor.

Since we check at most `log₂(N)` bits, each query takes:

```text
Time Complexity: O(log N)
```

while preprocessing the binary lifting table takes:

```text
Time Complexity: O(N log N)
Space Complexity: O(N log N)
```

*/

class TreeAncestor {
public:
    int binLift[50001][20];
    TreeAncestor(int n, vector<int>& parent) {

        memset(binLift, -1, sizeof(binLift));

      //Putting the value of immediate parent of every node /2^0 parent 
        for(int i=0;i<n;i++){
            binLift[i][0] = parent[i];
        }

      //Finding all the power of  2 parents
        for(int k=1;k<20;k++){
            for(int node = 0;node<n;node++){
                if(binLift[node][k-1]!=-1) binLift[node][k] = binLift[binLift[node][k-1]][k-1];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
    
        for(int bit=0;bit<20;bit++){
            if((k>>bit)&1){
                if(node!=-1) node = binLift[node][bit];
            }
        }
        return node;
    }
};
