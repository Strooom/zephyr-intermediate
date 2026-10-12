#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

struct sensorData {
    uint32_t measurementValue;
    uint32_t timestampInMs;
};

static void onSensorData(const struct zbus_channel *chan)
{
    const struct sensorData *data = static_cast<const sensorData *>(zbus_chan_const_msg(chan));
    LOG_INF("display %u, %u", data->measurementValue, data->timestampInMs);
}
// ZBUS_LISTENER_DEFINE(display_lis, onSensorData);
// ZBUS_SUBSCRIBER_DEFINE(logger_sub, 4);

ZBUS_CHAN_DEFINE(mySensorChannel, sensorData, NULL, NULL, ZBUS_OBSERVERS(syncListener), ZBUS_MSG_INIT(.measurementValue = 0, .timestampInMs = 0));

static void onTimerExpiry(struct k_timer *timer)
{
    struct sensorData someData;
    someData.measurementValue = 123;
    someData.timestampInMs = k_uptime_get_32();
    LOG_INF("publish %u, %u", someData.measurementValue, someData.timestampInMs);    
    zbus_chan_pub(&mySensorChannel, &someData, K_NO_WAIT);
}
K_TIMER_DEFINE(theTimer, onTimerExpiry, NULL);


void mySynchronousListener(const struct zbus_channel *chan)
{
    const struct sensorData *msg = static_cast<const sensorData *>(zbus_chan_const_msg(chan));
    LOG_INF("listenSynchronous %u, %u", msg->measurementValue, msg->timestampInMs);    
}
ZBUS_LISTENER_DEFINE(syncListener, mySynchronousListener);

int main(void)
{
    LOG_INF("Starting timer");
    k_timer_start(&theTimer, K_MSEC(1000), K_MSEC(1000));

    while (true) {
        k_sleep(K_MSEC(100));
    }

    return 0;
}

