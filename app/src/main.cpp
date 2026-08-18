#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

static constexpr uint32_t defaultThreadStackSize{1024U};
static constexpr uint32_t threadLowPriority{7U};
static constexpr uint32_t threadMediumPriority{5U};
static constexpr uint32_t threadHighPriority{3U};

void threadLowPriorityBody(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("Low priority thread is running");
        k_msleep(300);
    }
}

void threadMediumPriorityBody(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("Medium priority thread is running");
        k_msleep(200);
    }
}

void threadHighPriorityBody(void *p1, void *p2, void *p3)
{
    while (1) {
        LOG_INF("High priority thread is running");
        k_msleep(100);
    }
}

K_THREAD_DEFINE(thread_a, defaultThreadStackSize, threadLowPriorityBody,
                NULL, NULL, NULL, threadLowPriority, 0, 0);
// K_THREAD_DEFINE(thread_b, defaultThreadStackSize, threadMediumPriorityBody,
//                 NULL, NULL, NULL, threadMediumPriority, 0, 0);
// K_THREAD_DEFINE(thread_c, defaultThreadStackSize, threadHighPriorityBody,
//                 NULL, NULL, NULL, threadHighPriority, 0, 0);

int main(void)
{
    return 0;
}

