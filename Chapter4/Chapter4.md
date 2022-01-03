## My Answers
1. 100%

```
> python process-run.py -l 5:100,5:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2        RUN:cpu         READY             1
  3        RUN:cpu         READY             1
  4        RUN:cpu         READY             1
  5        RUN:cpu         READY             1
  6           DONE       RUN:cpu             1
  7           DONE       RUN:cpu             1
  8           DONE       RUN:cpu             1
  9           DONE       RUN:cpu             1
 10           DONE       RUN:cpu             1

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```


2. 11 
    = 4(process0) + 2(process1Run) + 5(defalut waiting time due to 0% hit rate)

```
> python process-run.py -l 4:100,1:0 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2        RUN:cpu         READY             1
  3        RUN:cpu         READY             1
  4        RUN:cpu         READY             1
  5           DONE        RUN:io             1
  6           DONE       WAITING                           1
  7           DONE       WAITING                           1
  8           DONE       WAITING                           1
  9           DONE       WAITING                           1
 10           DONE       WAITING                           1
 11*          DONE   RUN:io_done             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```


3. 7 IOs
    Due to the PID is free when run process0, the waiting time can start process1

```
> python process-run.py -l 1:0,4:100 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```


4. When process0 finished, process1 start

```
> python process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END   
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        WAITING         READY                           1
  3        WAITING         READY                           1
  4        WAITING         READY                           1
  5        WAITING         READY                           1
  6        WAITING         READY                           1
  7*   RUN:io_done         READY             1
  8           DONE       RUN:cpu             1
  9           DONE       RUN:cpu             1
 10           DONE       RUN:cpu             1
 11           DONE       RUN:cpu             1
```


5. The waiting of process0 can start process1

```
> python process-run.py -l 1:0,4:100 -c -SSWITCH_ON_IO  
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1              
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1              
```


6. Underutilized

```
> python process-run.py ./process-run.py -l 3:0,5:100,5:100,5:100 -SSWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1              
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1              
  8          READY          DONE       RUN:cpu         READY             1              
  9          READY          DONE       RUN:cpu         READY             1              
 10          READY          DONE       RUN:cpu         READY             1              
 11          READY          DONE       RUN:cpu         READY             1
 12          READY          DONE          DONE       RUN:cpu             1
 13          READY          DONE          DONE       RUN:cpu             1
 14          READY          DONE          DONE       RUN:cpu             1
 15          READY          DONE          DONE       RUN:cpu             1
 16          READY          DONE          DONE       RUN:cpu             1
 17    RUN:io_done          DONE          DONE          DONE             1
 18         RUN:io          DONE          DONE          DONE             1
 19        WAITING          DONE          DONE          DONE                           1 
 20        WAITING          DONE          DONE          DONE                           1 
 21        WAITING          DONE          DONE          DONE                           1 
 22        WAITING          DONE          DONE          DONE                           1 
 23        WAITING          DONE          DONE          DONE                           1 
 24*   RUN:io_done          DONE          DONE          DONE             1
 25         RUN:io          DONE          DONE          DONE             1
 26        WAITING          DONE          DONE          DONE                           1 
 27        WAITING          DONE          DONE          DONE                           1 
 28        WAITING          DONE          DONE          DONE                           1 
 29        WAITING          DONE          DONE          DONE                           1 
 30        WAITING          DONE          DONE          DONE                           1 
 31*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
```


7. It can fully use the Waiting to run other process

```
> python process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1              
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1              
  8         RUN:io          DONE         READY         READY             1              
  9        WAITING          DONE       RUN:cpu         READY             1             1
 10        WAITING          DONE       RUN:cpu         READY             1             1
 11        WAITING          DONE       RUN:cpu         READY             1             1
 12        WAITING          DONE       RUN:cpu         READY             1             1
 13        WAITING          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1              
 15         RUN:io          DONE          DONE         READY             1              
 16        WAITING          DONE          DONE       RUN:cpu             1             1
 17        WAITING          DONE          DONE       RUN:cpu             1             1 
 18        WAITING          DONE          DONE       RUN:cpu             1             1 
 19        WAITING          DONE          DONE       RUN:cpu             1             1 
 20        WAITING          DONE          DONE       RUN:cpu             1             1 
 21*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)
```

8. 

```
> python process-run.py -s 1 -l3:50,3:50, -s 2 -l 3:50,3:50, -s 3 -l 3:50,3:50 -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2         RUN:io         READY             1
  3        WAITING        RUN:io             1             1
  4        WAITING       WAITING                           2
  5        WAITING       WAITING                           2
  6        WAITING       WAITING                           2
  7        WAITING       WAITING                           2
  8*   RUN:io_done       WAITING             1             1
  9*       RUN:cpu         READY             1
 10           DONE   RUN:io_done             1
 11           DONE        RUN:io             1
 12           DONE       WAITING                           1
 13           DONE       WAITING                           1
 14           DONE       WAITING                           1
 15           DONE       WAITING                           1
 16           DONE       WAITING                           1
 17*          DONE   RUN:io_done             1
 18           DONE       RUN:cpu             1

Stats: Total Time 18
Stats: CPU Busy 9 (50.00%)
Stats: IO Busy  11 (61.11%)
```