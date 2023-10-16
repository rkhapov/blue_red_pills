#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Your Module Description");
MODULE_VERSION("0.01");

static void get_current_tick(uint64_t *ticks) {
    unsigned int lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    *ticks = ((unsigned long long)(hi) << 32) | lo;
}

static int __init lkm_example_init(void) {
    uint64_t start_time, end_time, sum_time;
sum_time=0;
    unsigned int ecx = 0; // XCR0 register index
    unsigned int xcr0;    // XCR0 value

    // Check if the CPU supports AVX
    int avxSupported = 0;
    asm volatile (
        "cpuid"
        : "+c"(ecx), "=a"(xcr0)
        : "a"(1)
        : "ebx", "edx"
    );

    if (ecx & (1 << 28)) {
        printk(KERN_INFO "AVX is supported by the CPU.\n");
        avxSupported = 1;
    } else {
        printk(KERN_INFO "AVX is not supported by the CPU.\n");
    }

    // If AVX is supported, enable it in XCR0
    if (avxSupported) {
    int i = 0;
    for(i=0; i<100; i++){
       get_current_tick(&start_time);
        asm volatile (
            "xgetbv"
            : "=a"(xcr0)
            : "c"(0)
            : "edx"
        );

        xcr0 |= (1 << 2);  // Set the AVX bit (bit 2)

        asm volatile (
            "xsetbv"
            :
            : "c"(0), "a"(xcr0), "d"(xcr0 >> 32)
            : "memory"
        );
             xcr0 &= ~(1 << 2); 
    get_current_tick(&end_time);
    sum_time+=end_time-start_time;
    printk(KERN_INFO "start-end: %llu - %llu\n", start_time, end_time);
    }
    printk(KERN_INFO "Time this time taken: %llu\n", sum_time/100);}
    return 0;}

static void __exit lkm_example_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
