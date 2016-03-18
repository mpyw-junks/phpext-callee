
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend_closures.h"
#include "ext/standard/info.h"
#include "Zend/zend_generators.h"
#include "ext/standard/php_rand.h"

#include "php_callee.h"

PHP_FUNCTION(callee)
{
    zend_execute_data *ptr, *skip, *call = NULL;
    zend_object *object;
    zend_function *func;
    zend_string *function_name;

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    if (!(ptr = EG(current_execute_data))) {
        return;
    }
    if (!ptr->func || !ZEND_USER_CODE(ptr->func->common.type)) {
        call = ptr;
        ptr = ptr->prev_execute_data;
    }
    if (ptr) {
        /* skip debug_backtrace() */
        call = ptr;
        ptr = ptr->prev_execute_data;
        if (!call) {
            call = ptr;
            ptr = ptr->prev_execute_data;
        }
    }
    if (!ptr) {
        return;
    }

    /* $this may be passed into regular internal functions */
    object = call ? Z_OBJ(call->This) : NULL;

    if (call && call->func) {
        func = call->func;
        function_name = (func->common.scope &&
                         func->common.scope->trait_aliases) ?
            zend_resolve_method_name(
                (object ? object->ce : func->common.scope), func) :
            func->common.function_name;
    } else {
        func = NULL;
        function_name = NULL;
    }

    if (!function_name) {
        return;
    }

    if (object) {
        zval zv;
        Z_ADDREF(call->This);
        ZVAL_COPY_VALUE(&zv, &call->This);
        array_init(return_value);
        add_next_index_zval(return_value, &zv);
        add_next_index_str(return_value, zend_string_copy(function_name));
    } else if (func->common.scope) {
        array_init(return_value);
        add_next_index_str(return_value, zend_string_copy(func->common.scope->name));
        add_next_index_str(return_value, zend_string_copy(function_name));
    } else if (func->op_array.fn_flags & ZEND_ACC_CLOSURE) {
        zend_create_fake_closure(return_value, func, func->common.scope, func->common.scope, NULL);
    } else {
        RETURN_NEW_STR(function_name);
    }

}

PHP_MINFO_FUNCTION(callee)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "callee support", "enabled");
    php_info_print_table_end();
}

const zend_function_entry callee_functions[] = {
    PHP_FE(callee, NULL)
    PHP_FE_END
};

zend_module_entry callee_module_entry = {
    STANDARD_MODULE_HEADER,
    "callee",
    callee_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(callee),
    PHP_CALLEE_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CALLEE
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(callee)
#endif
