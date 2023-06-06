# Problem 1: How To Complie and Run Source code

- You need to have a C/C++ compiler on your operating system, i used mingw-w64

- open terminal in the file location ```Problem1```

- to compile the code run this command in the opened terminal: ```gcc -o main main.c``` [You can skip this step, you have the .exe file already]

- to execute the code run this command in the opened terminal: ```./main.exe```


# Development Environment

You will see a main.c file in which the code is implemented. at the end of the file, you will see a second solution which came to my mind and i explained why it is more efficient than the solution i implemented. but i didn't write its code, for readonly.




# Step by Step Functions Explaination (if it is required)
- Define the enum typeTag to accept ADD, SUB, FIB, INT Types and the node to have type, value, left node ptr, right node ptr
- the type defintion for the function pointer takes two void and return pointer of node
```c

typedef enum TypeTag {
  ADD, SUB, MUL, FIB, INT
} TypeTag;

typedef struct Node {
  TypeTag type;
  int value;
  struct Node *left;
  struct Node *right;
} Node;

typedef Node* (*FuncPtr)(void*, void*);

```

- Define the a function that takes two void args (so that we can pass int or node)
- makeNode: builds a node from the passed type, store its memory address in an array, so that we can later check if the passed arg is one of those memory, otherwise it will not be node, propably int
- makeIntNode: creates a new node that has a value that will act as a base-case node 
```c

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
```

- checks if the passed arg one of the stored nodes we created
```c
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

```
- creates the node, decide if left/right will be intNode or if it is already a node
```c
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

```
- each function will be called based on the passed typetag. pass this type to "operation" func
```c
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
```

- return a specific function based on the given typetag

```c
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
```

- fibonacci using dynamic programming bottu-up approach. avoiding recursion
```c
int fibonacci(int n) {
  int fib[n+1];
  fib[0] = 0;
  fib[1] = 1;
  for(int i = 2; i <= n; i++) {
      fib[i] = fib[i-1] + fib[i-2];
  }
  return fib[n];
}
```

- Recursivly traverse the node tree, calculate each node based on type. returns the result

```c
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
  return result;
}

```

```c
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
```