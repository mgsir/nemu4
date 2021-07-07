#include <isa.h>
#include<stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NUM

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"\\-", '-'},         
  {"\\*",'*'},
  {"\\/",'/'},
  {"\\(",'('},
  {"\\)",')'},
  {"==", TK_EQ},        // equal
  {"[0-9]*",TK_NUM},    // number
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32] ;
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        struct token temp;
        memset(temp.str,0,sizeof(temp.str));

        switch (rules[i].token_type)
        {
        case TK_NOTYPE:
          temp.type = TK_NOTYPE;
          assert(substr_len <= 31);
          strncpy(temp.str, e + position - substr_len, substr_len);
          break;
        case TK_EQ:
          temp.type = TK_EQ;
          strcpy(temp.str, "==");
          break;
        case '+':
          temp.type = '+';
          strcpy(temp.str, "+");
          break;
        case '-':
          temp.type = '-';
          strcpy(temp.str, "-");
          break;
        case '*':
          temp.type = '*';
          strcpy(temp.str, "*");
          break;
        case '/':
          temp.type = '/';
          strcpy(temp.str, "/");
          break;
        case '(':
          temp.type = '(';
          strcpy(temp.str, "(");
          break;
        case ')':
          temp.type = ')';
          strcpy(temp.str, ")");
          break;
        case TK_NUM:
          temp.type = TK_NUM;
          assert(substr_len <= 31);
          strncpy(temp.str, e + position - substr_len, substr_len);
        }

        tokens[nr_token++] = temp;

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool check_parentheses(char *e,uint32_t p, uint32_t q)
{
  if(e[p] != '(' || e[q] != ')') return false;

  for(uint32_t i = p+1; i < q; ++i){ if(e[i] == ')') return false; }
  return true;
}

uint32_t eval(char *e, uint32_t p,  uint32_t q)
{
  if(p > q)  assert(0);
  else if(p == q) return (uint32_t)strtol(e[p]+"",NULL,10);
  else if(check_parentheses(e,p,q) == true) return eval(e,p-1,q-1);
  else
  {

  }
  return 0;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

  return 0;
}
