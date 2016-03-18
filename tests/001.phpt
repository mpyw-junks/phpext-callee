--TEST--
Execute factorial closure
--FILE--
<?php
var_dump((function ($n) {
    return $n < 2 ? 1 : $n * callee()($n - 1);
})(10));
?>
--EXPECT--
int(3628800)
