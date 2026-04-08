# Data Structures and Algorithms in C

[![C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A comprehensive C implementation of fundamental data structures and algorithms, built incrementally for educational purposes. Perfect for learning low-level programming concepts like memory management, pointers, and recursion.

## Table of Contents

- [Data Structures and Algorithms in C](#data-structures-and-algorithms-in-c)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Project Structure](#project-structure)
  - [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Build Steps](#build-steps)
  - [Usage](#usage)
  - [Examples](#examples)
    - [Linked List](#linked-list)
    - [Stack](#stack)
    - [Queue](#queue)
    - [Binary Search Tree](#binary-search-tree)
  - [Time Complexities](#time-complexities)

## Features

This project implements the following data structures:

- **Linked List**: Dynamic list with append, prepend, insert, remove, and search operations.
- **Stack**: LIFO structure with push, pop, peek, and overflow/underflow checks.
- **Queue**: FIFO structure with enqueue, dequeue, peek, and circular array implementation.
- **Binary Search Tree (BST)**: Tree-based structure with insert, search, and traversals (inorder, preorder, postorder).

All implementations include:
- Memory management (malloc/free)
- Error handling (overflow/underflow)
- Comprehensive tests

## Project Structure

```
data_struct_algor/
├── src/                 # Implementation files (.c)
│   ├── linked_list.c
│   ├── stack.c
│   ├── queue.c
│   └── bst.c
├── include/             # Header files (.h)
│   ├── linked_list.h
│   ├── stack.h
│   ├── queue.h
│   └── bst.h
├── tests/               # Test suites
│   ├── main.c           # Test runner
│   ├── test_linked_list.c
│   ├── test_stack.c
│   ├── test_queue.c
│   └── test_bst.c
├── Makefile             # Build automation
└── README.md            # This file
```

## Installation

### Prerequisites
- GCC compiler (or any C compiler)
- Make utility
- POSIX environment (Linux, macOS, or WSL on Windows)

### Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/DeepCore.git
   cd data_struct_algor
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run tests:
   ```bash
   ./test
   ```

4. Clean up:
   ```bash
   make clean
   ```

## Usage

Include the relevant headers in your C files and link against the compiled objects. For example:

```c
#include "include/linked_list.h"

int main() {
    LinkedList* list = create_list();
    append(list, 42);
    print_list(list);
    destroy_list(list);
    return 0;
}
```

Compile with:
```bash
gcc -Iinclude your_file.c src/linked_list.c -o your_program
```

## Examples

### Linked List
```c
LinkedList* list = create_list();
append(list, 1);
prepend(list, 0);
insert_at(list, 10, 1);
print_list(list);  // 0 -> 10 -> 1 -> NULL
destroy_list(list);
```

### Stack
```c
Stack stack;
init_stack(&stack);
push(&stack, 10);
push(&stack, 20);
printf("Top: %d\n", peek(&stack));  // 20
pop(&stack);  // Removes 20
```

### Queue
```c
Queue queue;
init_queue(&queue);
enqueue(&queue, 10);
enqueue(&queue, 20);
printf("Front: %d\n", peek_queue(&queue));  // 10
dequeue(&queue);  // Removes 10
```

### Binary Search Tree
```c
Node* root = NULL;
root = insert(root, 50);
insert(root, 30);
insert(root, 70);
inorder_traversal(root);  // 30 50 70
destroy_tree(root);
```

## Time Complexities

| Data Structure | Operation | Average | Worst Case |
|----------------|-----------|---------|------------|
| Linked List    | Append/Prepend | O(1) | O(1) |
|                | Insert/Remove at index | O(n) | O(n) |
|                | Find | O(n) | O(n) |
| Stack          | Push/Pop/Peek | O(1) | O(1) |
| Queue          | Enqueue/Dequeue/Peek | O(1) | O(1) |
| BST            | Insert/Search | O(log n) | O(n) |

