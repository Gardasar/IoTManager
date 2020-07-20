#pragma once

#include <Arduino.h>
#include <stdint.h>

#include <Ticker.h>
#include <functional>

void tickerFlagHandle(volatile bool *flag);

typedef std::function<void(void *)> tscallback_t;

struct TickerSchedulerItem {
    Ticker t;
    boolean flag = false;
    tscallback_t cb;
    void *cb_arg;
    uint32_t period;
    volatile boolean is_used = false;
};

class TickerScheduler {
   private:
    size_t size;
    TickerSchedulerItem *items = NULL;

    void handleTicker(tscallback_t, void *, boolean *flag);
    static void handleTickerFlag(boolean *flag);

   public:
    TickerScheduler(uint8_t size);
    ~TickerScheduler();

    boolean add(size_t i, uint32_t period, tscallback_t, void *, boolean shouldFireNow = false);
    boolean remove(size_t i);
    boolean enable(size_t i);
    boolean disable(size_t i);
    void enableAll();
    void disableAll();
    void update();

    void print(Print &p);
    void reset();
};

extern TickerScheduler ts;
