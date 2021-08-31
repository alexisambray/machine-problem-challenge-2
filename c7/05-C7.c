/*
    Do NOT forget to encode your name, section and date of submission.

    LASTNAME1, FIRSTNAME1:  AMBRAY, ALEXIS               SECTION: S13
    LASTNAME2, FIRSTNAME2:  MUROS, DON DAVID             SECTION: S11

    DATE SUBMITTED     :  August 24, 2021

        Make sure that you do the following:

        1. COMPILE your C source code with -Wall directive.

               Example: CCPROG2> gcc -Wall 02-C7.c -o 02-C7.exe

           where 02 is an example group number and C7 is the Challenge number.

           You must replace 02 with your own group number!

        2. RUN the program's exe file in the command line with input and output
   (I/O) redirection.

                        Example: CCPROG2> 02-C7 < AMZN.txt > 02-C7-OUTPUT.txt

       The text file 02-C7-OUTPUT.txt will contain the actual output of your
   program.

    3. COMPARE your program's output your program with the accompanying
   C7-EXPECTED.txt file using bbtest.c.

            In case you do not have bbtest.exe, produce it first by compiling
   bbtest.c as shown below:

                        Example: CCPROG2> gcc -Wall bbtest.c -o bbtest.exe

                Thereafter, run bbtest.exe with I/O redirection as shown below:

                        Example: CCPROG2> bbtest C7-EXPECTED.txt
   02-C7-OUTPUT.TXT > 02-C7-BBTEST.txt

                The output file 02-C7-BBTEST.txt contains the results of the
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

// Do NOT edit/delete the next two #include directives.
#include "C7.h"            // read and understand the contents of this file
#include "numeric_date.c"  // read and understand the contents of this file

/* Do NOT include other files. */

/*
        HARD REQUIREMENTS: NON-COMPLIANCE WILL MAKE YOUR SOLUTION INCORRECT or
   CAUSE POINT DEDUCTIONS!

        1. You are required to use structures, arrays and strings concepts in
   solving Challenge #7.
        2. Segregate your program's logic into multiple functions.
   Non-compliance will result to a 5 point deduction for this Challenge.
        3. Document your codes with SENSIBLE comments.
        4. You are NOT allowed to use library functions that were NOT discussed
   in our subject.
*/

/*
    Do NOT define any constant in this file.
    Do NOT declare any typedef that you need below this comment.
        You should encoded #define and typedef declarations in your
   GROUPNUMBER-C6.h header file.
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
void ProcessLine(Stock* ptr_stock, int i) {
  Shd* ptr_shd =
      &ptr_stock->shds[i];  // assigns index the of shds to a pointer variable
  scanf(
      "%s %lf %lf %lf %lf %lf", ptr_shd->date, &ptr_shd->ohlc.open,
      &ptr_shd->ohlc.high, &ptr_shd->ohlc.low, &ptr_shd->ohlc.close,
      &ptr_shd->volume);  // formats the dates, ohlc values, and volume in order
}

/* BinarySearch searches the stock historical data corresponding to the buy and
 * sell dates */
int BinarySearch(StrDate key, Shds shds, int totalRecords) {
  int low = 0, high = totalRecords - 1, mid;

  while (low <= high) {
    mid = low +
          (high - low) / 2;  // divides the array into half on every iteration
    if (numeric_date(key) == numeric_date(shds[mid].date)) {  // if found
      return mid;
    } else if (numeric_date(key) > numeric_date(shds[mid].date)) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

/* profitOrLoss returns the value of a profit per share a stock was sold */
double profitOrLoss(int indexBuy, int indexSell, Stock* ptrStock) {
  return ptrStock->shds[indexSell].ohlc.close -
         ptrStock->shds[indexBuy]
             .ohlc.close;  // subtract buying price from selling price
}

/* percentProfitOrLoss computes the percentage of the profit or loss */
double percentProfitOrLoss(int indexBuy, int indexSell, Stock* ptrStock) {
  double profitOrLossValue = profitOrLoss(
      indexBuy, indexSell,
      ptrStock);  // assigns profitOrLoss function to profitOrLossValue

  return profitOrLossValue / ptrStock->shds[indexBuy].ohlc.close * 100;
}

/* displayTradeOutput displays whether the Trade output is found or not */
void displayTradeOutput(int indexBuy,
                        int indexSell,
                        StrDate buy_date,
                        StrDate sell_date,
                        Stock* ptrStock) {
  if (indexBuy != -1) {  // if index of buy date and buy price is found
    printf("BUY DATE %s FOUND IN INDEX %d! BUY PRICE = %.2lf\n", buy_date,
           indexBuy, ptrStock->shds[indexBuy].ohlc.close);
  } else {
    printf("BUY DATE %s NOT FOUND!\n", buy_date);
  }

  if (indexSell != -1) {  // if index of sell date and sell price is found
    printf("SELL DATE %s FOUND IN INDEX %d! SELL PRICE = %.2lf\n", sell_date,
           indexSell, ptrStock->shds[indexSell].ohlc.close);
  } else {
    printf("SELL DATE %s NOT FOUND!\n", sell_date);
  }

  if (indexBuy != -1 && indexSell != -1) {  // if both indexes are found
    printf("P/L = %.2lf\n",
           profitOrLoss(indexBuy, indexSell,
                        ptrStock));  // display the value of a profit per share
                                     // a stock was sold
    printf("%%P/L = %.2lf\n",
           percentProfitOrLoss(
               indexBuy, indexSell,
               ptrStock));  // display the percentage of the profit or loss
  }
}
/*
    TO DO: Implement a function that will read the stock historical data via
   scanf().  The actual data will be supplied via input redirection.

                   Fill in the blanks.  The first missing item is the function
   name, and the second one is the missing portion for the data type of formal
   parameter ptr_stock.  Take note that this function has ONE structure pointer
   formal parameter!
*/
void ReadStock(Stock* ptr_stock)  // do NOT change the parameter name
{
  /* Implement the body of this function.  Declare your own local variables. */
  int i;

  GetCompanyCodeAndTotalRecords(
      ptr_stock);  // display company name and number of records first

  for (i = 0; i < ptr_stock->numRecords; i++) {
    ProcessLine(ptr_stock,
                i);  // process each line with the data
  }
}

/*
    TO DO: Implement the Trade() function.  Do NOT change the return type,
   function name, and formal parameter names. Fill in the blank by supplying the
   data type of the formal parameter named as ptr_stock. Take note that this
   function has ONE structure pointer formal parameter!
*/
void Trade(StrDate buy_date, StrDate sell_date, Stock* ptrStock) {
  /* Implement the body of this function.  Declare your own local variables. */
  /*
              IMPORTANT: The Trade() function must call a binary search function
     twice. The first time is to search the buy_date. The second time is to
     search the sell_date.
      */
  int indexBuy = BinarySearch(buy_date, ptrStock->shds, ptrStock->numRecords);
  int indexSell = BinarySearch(sell_date, ptrStock->shds, ptrStock->numRecords);

  displayTradeOutput(indexBuy, indexSell, buy_date, sell_date, ptrStock);
}

/*
        TO DO: Complete the body of the main() function.
*/
int main() {
  /* Do NOT change the next line of variable declaration. */
  int i;

  /* Do NOT change the next two line of array definition. View the C7.h header
   * file to see the values of the macros. */
  StrDate buy_date[6] = {TEST_BUYDATE1, TEST_BUYDATE2, TEST_BUYDATE3,
                         TEST_BUYDATE4, TEST_BUYDATE5, TEST_BUYDATE6};
  StrDate sell_date[6] = {TEST_SELLDATE1, TEST_SELLDATE2, TEST_SELLDATE3,
                          TEST_SELLDATE4, TEST_SELLDATE5, TEST_SELLDATE6};

  /*
          TO DO: Declare your own local structure variable that will the store
     the SHD for a company read from an input text file
  */
  Stock stock;  // supply the structure data type alias based on your C6 header
                // file contents the structure variable name should be stock --
                // don't change this!

  /* NOTE: The statements below should produce the required output. You are
     allowed to change or edit ONLY those lines with blanks by filling-up the
     missing information.

     Refer to the accompanying C7-EXPECTED.txt to see the expected results using
     AMZN.txt as input file.
  */

  /*
          TO DO: Fill in the blank by CALLing the function that you defined
     above for reading the stock historical data.
  */
  ReadStock(&stock);  // do NOT change the &stock parameter, do NOT
                      // add other parameters

  /* TO DO: Fill in the blank to print the company symbol. */
  printf("%s\n", stock.stockName);

  /* TO DO: Fill in the blank to print the count/number of rows of stock
   * historical data. */
  printf("%d\n", stock.numRecords);
  printf("\n");

  /*
          DO NOT change any of the codes below.
  */
  for (i = 0; i < 6; i++) {
    printf("**TEST-CASE-%d**\n", i + 1);  // there are 6 test cases
    Trade(buy_date[i], sell_date[i],
          &stock);  // you'll need to implement the Trade() function
    printf("\n");
  }

  return 0;
}
