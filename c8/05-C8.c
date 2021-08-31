/*
    Do NOT forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1: AMBRAY, ALEXIS                SECTION: S13
    LASTNAME2, FIRSTNAME2: MUROS, DON DAVID              SECTION: S11

    DATE SUBMITTED     : August 23, 2021

        Make sure that you do the following:

        1. COMPILE your C source code with -Wall directive.

               Example: CCPROG2> gcc -Wall 02-C8.c -o 02-C8.exe

           where 02 is an example group number and C8 is the Challenge number.

           You must replace 02 with your own group number!

        2. RUN the program's exe file in the command line with input and output
   (I/O) redirection.

                        Example: CCPROG2> 02-C8 < AMZN.txt > 02-C8-OUTPUT.txt

       The text file 02-C8-OUTPUT.txt will contain the actual output of your
   program.

    3. COMPARE your program's output your program with the accompanying
   C8-EXPECTED.txt file using bbtest.c.

            In case you do not have bbtest.exe, produce it first by compiling
   bbtest.c as shown below:

                        Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe

                Thereafter, run bbtest.exe with I/O redirection as shown below:

                        Example: CCPROG2> bbtest C8-EXPECTED.txt
   02-C8-OUTPUT.TXT > 02-C8-BBTEST.txt

                The output file 02-C8-BBTEST.txt contains the results of the
   comparison.  If you see Differences = 0 towards the end of the file, then it
   means that your program's output matches the expected output. Otherwise, if
   you see a Differences value higher than 0, then there's a strong probability
   that you either have a logical error in your program, or you did NOT follow
   the MP specifications (including the directions in this file).

                Debug your C source file, and redo the steps above until you get
   Differences = 0.

                Take note, however, that Differences = 0 does NOT necessarily
   mean that your solutions is 100% logically correct.  The bbtest.exe only
   tests if two files have the same contents.  It is not meant to test the logic
                of your C program.

        4. TEST your solution using the stock historical data for other
   companies other than AMZN.txt.  Note that there are no expected output files
   provided for other companies.  You'll have to figure out how to verify the
           correctness of your program's output on your own.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
        TO DO: replace GROUPNUMBER in the #include below with your own group
   number.  For example if you are group 2, you should have #include "02-C6.h".
   Group numbers from 1 to 9 should have a leading zero in the filename.
*/
#include "05-C6.h"

// Do NOT edit/delete the next #include directive.
#include "C8.h"  // read and understand the contents of this file

/* Do NOT include other files. */

/*
        HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or
   CAUSE POINT DEDUCTIONS!

        1. You are required to use structures, arrays and strings concepts in
   solving Challenge #8.
        2. Segregate your program's logic into multiple functions.
   Non-compliance will result to a 5 point deduction for this Challenge.
        3. Document your codes with SENSIBLE comments.
        4. You are NOT allowed to use library functions that were NOT discussed
   in our subject.
*/

/*
        Do NOT define any constant in this file.
    Do NOT declare any typedef that you need below this comment.
        You should have them encoded instead in your GROUPNUMBER-C6.h header
   file.
*/

/*
    TO DO: Define ANY number of functions that you need below this comment.
   Unless otherwise specified explicitly, you are the one responsible in
   deciding what should be the function's a. return data type b. name c. formal
   parameters d. local variables and statements inside the body.

        You SHOULD write a SENSIBLE comment describing briefly what the function
   is supposed to accomplish BEFORE the function definition itself.
*/

/* GetCompanyCodeAndTotalRecords prints the company name and total number of
 * records */
void GetCompanyCodeAndTotalRecords(Stock* ptr_stock) {
  scanf("%s %d", ptr_stock->stockName, &ptr_stock->numRecords);
}

/* ProcessLine processes each line and formats the data in order */
void ProcessLine(Stock* ptr_strock, int i) {
  Shd* ptr_shd = &ptr_strock->shds[i];

  scanf("%s %lf %lf %lf %lf %lf", ptr_shd->date, &ptr_shd->ohlc.open,
        &ptr_shd->ohlc.high, &ptr_shd->ohlc.low, &ptr_shd->ohlc.close,
        &ptr_shd->volume);  // Formats the dates, ohlc values, and volume
                            // in order
}

/* ComputeAverageClose computes for the average of the closing values */
double ComputeAverageClose(Stock* ptr_stock, int startIndex, int endIndex) {
  double sum = 0;
  for (int i = startIndex; i <= endIndex; i++) {
    sum += ptr_stock->shds[i].ohlc.close;  // sum of all closing values
  }
  double average =
      sum / (endIndex - startIndex + 1);  // average of closing values
  return average;
}
/*
    TO DO: Implement a function that will read the stock historical data via
   scanf().  The actual data will be supplied via input redirection.

                   Fill in the blanks.  The first missing item is the function
   name, and the second one is the missing portion for the data type of formal
   parameter ptr_stock.  Take note that this function has ONE structure pointer
   formal parameter!
*/
void ReadStockHistoricalData(
    Stock* ptr_stock)  // do NOT change the parameter name
{
  /* Implement the body of this function.  Declare your own local variables. */
  int i;

  GetCompanyCodeAndTotalRecords(ptr_stock);  // display the company name and num
                                             // total records in data first

  for (i = 0; i < ptr_stock->numRecords; i++) {
    ProcessLine(ptr_stock,
                i);  // then process each line to format the data needed
  }
}

/*
    TO DO: Implement the function ComputeSignal().  Do not change function data
   type, function name and parameter names. Fill in the blank by supplying the
   missing portion portion for formal parameter ptr_stock. Take note that this
   function has TWO structure pointer parameters!
*/
void ComputeSignal(indicatorType* ptr_indicator, Stock* ptr_stock) {
  /* Implement the body of this function.  Declare your own local variables. */
  int mlt = ptr_indicator->mlt, mst = ptr_indicator->mst;
  ptr_indicator->count =
      ptr_stock->numRecords - mlt + 1;  // where the date starts

  for (int i = ptr_stock->numRecords - mlt, j = 0; i >= 0; i--, j++) {
    int endIndexMlt = i + (mlt - 1);
    int endIndexMst = i + (mst - 1);

    strcpy(ptr_indicator->SIGNAL[j].date,
           ptr_stock->shds[i].date);  // copying date from stock to signal
    ptr_indicator->SIGNAL[j].long_term_MA = ComputeAverageClose(
        ptr_stock, i, endIndexMlt);  // compute average close for long term MA
    ptr_indicator->SIGNAL[j].short_term_MA = ComputeAverageClose(
        ptr_stock, i, endIndexMst);  // compute average close for short term MA

    if (ptr_indicator->SIGNAL[j].short_term_MA >
        ptr_indicator->SIGNAL[j].long_term_MA) {
      ptr_indicator->SIGNAL[j].signal =
          'B';  // buy if the short term MA is higher than long term MA
    } else {
      ptr_indicator->SIGNAL[j].signal = 'S';  // otherwise it is a sell
    }
  }
}

/*
        TO DO: Complete the body of the main() function.
*/
int main() {
  /* Do NOT change the next two lines of variable declarations. */
  int i, j;
  indicatorType indicator;  // NOTE: study the file C8.h file -- it contains the
                            // declaration of indicatorType alias.

  /* Do NOT change the next line of array definition. View the C8.h header file
   * to see the values of the macros. */
  int test_cases[4] = {TEST_NDAYS1, TEST_NDAYS2, TEST_NDAYS3, TEST_NDAYS4};

  /*
          TO DO: Declare your own local structure variable that will the store
     the SHD for a company read from an input text file
  */
  Stock stock;  // supply the structure data type alias based on your C6
                // header file contents the structure variable name should
                // be stock -- don't change this!

  /* NOTE: The statements below should produce the required output. You are
     allowed to change or edit ONLY those lines with blanks by filling-up the
     missing information.

     Refer to the accompanying C8-EXPECTED.txt to see the expected results using
     AMZN.txt as input file.
  */

  /*
          TO DO: Fill in the blank by CALLing the function that you defined
     above for reading the stock historical data.
  */
  ReadStockHistoricalData(&stock);  // do NOT change the &stock parameter, do
                                    // NOT add other parameters

  /* TO DO: Fill in the blank to print the company symbol. */
  printf("%s\n", stock.stockName);

  /* TO DO: Fill in the blank to print the count/number of rows of stock
   * historical data. */
  printf("%d\n", stock.numRecords);
  printf("\n");

  /*
          except for the strcpy() below, DO NOT change any of the codes below.
  */
  for (i = 0; i < 3; i++) {
    /*
            TO DO: Fill in the blank to copy the stock symbol.
    */
    strcpy(indicator.symbol, stock.stockName);

    indicator.mst =
        test_cases[i];  // number of days for the short term SMA, ex. 50-day MA
    indicator.mlt =
        test_cases[i +
                   1];  // number of days for the long term SMA,  ex. 200-day MA

    ComputeSignal(&indicator,
                  &stock);  // call the function that you implemented

    // print the values computed by the student's solution
    printf("**TEST-CASE-%d**\n", i + 1);
    printf("mst = %d-days, mlt = %d-days\n", indicator.mst, indicator.mlt);
    printf("count = %d\n", indicator.count);
    for (j = 0; j < indicator.count; j++) {
      printf("%3d   %10s %10.2lf %10.2lf   ", j + 1, indicator.SIGNAL[j].date,
             indicator.SIGNAL[j].short_term_MA,
             indicator.SIGNAL[j].long_term_MA);
      if (indicator.SIGNAL[j].signal == 'B')
        printf("BUY\n");
      else if (indicator.SIGNAL[j].signal == 'S')
        printf("SELL\n");
      else
        printf("INCORRECT!\n");  // NOTE: there's a logical error in student
                                 // solution if this is printed!!!!
    }
    printf("\n\n");
  }

  return 0;
}
