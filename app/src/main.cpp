#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

static constexpr uint32_t messageItemSize = sizeof(uint32_t);
static constexpr uint32_t messageQueueLength = 8;
K_MSGQ_DEFINE(theQueue, messageItemSize, messageQueueLength, 4);

static void onTimerExpiry(struct k_timer *timer)
{
    uint32_t currentTime = k_uptime_get_32();
    LOG_INF("push %u", currentTime);    
    k_msgq_put(&theQueue, &currentTime, K_NO_WAIT);
}
K_TIMER_DEFINE(theTimer, onTimerExpiry, NULL);

int main(void)
{
    	uint32_t level = messageQueueLength - k_msgq_num_free_get(&theQueue);
    LOG_INF("Queue level: %u", level);
    LOG_INF("Starting timer");
    k_timer_start(&theTimer, K_MSEC(1000), K_MSEC(1000));

for (uint32_t loopIndex = 0; loopIndex < 10; ++loopIndex) {
        uint32_t currentTime;
        k_msgq_get(&theQueue, &currentTime, K_FOREVER);
        LOG_INF("pop %u", currentTime);
    }
    return 0;
}

