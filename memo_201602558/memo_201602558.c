#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sysinfo.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/swap.h>


static int open_action(struct seq_file *m, void *v){
 struct sysinfo i;
 si_meminfo(&i);
 long available ;
 available = si_mem_available();
 seq_printf(m,"Carnet - 201602558 \n");
 seq_printf(m,"Nombre - Franklin Velasquez \n");
 seq_printf(m,"Sistema Operativo: Fedora \n");
 seq_printf(m,"Memoria Total: %lu KB \n", i.totalram*4);
 seq_printf(m,"Memoria Libre: %lu KB \n",i.freeram * 4);
 seq_printf(m,"Usado : %lu KB  \n", i.totalram*4 -i.freeram*4);

 return 0;
}


ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp){
 return 0;
}

int open_proc(struct inode *inode, struct file *file){
  return single_open(file, open_action , NULL);
}


static struct file_operations proc_fops = {
 read : seq_read,
 write : write_proc,
 open : open_proc,
 release : single_release,
 llseek : seq_lseek
};


static int __init memo_201602558_init(void) {
 printk(KERN_INFO "Carnet - 201602558 \n");

 struct proc_dir_entry *entry;
 entry = proc_create("memo_201602558",0777,NULL,&proc_fops); 

 if (!entry){
   return -1;
 } 


 return 0;
}

static void __exit memo_201602558_exit(void) {
 printk(KERN_INFO "Curso - Sistemas Operativos 1\n");
 remove_proc_entry("memo_201602558",NULL);
}

module_init(memo_201602558_init);
module_exit(memo_201602558_exit);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franklin Velasquez");
MODULE_DESCRIPTION("Memo");
MODULE_VERSION("0.01");

