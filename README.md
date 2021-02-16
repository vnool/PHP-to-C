# PHP-to-C
 
BinaryPHP is a PHP To C++ converter, which will convert PHP scripts into C++ equivalents ready to be compiled using any ANSI compiler.


## DEPENDS
  * PHP (cli-sapi)
  
  Tested using 4.X series of the CLI sapi

  * C++ compiler
  
  Tested with: GNU g++ 2.9.5 and 3.0.4 and some unknown version of MSVC++


## BUILDING

  None Needed


## USAGE

  convert.php --if <inputfile.php> --of <output> [-v | --verbose] [-h | --help]

  Included Examples:
  
    ./convert.php --if examples/irc.php --of ircbot
    ./convert.php --if examples/helloworld.php --of hello


## CHANGELOG

  see [ChangeLog](DOCS/ChangeLog)
  

### refer to

+ http://rosecompiler.org/
+ https://github.com/facebook/hhvm
 
