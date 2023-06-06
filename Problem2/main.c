#include <stdio.h>

/* F1
we need extra variable f2 to calcualte the relation F(n) = F(n-3) - F(n-2)
Advantages:
- This implementation  is of bigO(N) time complexity, F1 is executed n times based on the length of n.
- easy to trace if you don't know recursion.
Disadvantages:
- what if we need to calculate the relation F(n) = F(n-3) + F(n-4) ?
- we will need one more variable to store the fourth variable
- the more variables we need if we change the relation.
*/

// iterative
int F1(int n) {
  if(n <=2) {
    return n;
  }

  int f0 = 0, f1 = 1, f2 = 2, f;

  for(int i = 3; i <= n; i++) {
    f = f0 + f1;
    f0 = f1;
    f1 = f2;
    f2 = f;
  }
  return f;
}





/* F2
This method uses the recursive solution, it creates multiple activation records which will stop when we face the base case(n<=2). for each time F is called, it will call two Fs(Expnonetial behaivour) making it BigO(2^n) 

Advantages:
- very straightforward implementation (even if you don't understand recursion)
Disadvantages:
- slower than the previous solution, this is bigO(2^n) time complexity
- redundant execution of functions makes
*/

// Recursive
int F2(int n) {
  if(n <=2) {
    return n;
  }

  return F2(n-3) + F2(n-2);
}


/* F3
this method uses an array "memo" to store the values of previously calculated functions(of each n) so that we don't re-execute functions who were previously executed. now, after each call F is called with each argument x i.e each f(x) such that 0 <= x <= n. the down if else block will not be caled again, and the first if statement will be called making it a bigO(N).

Advantages:
- Faster Than F2
Disadvantages:
- Still uses recurions which is not the optimal way to go as recursion creates lots of activation records in the call stack
- slower than F1
*/



// memoization
int F3(int n, int memo[]) {
  if (memo[n] != 0)
    return memo[n];


  int result;
  if(n <= 2) {
    result = n;
  } else {
   result = F3(n-3, memo) + F3(n-2, memo);
  }

  memo[n] = result;

  return result;
}



/* F4
Memoization uses recursion to go from up to bottum and stores values from bottum to up,  then why don't we store values from bottum to up in a liear way ? i.e BigO(N) .
We use the recurrence relation f[i-2] and f[i-3] to calculate the value of f[i] based on the previous two values, then we return f[n]

Advantages:
- Faster Than F3, BigO(N)
- avoiding recursion, i.e: iterative

Disadvantages:
- uses more memory than F1

*/


// bottum-up approach
int F4(int n) {
  int fib[n+1];
  fib[0] = 0;
  fib[1] = 1;
  fib[2] = 2;
  for(int i = 3; i <= n; i++) {
      fib[i] = fib[i-2] + fib[i-3];
  }
  return fib[n];
}


int main() {
  int memo[500] = {};
  int n;
  printf("Enter n: ");
  scanf("%d", &n);
  printf("First function: %d\n", F1(n));
  printf("Second function: %d\n", F2(n));
  printf("Third  function: %d\n", F3(n, memo));
  printf("Fourth function: %d\n", F4(n));
  return 0;
}



