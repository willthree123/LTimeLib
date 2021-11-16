#ifndef _LTime_h
#ifdef __cplusplus
#define _LTime_h

#if !defined(__time_t_defined) // avoid conflict with newlib or other posix libc
typedef unsigned long time_t;
#endif

extern "C++" {

typedef struct  { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month; 
  uint8_t Year;   // offset from 1970; 
} 	tmElements_t, TimeElements, *tmElementsPtr_t;

//typedef time_t(*getExternalTime)();

/*==============================================================================*/
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)

time_t makeTime(tmElements_t &tm);  // convert time elements into time_t

} // extern "C++"
#endif // __cplusplus
#endif /* _LTime_h */