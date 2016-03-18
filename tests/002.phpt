--TEST--
Test static binding for closures
--FILE--
<?php
$a = 1;
$first = true;
(function ($n) use ($a, &$b) {
    static $c;
    if ($GLOBALS['first']) {
        $GLOBALS['first'] = false;
        $b = 2;
        $c = 3;
    }
    var_dump(compact('a', 'b', 'c'));
    return $n <= 1 ? null : callee()($n - 1);
})(3);
?>
--EXPECT--
array(3) {
  ["a"]=>
  int(1)
  ["b"]=>
  &int(2)
  ["c"]=>
  &int(3)
}
array(3) {
  ["a"]=>
  int(1)
  ["b"]=>
  &int(2)
  ["c"]=>
  &int(3)
}
array(3) {
  ["a"]=>
  int(1)
  ["b"]=>
  &int(2)
  ["c"]=>
  &int(3)
}
