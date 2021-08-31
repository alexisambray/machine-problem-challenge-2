/*
        Challenge #6 header file.

        This file will be included in your source codes for Challenges #7 and
   *8.

    Do NOT forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1:  AMBRAY, ALEXIS               SECTION: S13
    LASTNAME2, FIRSTNAME2:  MUROS, DON DAVID             SECTION: S11

    DATE SUBMITTED     : August 23, 2021
*/

/*
        Do NOT change the lines that contain #ifndef, #define and #endif
   processor directives.
*/
#ifndef C6_DEFINED

#define C6_DEFINED (1)

/*
        You may #define any constants that you need below this comment.
*/
#define MAX_RECORDS 1000

/*
    You may declare any typedef that you need below this comment.
*/
typedef struct {
  double open;   // open value of ohlc
  double high;   // high value of ohlc
  double low;    // low value of ohlc
  double close;  // close value of ohlc
} Ohlc;

/*
        Do NOT change the next two typedef declarations.

        You should use StrDate alias for a string that represents date.
        You should use StrStock alias for a string that represents the stock
   code, for example: "AMZN".
*/
typedef char StrDate[11];
typedef char StrStock[6];

/*
        TO DO: Declare your struct data type for representing & storing ONE row
   of stock historical data (SHD), i.e., date, OHLC and volume.  Again, it is
   for just one row (or one line of text), NOT for all rows of stock data.

        Use sensible names.

        You are REQUIRED to write sensible inline comments to describe the
   purose/use purpose of each member.
*/
struct ShdTag {
  StrDate date;   // date represents the date in the data
  Ohlc ohlc;      // ohlc represents the open high low close value
  double volume;  // volume represents the volume value in the data
};

/*
        TO DO: Declare a typedef alias for the struct data type you declared
   above.
*/
typedef struct ShdTag Shd;
typedef Shd Shds[MAX_RECORDS];

/*
        TO DO: Declare your struct data type for representing and storing ALL
   values present in a one text file which contains the stock data.

        Use sensible names.

        You are REQUIRED to write sensible inline comments to describe the
   purose/use purpose of each member.
*/
struct StockTag {
  StrStock stockName;  // used for the company name
  int numRecords;      // used for the total number of records in the data
  Shds shds;           // shds is an array of stock historical datas
};

/*
        TO DO: Declare a typedef alias for the struct data type you declared
   above.
*/
typedef struct StockTag Stock;

#endif
