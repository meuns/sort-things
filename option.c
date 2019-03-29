#include "option.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int option_parse_command_line(int argc, char** argv, const char* long_option, const char* short_option, int default_value)
{
  const size_t long_length = strlen(long_option);
  const size_t short_length = strlen(short_option);

  for (int argument_index = 1; argument_index < argc; ++argument_index)
  {
    const char* argument = argv[argument_index];
    if (strncmp(argument, long_option, long_length) == 0)
    {
      errno = 0;
      long int value = strtol(&argument[long_length], NULL, 10);
      if (errno == 0)
      {
        return (int)value;
      }
    }

    if (strncmp(argument, short_option, short_length) == 0)
    {
      errno = 0;
      long int value = strtol(&argument[short_length], NULL, 10);
      if (errno == 0)
      {
        return (int)value;
      }
    }
  }

  return default_value;
}
