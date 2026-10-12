#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

struct sensorData {
    uint32_t measurementValue;
    uint32_t timestampInMs;
};

ZBUS_CHAN_DEFINE(mySensorChannel, sensorData, NULL, NULL, ZBUS_OBSERVERS(syncListener, asyncListener), ZBUS_MSG_INIT(.measurementValue = 0, .timestampInMs = 0));

static void onTimerExpiry(struct k_timer *timer)
{
    struct sensorData someData;
    someData.measurementValue = 123;
    someData.timestampInMs = k_uptime_get_32();
    LOG_INF("publish %u, %u", someData.measurementValue, someData.timestampInMs);    
    zbus_chan_pub(&mySensorChannel, &someData, K_NO_WAIT);
}
K_TIMER_DEFINE(theTimer, onTimerExpiry, NULL);


void mySynchronousListener(const struct zbus_channel *someChannel)
{
    const struct sensorData *msg = static_cast<const sensorData *>(zbus_chan_const_msg(someChannel));
    LOG_INF("listenSynchronous %u, %u", msg->measurementValue, msg->timestampInMs);    
}
ZBUS_LISTENER_DEFINE(syncListener, mySynchronousListener);

ZBUS_SUBSCRIBER_DEFINE(asyncListener, 8); 

int main(void)
{
    LOG_INF("Starting timer");
    k_timer_start(&theTimer, K_MSEC(1000), K_MSEC(1000));

    while (true) {
        k_sleep(K_MSEC(2000));

        const struct zbus_channel *someChannel;
        while (!zbus_sub_wait(&asyncListener, &someChannel, K_FOREVER)) 
            {
            struct sensorData msg;
            zbus_chan_read(someChannel, &msg, K_MSEC(100));
            LOG_INF("listenAsynchronous %u, %u", msg.measurementValue, msg.timestampInMs);
        }
    }
    return 0;
}

