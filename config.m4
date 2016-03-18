PHP_ARG_ENABLE(callee, whether to enable callee support,
[  --enable-callee           Enable callee support])

if test "$PHP_CALLEE" != "no"; then
    PHP_NEW_EXTENSION(callee, callee.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
