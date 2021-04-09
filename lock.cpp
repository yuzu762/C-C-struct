static inline void xspin_lock(volatile uint32_t *flag) {
   while(__sync_lock_test_and_set(flag,1)){
     while（*flag） {
 #ifdef __amd64__ 
        __asm__("pause" ::: "memory");
 #endif
 #ifdef __powerpc64__
        __asm__("or 1, 1, 1" ::: "memory");
           __asm__("or 2, 2, 2" ::: "memory");
 #endif
     }
   }
}

static inline void xspin_unlock(volatile uint32_t *flag) {
   __sync_lock_release(flag);
}
