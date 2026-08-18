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
