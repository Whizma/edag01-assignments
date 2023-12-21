#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N (10)

static void error(unsigned int line, int c, bool *err)
{
  char buf[3];

  if (c == '\n')
    strcpy(buf, "\\n");
  else
  {
    buf[0] = c;
    buf[1] = 0;
  }

  printf("line %u: error at %s\n", line, buf);

  *err = true;
}

int main(void)
{
  int stack[N], i, c, x;
  bool num, err;
  unsigned line;

  x = 0;
  i = 0;
  line = 1;
  num = false;
  err = false;

  while ((c = getchar() != EOF))
  {
    if (err)
    {
      if (c == '\n')
      {
        line++;
        err = 0;
        i = 0;
      }
      continue;
    }
    else if (isdigit(c))
    {
      x = x * 10 + c - '0';
      num = true;
      continue;
    }
    else if (num)
    {
      if (i == N)
      {
        error(line, '0' + x % 10, &err);
      }
      else
      {
        stack[i++] = x;
        num = false;
        x = 0;
      }
    }
    if (i >= 2)
    {
      switch (c)
      {
      case '+':
        stack[i - 2] = stack[i - 1] + stack[i - 2];
        i--;
        break;

      case '-':
        stack[i - 2] = stack[i - 2] - stack[i - 1];
        i--;
        break;

      case '*':
        stack[i - 2] = stack[i - 2] * stack[i - 1];
        i--;
        break;
      case '/': // behöver check för div med0;
        if (!(stack[i - 1] == 0))
        {
          stack[i - 2] = stack[i - 2] / stack[i - 1];
          i--;
        }
        else
        {
          error(line, c, &err);
        }
      }
    }
    return 0;
  }
}
