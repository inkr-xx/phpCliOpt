Simple tool to manage PHP command line script options and get info about possible options and their values.

See example.php for script side usage.

Supoorted are optinons in "o" and "-o" style and order of options is not fixed.

Correct usage:
> php example.php id 4432 debug d 2012-10-10 e info@email.com
or
> php example.php -id 4432 -d 2012-10-10 -e info@email.com debug

See possible options:
> php example.php help
        help [optional] Show help
        debug (bool) [optional] Show debugging data
        id (int) Object ID
        d (date) [optional] Time to last trip
        e [optional] Email to send result
        
Mandatory option "id" is not set:
> php example.php
  Parameter id value must be set
        help [optional] Show help
        debug (bool) [optional] Show debugging data
        id (int) Object ID
        d (date) [optional] Time to last trip
        e [optional] Email to send result

> php example.php id 4432 d 2012-10-32
Parameter d value must be date with format Y-m-d
        help [optional] Show help
        debug (bool) [optional] Show debugging data
        id (int) Object ID
        d (date) [optional] Time to last trip
        e [optional] Email to send result
