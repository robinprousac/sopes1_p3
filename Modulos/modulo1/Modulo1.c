#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
    
//#include <linux-5.1.15.arch1/stdio.h> //probando otra ruta jeje
#include <linux/string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>
//#include <sys/inotify.h>
#include <linux/inotify.h>
//#include <limits.h>
#include <linux/limits.h>


#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*buffer to store the data of events*/
 

	

    static int __init inicio_mod(void)
    {
		//Este metodo escribe el archivo en la carpeta PROC
        printk(KERN_INFO "Maria Soledad De Leon Lopez.\n");
        //proc_create("201114565_file", 0, NULL, &meminfo_proc_fops);
        int length, i = 0, wd;
        int fd;
        char buffer[BUF_LEN];
        
        printf("carne : 201114565 \n");
        printf("Nombre : Maria Soledad De Leon Lopez\n");
        /* Initialize Inotify*/
        fd = inotify_init();
        if ( fd < 0 ) {
            printf("Couldn't initialize inotify");
        }
        
        /* add watch to starting directory */
        wd = inotify_add_watch(fd, "/home/u201114565", IN_CREATE | IN_MODIFY | IN_DELETE); 
        
        if (wd == -1)
            {
            printf("Couldn't add watch to %s\n","/home/u201114565");
            }
        else
            {
            printf("Watching:: %s\n","/home/u201114565");
            }
        
        /* do it forever*/
        while(1)
            {
            i = 0;
            length = read(fd, buffer, BUF_LEN );  
        
            if ( length < 0 ) {
                perror( "read" );
            }  
        
            while ( i < length ) {
                struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
                if ( event->len ) {
                if ( event->mask & IN_CREATE) {
                    if (event->mask & IN_ISDIR)
                    printf("The directory %s was Created.\n", event->name );       
                    else
                    printf("The file %s was Created with WD %d\n", event->name, event->wd );       
                }
                
                if ( event->mask & IN_MODIFY) {
                    if (event->mask & IN_ISDIR)
                    printf("The directory %s was modified.\n", event->name );       
                    else
                    printf("The file %s was modified with WD %d\n", event->name, event->wd );       
                }
                
                if ( event->mask & IN_DELETE) {
                    if (event->mask & IN_ISDIR)
                    printf("The directory %s was deleted.\n", event->name );       
                    else
                    printf("The file %s was deleted with WD %d\n", event->name, event->wd );       
                }  
        
        
                i += EVENT_SIZE + event->len;
                }
            }
            }
        
            /* Clean up*/
            inotify_rm_watch( fd, wd );
            close( fd );
            
            return 0;
    }

	static void __exit final_mod(void)
    {   
		//Este metodo sale del modulo
        printk(KERN_INFO "Sistemas operativos 1.\n");
        //remove_proc_entry("201114565_file",NULL);
    }

    module_init(inicio_mod);
    module_exit(final_mod);

	MODULE_LICENSE("GPL");
