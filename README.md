# callee

Provide recursion system for anonymous closures.

## Requirements

PHP 7.x

## Installing

### Basic

```ShellSession
mpyw@localhost:~$ git clone git@github.com:mpyw/phpext-callee.git
mpyw@localhost:~$ cd phpext-callee
mpyw@localhost:~/phpext-callee $ /path/to/phpize
mpyw@localhost:~/phpext-callee $ ./configure --enable-callee --with-php-config=/path/to/php-config --prefix=/path/to/php-src
mpyw@localhost:~/phpext-callee $ make
mpyw@localhost:~/phpext-callee $ make install
mpyw@localhost:~/phpext-callee $ vim /path/to/php.ini
```

### [PHPBrew](https://github.com/phpbrew/phpbrew)

```ShellSession
mpyw@localhost:~$ phpbrew ext install git@github.com:mpyw/phpext-callee.git
```

## Usage

```php
<?php
var_dump((function ($n) {
    return $n < 2 ? 1 : $n * callee()($n - 1);
})(5));

// 5! = 5 * 4 * 3 * 2 * 1 = int(120)
```
