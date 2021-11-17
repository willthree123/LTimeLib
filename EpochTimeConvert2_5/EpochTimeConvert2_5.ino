


typedef unsigned long time_t;

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )// leap year calulator expects year argument as years offset from 1970

static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

extern "C++" {
typedef struct  { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month; 
  uint8_t Year;   // offset from 1970; 
}   tmElements_t;
time_t makeTime(tmElements_t &tm);  // convert time elements into time_t
} // extern "C++"


time_t makeTime(tmElements_t &tm){    
  int i;
  uint32_t seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds= tm.Year*(SECS_PER_DAY * 365);
  for (i = 0; i < tm.Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds +=  SECS_PER_DAY;   // add extra days for leap years
    }
  }
  
  // add days for this year, months start from 1
  for (i = 1; i < tm.Month; i++) {
    if ( (i == 2) && LEAP_YEAR(tm.Year)) { 
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds+= (tm.Day-1) * SECS_PER_DAY;
  seconds+= tm.Hour * SECS_PER_HOUR;
  seconds+= tm.Minute * SECS_PER_MIN;
  seconds+= tm.Second;
  return (time_t)seconds; 
}

/*==============================================================================*/
unsigned long epochConverter(char rawTime[21]){
  tmElements_t my_time;  // time elements structure
  time_t unix_timestamp; // a timestamp
  
  int tmpTime[13];//yyMMddhhmmss
  int cursor=0;
  int counter=0;

  //Convert the String input to int array
  for(int i=0;i<6;i++){
    for(int k=0;k<2;k++){
      tmpTime[cursor-counter] = rawTime[cursor]-'0';
      cursor++;
    }
    cursor++;
    counter++;
  }

  //Storing variables into my_time
  my_time.Year = (2000 + tmpTime[0]*10 + tmpTime[1]) - 1970; // years since 1970, so deduct 1970
  my_time.Month = tmpTime[2]*10 + tmpTime[3];      // months start from 0, so deduct 1
  my_time.Day = tmpTime[4]*10 + tmpTime[5];
  my_time.Hour = tmpTime[6]*10 + tmpTime[7];
  my_time.Minute = tmpTime[8]*10 + tmpTime[9];
  my_time.Second = tmpTime[10]*10 + tmpTime[11];

  unix_timestamp =  makeTime(my_time);
  //Serial.println(unix_timestamp);
  return unix_timestamp;
}

/*==============================================================================*/

int const DELAY=10000;
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Epoch Time for \"99/12/31,23:59:59+32\" :");
  Serial.println(epochConverter("99/12/31,23:59:59+32"));
  Serial.print("Epoch Time for \"38/01/19,03:14:08+32\" :");
  Serial.println(epochConverter("38/01/19,03:14:08+32"));
  Serial.print("Epoch Time for \"38/01/19,03:14:06+32\" :");
  Serial.println(epochConverter("38/01/19,03:14:06+32"));
  Serial.print("Epoch Time for \"21/11/16,08:50:06+32\" :");
  Serial.println(epochConverter("21/11/16,08:50:06+32"));
  Serial.println("");
  delay(DELAY);
}
