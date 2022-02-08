## My Answers
1.SJF and FIFO are same, just change the FIFO to SJF.

```
> python ./scheduler.py -p FIFO -l 200,200,200 -c
...
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00
```


2.SJF and FIFO are same, just change the FIFO to SJF.

```
> python ./scheduler.py -p SJF -l 100,200,300 -c
...
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00
```


3

```
> python ./scheduler.py -p RR -l 200,200,200 -c
...
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 598.00  Wait 398.00
  Job   1 -- Response: 1.00  Turnaround 599.00  Wait 399.00
  Job   2 -- Response: 2.00  Turnaround 600.00  Wait 400.00
```


4.Jobs which are increasing in size or same size.


5.The scheduling quantum of RR is larger than the largest job and when the jobs arrive in order of increasing job size. [Resourse](https://homeostasis.scs.carleton.ca/wiki/index.php/Operating_Systems_2014F:_Assignment_3)  


6.The response time will be increased.


7.The response time will increase; The bad response time is (n-1)*q.
