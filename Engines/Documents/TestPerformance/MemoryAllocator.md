
```log
int numOfObjects = 2000000; // first test

[22:48:54] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:18531] Delete operator takes: 0.912389349 seconds
[22:48:55] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:18531] LinearAllocator takes: 0.7109223339999999 seconds
[22:48:56] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:18531] StackAllocator takes: 0.73726347 seconds
[22:48:57] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:18531] PoolAllocator takes: 0.637863224 seconds
```

```log
	int numOfObjects = 2000000; // second test

[22:59:20] [onAttach:23] [Client] [Thread:19355] UserPlayLayer is attached
[22:59:21] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:19355] Delete operator takes: 0.848011402 seconds
[22:59:21] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:19355] LinearAllocator takes: 0.580407825 seconds
[22:59:22] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:19355] StackAllocator takes: 0.617281946 seconds
[22:59:23] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:19355] PoolAllocator takes: 0.567030486 seconds
```

```log
	int numOfObjects = 20000;
[23:01:41] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:19469] Delete operator takes: 0.010341232 seconds
[23:01:41] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:19469] LinearAllocator takes: 0.005868733 seconds
[23:01:41] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:19469] StackAllocator takes: 0.007162491 seconds
[23:01:41] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:19469] PoolAllocator takes: 0.052259977 seconds

```

```log
	int numOfObjects = 3000000; // over
[23:03:40] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:19745] Delete operator takes: 1.5474912349999999 seconds
[23:03:40] [memAllocate:20] [ViSolEngine] [Thread:19745] LinearAllocator is full, can not allocate for new data with size 40
./tools/script/run.sh: line 8: 19745 Segmentation fault      (core dumped) ./build/bin/ViRobot
```

```log
	int numOfObjects = 100000;
[23:05:44] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:20035] Delete operator takes: 0.045524744 seconds
[23:05:44] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:20035] LinearAllocator takes: 0.029000454000000002 seconds
[23:05:44] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:20035] StackAllocator takes: 0.040112397 seconds
[23:05:44] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:20035] PoolAllocator takes: 0.06399729700000001 seconds
[23:05:44] [testPerformanceMemoryAllocator:277] [ViSolEngine] [Thread:20035] DONE TESTING MEMROY ALLOCATOR

```

```log
	int numOfObjects = 700000;
[23:07:47] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:20202] Delete operator takes: 0.23521838 seconds
[23:07:47] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:20202] LinearAllocator takes: 0.195341699 seconds
[23:07:48] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:20202] StackAllocator takes: 0.19809775200000002 seconds
[23:07:48] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:20202] PoolAllocator takes: 0.195321568 seconds
[23:07:48] [testPerformanceMemoryAllocator:277] [ViSolEngine] [Thread:20202] DONE TESTING MEMROY ALLOCATOR


[23:09:18] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:20250] Delete operator takes: 0.248607516 seconds
[23:09:18] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:20250] LinearAllocator takes: 0.17804547199999998 seconds
[23:09:18] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:20250] StackAllocator takes: 0.189174355 seconds
[23:09:19] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:20250] PoolAllocator takes: 0.19122577799999999 seconds
[23:09:19] [testPerformanceMemoryAllocator:277] [ViSolEngine] [Thread:20250] DONE TESTING MEMROY ALLOCATOR


```


```log
	int numOfObjects = 400000;
[23:10:38] [testPerformanceMemoryAllocator:196] [ViSolEngine] [Thread:20346] Delete operator takes: 0.141092565 seconds
[23:10:38] [testPerformanceMemoryAllocator:223] [ViSolEngine] [Thread:20346] LinearAllocator takes: 0.104193178 seconds
[23:10:38] [testPerformanceMemoryAllocator:249] [ViSolEngine] [Thread:20346] StackAllocator takes: 0.111988722 seconds
[23:10:38] [testPerformanceMemoryAllocator:275] [ViSolEngine] [Thread:20346] PoolAllocator takes: 0.123882674 seconds
[23:10:38] [testPerformanceMemoryAllocator:277] [ViSolEngine] [Thread:20346] DONE TESTING MEMROY ALLOCATOR
```