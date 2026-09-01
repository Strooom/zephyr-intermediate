# Remarks for the Iomico reviewer

## l1-task1
* added 3 thread bodies, and started 3 threads with low, medium, high priority. Each body logs a msg when it runs
* the scheduling appears correct, although there is 310 ms timeout even if the sleep is only 300 ms... Strange
* then added the 4th thread, cooperative thread. Now the other threads are no longer running because the cooperative thread always has priority. It yields, but never sleeps.
* Added a startup delay of 1 second for the cooperative thread. The 3 other threads can do some work, then after 1 second, the cooperative thread again takes the whole CPU

```
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> demo: High priority thread is running
[00:00:00.000,000] <inf> demo: Medium priority thread is running
[00:00:00.000,000] <inf> demo: Low priority thread is running
[00:00:00.110,000] <inf> demo: High priority thread is running
[00:00:00.210,000] <inf> demo: Medium priority thread is running
[00:00:00.220,000] <inf> demo: High priority thread is running
[00:00:00.310,000] <inf> demo: Low priority thread is running
[00:00:00.330,000] <inf> demo: High priority thread is running
[00:00:00.420,000] <inf> demo: Medium priority thread is running
[00:00:00.440,000] <inf> demo: High priority thread is running
[00:00:00.550,000] <inf> demo: High priority thread is running
[00:00:00.620,000] <inf> demo: Low priority thread is running
[00:00:00.630,000] <inf> demo: Medium priority thread is running
[00:00:00.660,000] <inf> demo: High priority thread is running
[00:00:00.770,000] <inf> demo: High priority thread is running
[00:00:00.840,000] <inf> demo: Medium priority thread is running
[00:00:00.880,000] <inf> demo: High priority thread is running
[00:00:00.930,000] <inf> demo: Low priority thread is running
[00:00:00.990,000] <inf> demo: High priority thread is running
[00:00:01.010,000] <inf> demo: Cooperative thread running
[00:00:01.020,000] <inf> demo: Cooperative thread yielding
[00:00:01.020,000] <inf> demo: Cooperative thread running
[00:00:01.030,000] <inf> demo: Cooperative thread yielding
[00:00:01.030,000] <inf> demo: Cooperative thread running
[00:00:01.040,000] <inf> demo: Cooperative thread yielding
[00:00:01.040,000] <inf> demo: Cooperative thread running
[00:00:01.050,000] <inf> demo: Cooperative thread yielding
[00:00:01.050,000] <inf> demo: Cooperative thread running
[00:00:01.060,000] <inf> demo: Cooperative thread yielding
[00:00:01.060,000] <inf> demo: Cooperative thread running
[00:00:01.070,000] <inf> demo: Cooperative thread yielding
[00:00:01.070,000] <inf> demo: Cooperative thread running
```

## l2-task1
* I recreated the 2 thread with common counter example
* I noticed that threadTwo was only started after threadOne finished -> corrected this by adding CONFIG_TIMESLICING=y to prj.conf.  Then both threads start and run simultaneously.
* When running it on the native-sim, it was not possible to reproduce the race condition. I tried several things, but maybe the PC is too fast so the thread still finish before being interrupted.
* Then I move to a devkit, in my case I took the FRDM-MCXA153, as it has a handy onboard debuglink / serial, all in one USB-C
* Now the race condition appears : counter should be 100.000 but shows a smaller number, different every run.
* Sometimes the count is still 100.000, so the race condition is a tough thing to reproduce, probably even tougher to debug

```
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,274] <inf> demo: Starting threads : counter = 0
[00:00:00.000,375] <inf> demo: Thread threadOne started
[00:00:00.010,442] <inf> demo: Thread threadTwo started
[00:00:00.025,115] <inf> demo: Thread threadOne finished
[00:00:00.030,077] <inf> demo: Thread threadTwo finished
[00:00:00.030,184] <inf> demo: Threads ready : counter = 83983
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,274] <inf> demo: Starting threads : counter = 0
[00:00:00.000,375] <inf> demo: Thread threadOne started
[00:00:00.010,442] <inf> demo: Thread threadTwo started
[00:00:00.025,113] <inf> demo: Thread threadOne finished
[00:00:00.030,074] <inf> demo: Thread threadTwo finished
[00:00:00.030,181] <inf> demo: Threads ready : counter = 66243
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,274] <inf> demo: Starting threads : counter = 0
[00:00:00.000,375] <inf> demo: Thread threadOne started
[00:00:00.010,442] <inf> demo: Thread threadTwo started
[00:00:00.025,116] <inf> demo: Thread threadOne finished
[00:00:00.030,079] <inf> demo: Thread threadTwo finished
[00:00:00.030,186] <inf> demo: Threads ready : counter = 83980
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,274] <inf> demo: Starting threads : counter = 0
[00:00:00.000,375] <inf> demo: Thread threadOne started
[00:00:00.010,442] <inf> demo: Thread threadTwo started
[00:00:00.025,117] <inf> demo: Thread threadOne finished
[00:00:00.030,080] <inf> demo: Thread threadTwo finished
[00:00:00.030,187] <inf> demo: Threads ready : counter = 66251
```