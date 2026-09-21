#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

static void workHandler(struct k_work *work)
{
    ARG_UNUSED(work);
    LOG_INF("workHandler : %u", k_uptime_get_32());
}
K_WORK_DEFINE(workThread, workHandler);

static void onTimerExpiry(struct k_timer *timer)
{
    if (k_is_in_isr()) {
        LOG_INF("timer ISR : %u", k_uptime_get_32());
    } else {
        LOG_INF("timer thread : %u", k_uptime_get_32());
    }
    k_work_submit(&workThread);
}
K_TIMER_DEFINE(theTimer, onTimerExpiry, NULL);


int main(void)
{
    LOG_INF("Starting timer");
    k_timer_start(&theTimer, K_MSEC(1000), K_MSEC(1000));
    while (true) {
        k_sleep(K_MSEC(500));
        if (k_uptime_get_32() > 5000) {
            LOG_INF("Stopping timer");
            k_timer_stop(&theTimer); 
            break;
        }
    }
    return 0;
}

