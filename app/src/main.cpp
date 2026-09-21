#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

static void work001Handler(struct k_work *work)
{
    ARG_UNUSED(work);
    LOG_INF("workHandler : %u", k_uptime_get_32());
}
K_WORK_DEFINE(workThread001, work001Handler);

static void onTimer001Expiry(struct k_timer *timer)
{
    if (k_is_in_isr()) {
        LOG_INF("ISR : %u", k_uptime_get_32());
    } else {
        LOG_INF("Thread : %u", k_uptime_get_32());
    }
    k_work_submit(&workThread001);
}
K_TIMER_DEFINE(timer001, onTimer001Expiry, NULL);


int main(void)
{
    LOG_INF("Starting timer");
    k_timer_start(&timer001, K_MSEC(1000), K_MSEC(1000));
    while (true) {
        k_sleep(K_MSEC(500));
        if (k_uptime_get_32() > 10000) {
            LOG_INF("Stopping timer");
            k_timer_stop(&timer001); 
            break;
        }
    }
    return 0;
}








// static constexpr uint32_t defaultThreadStackSize{1024U};
// static constexpr int32_t threadPriority{5};
// static constexpr int32_t nmbrOfLoops{50000U};

// static volatile uint64_t testCounter{};
// static struct k_sem ready;

// void workerFunction(void *p1, void *p2, void *p3)
// {
// const char *threadName = k_thread_name_get(k_current_get());
//     LOG_INF("Thread %s started", threadName);
//     for (uint32_t index = 0; index < nmbrOfLoops; ++index) {
//         uint64_t temp = testCounter;
//         temp++;
//         testCounter = temp;
//     }
//     LOG_INF("Thread %s finished", threadName);
//     k_sem_give(&ready);
// }


// K_THREAD_DEFINE(threadOne, defaultThreadStackSize, workerFunction, NULL, NULL, NULL, threadPriority, 0, 0);
// K_THREAD_DEFINE(threadTwo, defaultThreadStackSize, workerFunction, NULL, NULL, NULL, threadPriority, 0, 0);


// int main(void)
// {
//     k_sem_init(&ready, 0, 2);
//     LOG_INF("Starting threads : counter = %llu", testCounter);
//     k_sem_take(&ready, K_FOREVER);
//     k_sem_take(&ready, K_FOREVER);
//     LOG_INF("Threads ready : counter = %llu", testCounter);
//     return 0;
// }

