# CommonDataStructuresC
Some basic data structure for C

Containing:
---
linked lists:

  nodes with the information of the next node in the list
  
doubly linked lists:

  nodes with the information of the next and previous node in the list
  
sets:

  a basic way to add an index to search your node, also using linked lists
  
dictionarys:

  adding a value to sets, looking for a set key will return a node that also contains a value now

SetUp:
---
commands:

  create the exe file:
  
      clang.exe -o dictionary.exe .\dictionary.c
  run the exe file:
  
      .\dictionary.exe
  if opcodes are needed get the .o file:
  
      clang.exe -c -o linkedList.o -O0 -g .\linkedList.c
  
