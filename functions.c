/******************************************************************************
 * @file: functions.c
 *
 * WISC NETID - rkumthekar
 * CANVAS USERNAME - Reva KUMTHEKAR
 * WISC ID NUMBER - 9082067217
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Reva Kumthekar (rkumthekar@wisc.edu)
 * @modified: 10/7/2021
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you
#define MAX_USERNAME_LEN 32
#define MAX_EMAIL_LEN 32
#define MAX_DOMAIN_LEN 64
#define MIN_PASSWORD_LEN 8
#define MAX_PASSWORD_LEN 16
#define NEW_LINE_CHAR 10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE
// Examples: IsLetter, IsDigit, Length, Find...

//a helper function to check if the character given, char a, is a letter [A-Z, a-z]
int IsLetter(char a)
{
    if((a > 64 && a < 91) || (a > 96 && a < 123))
    {
        return 1;
    }else{
        return 0;
    }
}

//a helper function to check if the character given, char a, is a digit [0-9]
int IsDigit(char n)
{
    if((n > 47 && n < 58))
    {
        return 1;
    }else{
        return 0;
    }
}

//a helper function to compare a pointer to an array and an array of chars, and then return 1 if they are equal and 0 if they are not equal
int isEqual(char *p, char arr[], int expected)
{
    int counter = 0;
    for(int i  = 0; arr[i] != 0; i++)
    {
        if(*p == arr[i])
        {
            p++;
            counter++;
            
        }
    }
    if(counter == expected)
    {
        return 1;
    }else{
        return 0;
    }
}

//a helper function to check if the character given, char a, is a period symbol '.'
int IsPeriod(char a)
{
    if(a == 46)
    {
        return 1;
    }else{
        return 0;
    }
}

//a helper function to determine the length of an array of characters and also make sure that the length is within the input buffer amount given
int Length(char arr[], size_t maxLen)
{
    //int counter = 0;
    for(int i  = 0; i < maxLen; i++)
    {
        if(arr[i] == 0)
        {
            return i;
        }
    }
    return maxLen;
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len)
{

    /* BEGIN MODIFYING CODE HERE */
    dbgprintf("This line only prints if DEBUG is set to 1\n");
    if(!IsLetter(user[0]))
    {
        printf(ERROR_01_USER_START_INVALID);
        return 0;
    }

    if(Length(user, len) > 32)
    {
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }

    int i = 0;
    //if the char in the username is a letter, a digit, or an underscore, then it should pass, else it should throw the error
    while(i < Length(user, len))
    {
        if( IsDigit(user[i]) || IsLetter(user[i]) || user[i] == 95)
        {
            i++;
        }else{
            printf(ERROR_03_USER_CHARS_INVALID);
            return 0;
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_1_USER);
    return 1;
}

/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len)
{

    /* BEGIN MODIFYING CODE HERE */
    if(email[0] == 64)
    {
        printf(ERROR_04_EMAIL_MISSING_NAME); // example @domain.com
        return 0;
    }
    if(!IsLetter(email[0]))
    {
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }
    
    //This is creating a pointer to the @ symbol and the end of the char array, which should be the null terminating character
    char *at_pointer = email; 
    char *end_pointer = &email[Length(email, len)];
    for(int i = 0; i < Length(email, len); i++)
    {
        if(email[i] == 64)
        {
            at_pointer = &email[i];
            break;
        }
    }

    for(int i = 0; i < Length(email, len); i++)
    {
        if(email[i] == 0)
        {
            end_pointer = &email[i];
        }
    }

    
    //if the @ symbol pointer is still at the beginning of the loop from where we set it above, 
        // then that means the symbol doesn't exist, and then set it to the end of the array
    if(at_pointer == email)
    {
        at_pointer = &email[Length(email, len)];
    }
    

    //This is creating the pointer to the top level domain
    char *last_four = end_pointer - 4;
    char comArray[5] = ".com";
    char eduArray[5] = ".edu";
    char netArray[5] = ".net";

    
    //if the last four characters of the array match one of the possible top level domains, then set the pointer to there, 
        //otherwise set the pointer to the end of the array
    if(isEqual(last_four, comArray, 4) || isEqual(last_four, eduArray, 4) || isEqual(last_four, netArray, 4))
    {
        last_four = end_pointer - 4;
    }else{
        last_four = end_pointer;
    }
    
    int name_to_tld = 0;
    int name_length = 0;
    //if the @ symbol doesn't exist, treating the name from the start of the array to top-level-domain
    if(at_pointer == end_pointer)
    {
        
        //if tld doesn't exist
        if(last_four == end_pointer)
        {
            name_to_tld = Length(email, len);
        }else{ 
            name_to_tld = Length(email, len) - 4;
        }
        if(name_to_tld > 32)
        {
            printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
            return 0;
        }
    }else{
        //if the @ symbol does exist, then check the length from the start of the array to the @ symbol
        name_length = at_pointer - email;
        if(name_length > 32)
        {
            printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
            return 0;
        }
    }

    //if the @ symbol doesn't exist, then we are checking the start of the array to the top level domain
    if(at_pointer == end_pointer)
    {
        for(int i  = 0; i < name_to_tld; i++)
        {
            if(!IsLetter(email[i]) && !IsDigit(email[i]))
            {
                printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
                return 0;
            }
        }
    }

    //if the @ symbol does exist, treating the name up until the @ symbol to check for the invalid characters
    for(int i = 0; i < name_length; i++)
    {
        if((IsLetter(email[i]) + IsDigit(email[i])) == 0)
        {
            printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
            return 0;
        }
    }
    
    //if the @ symbol's pointer is at the end of the array, that means it doesn't exist
    if(at_pointer == end_pointer)
    {
        printf(ERROR_08_EMAIL_MISSING_SYMBOL);
        return 0;
    }

    //if the @ symbol's pointer's next character is equal to the top level domain's pointer, then the domain is missing
    if(at_pointer+1 == last_four)
    {
        printf(ERROR_09_EMAIL_MISSING_DOMAIN); // example mike@.edu
        return 0;
    }

    int domain_len = last_four - (at_pointer+1);
    if(domain_len > 64)
    {
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }
    
    //an if statement to check if the character directly after the @ symbol is a valid start to the domain
    if(!IsLetter(*(at_pointer+1)))
    {
       printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
       return 0; 
    }
    //a for loop that starts from the char next to @ symbol and up to the top level domain to check for an invalid start to a subdomain
    for(char *i = at_pointer+1; i < last_four; i++)
    {
        if(*i == '.')
        {
            if(i == (end_pointer-1))
            {
                break;
            }
            if(!IsLetter(*(i+1)))
            {
              printf(ERROR_11_EMAIL_DOMAIN_START_INVALID); 
              return 0; 
            }
        }
    }

    //a for loop that starts from the char next to @ symbol and up to the top level domain to check for any invalid character within the subdomains
    for(char *i = at_pointer + 1; i < last_four; i++)
    {
        if((IsLetter(*i) + IsDigit(*i) + IsPeriod(*i)) == 0)
        {
            printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID); 
            return 0; 
        }
        
    }
    
    //if the top level domain's pointer is equal to the end pointer then that means the top level domain was not valid
    if(last_four == end_pointer)
    {
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }
    
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len)
{
    /* BEGIN MODIFYING CODE HERE */
    //a for loop to go through the password to make sure there are no spaces
    for(int i = 0; i < Length(pwd, len); i++)
    {
        if(pwd[i] == 32)
        {
            printf(ERROR_14_PWD_SPACES_INVALID);
            return 0;
        }
    }
    
    if(Length(pwd, len) < 8)
    {
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }
    if(Length(pwd, len) > 16)
    {
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }
    
    int upperCount = 0;
    // a for loop that goes through the password to make sure there is at least 1 Uppercase character
    for(int i = 0; i < Length(pwd, len); i++)
    {
        if(pwd[i] > 64 && pwd[i] < 91)
        {
            upperCount++;
        }
    }
    if(upperCount < 1)
    {
         printf(ERROR_17_PWD_MIN_UPPER_INVALID);
         return 0;
    }
   
    int lowerCount = 0;
    // a for loop that goes through the password to make sure there is at least 1 Lowercase character
    for(int i = 0; i < Length(pwd, len); i++)
    {
        if(pwd[i] > 96 && pwd[i] < 123)
        {
            lowerCount++;
        }
    }
    if(lowerCount < 1)
    {
         printf(ERROR_18_PWD_MIN_LOWER_INVALID);
         return 0;
    }
    
    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2)
{

    /* BEGIN MODIFYING CODE HERE */

    if(!isEqual(pwd1, pwd2, Length(pwd1, len1)))
    {
        printf(ERROR_19_PWD_MATCH_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */

void Get_User_Data(char *message, char *data, const int MAX_LENGTH)
{
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */

    //replacing the newline character with a null terminating character
    for(int i = 0; i < Length(data, MAX_LENGTH); i++)
    {
        if(data[i] == '\n')
        {
            data[i] = '\0';
        }
    }
    /* END MODIFYING CODE HERE */
    return;
}