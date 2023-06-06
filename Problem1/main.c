#include <stdio.h>
#include <stdlib.h>

long long nodeIps[50] = {};
int intIpIdx = 0;

typedef enum TypeTag {
  ADD, SUB, MUL, FIB, INT
} TypeTag;

typedef struct Node {
  TypeTag type;
  int value;
  struct Node *left;
  struct Node *right;
} Node;

// defenition of makeFunc
typedef Node* (*FuncPtr)(void*, void*);

Node* makeNode(TypeTag type) {
  Node* node = (Node*)malloc(sizeof(Node));
  
  // store it in nodeIps
  nodeIps[intIpIdx] = (int)node;
  intIpIdx++;

  node->type = type;
  node->left = NULL;
  node->right = NULL;
  // return node;
}

Node* makeIntNode(int value) {
  Node *node = makeNode(INT);
  node->value = value;
  // return node;
}

/*
Because i wasted 5 hours trying to figure out how to know the type that the void* arg points to, i came up with this idea:
each node we make, i store it in nodeIps, hence, when we pass int i will know
*/
int isNode(void* arg) {
  int found = 0;
  int i = 0;
  while(nodeIps[i] != 0) {    
    if(((int*)(arg)) == nodeIps[i]) {
      found = 1;
      break;
    }
    i++;
  }
  return found;
}


/*
receives arg1 and arg2, creates a node, build left and right nodes.
if isNode, we simply make the left of the node the passed in node itself.
else, we create an int node, which a node that has a value but no left or right, set left or right to newly created node  
*/
Node* operation(void* arg1, void* arg2, TypeTag type) {
  
  Node* node = makeNode(type);
  
  if(isNode(arg1)) {
    node->left = arg1;
  } else{
    node->left = makeIntNode(arg1);
  }

  if(isNode(arg2)) {
    node->right = arg2;
  } else {
    node->right = makeIntNode(arg2);
  }


  return node;
}

// each function will be called based on the passed typetag. pass this type to "operation" func
// their logic is the same, that's why i created the "operation" function
Node* add(void* arg1, void* arg2) {
  return operation(arg1, arg2, ADD);
}

Node* mul(void* arg1, void* arg2) {
  return operation(arg1, arg2, MUL);
}

Node* sub(void* arg1, void* arg2) {
  return operation(arg1, arg2, SUB);
}

Node* fib(void* arg1, void* arg2) {
  return operation(arg1, arg2, FIB);
}


// return a specific function based on the given typetag
Node* (*makeFunc(TypeTag type))(void*, void*) {
  switch(type) {
    case ADD:
      return &add;
      break;
    case SUB:
      return &sub;
      break;
    case MUL:
      return &mul;
      break;      
    case FIB:
      return &fib;
      break;
    default:
      printf("Unknown TypeTag\n");     
  }
}

// fibonacci using dynamic programming bottu-up approach. avoiding recursion
int fibonacci(int n) {
  int fib[n+1];
  fib[0] = 0;
  fib[1] = 1;
  for(int i = 2; i <= n; i++) {
      fib[i] = fib[i-1] + fib[i-2];
  }
  return fib[n];
}

// Recursivly traverse the node tree, calculate each node based on type. returns the result

int calc(Node* node) {
  int result;
  if (node->type == ADD) {
      result = calc(node->left) + calc(node->right);
  } else if (node->type == SUB) {
      result = calc(node->left) - calc(node->right);
  } else if (node->type == MUL) {
      result = calc(node->left) * calc(node->right);
  } else if (node->type == FIB) {
      int n = calc(node->left);
      result = fibonacci(abs(n));
  } else if (node->type == INT) {
      result = node->value;
  } else {
    printf("Unknown node type %d\n", node->type);
  }
  // printf("NodeType: %d    Result: %d\n", node->type, result);
  return result;
}


int main() {
  // build our node tree
  Node *add = (*makeFunc(ADD))(10, 6);
  Node *mul = (*makeFunc(MUL))(5, 4); 
  Node *sub = (*makeFunc(SUB))(add, mul);  // 1st-2nd
  Node *fibo = (*makeFunc(FIB))(sub, NULL);

  // calculate the node, print it
  printf("%d\n", calc(add));
  printf("%d\n", calc(mul));
  printf("%d\n", calc(sub));
  printf("%d\n", calc(fibo));
}

/*
Another Solution:

Creating a tree of nodes is ineffecient because we need to recursively go through the entire tree each time we call calc() to calculate the result. i just thought the main goal was to create the tree structure, that's why i decided i would go with this solution.

However, A more efficient way of solving this problem would have been to build separate nodes
each node has its type and its left and right which are base-nodes (intNode) that have values.  

When we want to make a new node and pass another node to its left/right, instead of assigning the node to the left/right,  Node *sub = (*makeFunc(SUB))(add, mul), we want to immediately calculate the passed-in node's value, make an intNode with that value. assign it to left/right. return this new node

Based on the nodes created in the main function, this will make this shape:

         Node(type:ADD)      
        /              \    
 Node(val:5)     Node(val:6)
 type: INT       type: INT

         Node(type:MUL)      
        /              \    
 Node(val:5)     Node(val:4)
 type: INT       type: INT

                                  Node(type:SUB)      
                                /                \    
 Node(val:20(created after evaluating mul))     Node(val:16(calculated after evaluating ADD))
 type:INT                                       type:INT

                                      Node(type:FIBO)      
                                      /              \    
 Node(val:4(created after evaluating abs(SUB)))       NULL
 type:INT

*/
// Mustafa Mahmoud
