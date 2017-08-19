# Parallel_processing


Problem Introduction
In this problem you will simulate a program that processes a list of jobs in parallel. Operating systems such as Linux, MacOS or Windows all have special programs in them called schedulers which do exactly this with the programs on your computer.

Problem Description
Task. You have a program which is parallelized and uses � independent threads to process the given list of m jobs. Threads take jobs in the order they are given in the input. If there is a free thread, it immediately takes the next job from the list. If a thread has started processing a job, it doesn’t interrupt or stop until it fnishes processing the job. If several threads try to take jobs from the list simultaneously, the thread with smaller index takes the job. For each job you know exactly how long will it take any thread to process this job, and this time is the same for all the threads. You need to determine for each job which thread will process it and when will it start processing.

Input Format. The frst line of the input contains integers n and m.
The second line contains m integers t_i — the times in seconds it takes any thread to process i-th job.
The times are given in the same order as they are in the list from which threads take jobs.
Threads are indexed starting from 0.
Constraints. 1 ≤ n ≤ 105; 1 ≤ m ≤ 105; 0 ≤ t_i ≤ 109.
Output Format. Output exactly m lines. i-th line (0-based index is used) should contain two spaceseparated integers — the 0-based index of the thread which will process the i-th job and the time in
seconds when it will start processing that job.
Time Limits. C: 1 sec, C++: 1 sec, Java: 4 sec, Python: 6 sec. C#: 1.5 sec, Haskell: 2 sec, JavaScript:
6 sec, Ruby: 6 sec, Scala: 6 sec.
Memory Limit. 512Mb.