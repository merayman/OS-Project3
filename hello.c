
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/mm.h>

#define DEFAULT  "\033[0m"
#define BOLD     "\033[1m"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omer Faruk Karakaya-Musab Erayman");
/* 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non−zero) at a later stage.
 */

#define next_task(p) \
	list_entry_rcu((p)->tasks.next, struct task_struct, tasks)

#define for_each_process(p) \
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )
pid_t processid;
module_param(processid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(int, "Some porcess ID");
static void print_mem(struct task_struct *task)
{
        struct mm_struct *mm;
        struct vm_area_struct *vma;
		
       
        int count = 0;
        mm = task->mm;
        pgd_t *pgd = mm->pgd;
        vma = mm->mmap;
        while(vma->vm_next){
        	vma= vma -> vm_next;
			}
		
        /*printk(KERN_INFO "\nThis mm_struct has %d vmas.\n", mm->map_count);
        for (vma = mm->mmap ; vma ; vma = vma->vm_next) {
                printk(KERN_INFO "\nVma number %d: \n", ++count);
                printk( KERN_INFO " Starts at 0x%lx, Ends at 0x%lx\n",
                          vma->vm_start, vma->vm_end);
        }*/
		printk(KERN_INFO BOLD "\nMEMORY INFO\n"DEFAULT);
        printk(KERN_INFO 
        		 "Virtual memory Starts= 0x%lx, end= 0x%lx size=%lu kB \n"
        		 "Code  Segment start = 0x%lx, end = 0x%lx, size=%lu kB\n"
                 "Data  Segment start = 0x%lx, end = 0x%lx, size=%lu kB\n"
                 "Argument  Segment start = 0x%lx, end = 0x%lx, size=%lu Bytes\n"
                 "Env  Segment start = 0x%lx, end = 0x%lx, size=%lu Bytes\n"
                 "Stack Segment start = 0x%lx, end = 0x%lx, size=%lu kB\n"
                 "Heap Segment start = 0x%lx, end = 0x%lx, size=%lu Bytes\n"
                 "number of frames used(VMRSS)= %lu \n"
                 "total vm pages used= %lu\n",
                 mm->start_code, vma->vm_end, mm->total_vm << (PAGE_SHIFT-10),/*vm info*/
                 mm->start_code, mm->end_code, (PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK)) >> 10,/*code info*/
                 mm->start_data, mm->end_data, mm->data_vm << (PAGE_SHIFT-10),/*data info*/
                 mm->arg_start, mm->arg_end, mm->arg_end - mm->arg_start,/*argument info*/
                 mm->env_start, mm->env_end, mm->env_end - mm->env_start,/*environment info*/
                 //vma->vm_end, vma->vm_start, vma->vm_end - vma->vm_start,
                 vma->vm_end, vma->vm_start, mm ->stack_vm << (PAGE_SHIFT-10),/*stack info*/
                 mm->start_brk, mm->brk, (mm->brk - mm->start_brk),/*heap info*/
                 ( get_mm_counter(mm, MM_ANONPAGES) + get_mm_counter(mm, MM_FILEPAGES)+ get_mm_counter(mm, MM_SHMEMPAGES) ),/*rss info*/
                 (PTRS_PER_PTE * sizeof(pte_t) * atomic_long_read(&mm->nr_ptes) * 512) >> 10/*total vm info*/);
                 
         //page tabel info//
         //printk(KERN_INFO "pgd_val = 0x%lx\n", pgd_val(*pgd));
         //printk(KERN_INFO "pagetable baseaddres: \n",
			//			pagetable
			//);
			int i = 0;
			printk(KERN_INFO BOLD"\nPAGE TABLE INFO\n"DEFAULT);
			while(i<512)
			{
				void *p_val = (void *)(pgd_val(pgd[i]));
				if( p_val == NULL )
					printk(KERN_INFO "PGD[%d]: %p\n",i,p_val);
				else{
					printk(KERN_INFO BOLD "\nPGD[%d]:" DEFAULT " 0x%p\t",i,p_val);
					printk(KERN_INFO BOLD"PGD[%d]:" DEFAULT "  Present: %d \t",i,((int)(p_val)&1));
					printk(KERN_INFO BOLD"PGD[%d]: " DEFAULT " Read\write: %d \t",i,((int)(p_val)&2) >>1);
					printk(KERN_INFO BOLD"PGD[%d]: " DEFAULT " User\Supervisor: %d \t",i,((int)(p_val)&4) >>2);
					printk(KERN_INFO BOLD"PGD[%d]: " DEFAULT " Write Through: %d \t",i,((int)(p_val)&8)>>3);
					printk(KERN_INFO BOLD"PGD[%d]:" DEFAULT "  Cache Disabled: %d \t",i,((int)(p_val)&16)>>4);
					printk(KERN_INFO BOLD"PGD[%d]:" DEFAULT "  Accessed: %d \t",i,((int)(p_val)&32)>>5);
					printk(KERN_INFO BOLD"PGD[%d]: " DEFAULT " Dirty: %d \t",i,((int)(p_val)&64)>>6);
					printk(KERN_INFO BOLD"PGD[%d]: " DEFAULT " Global: %d \n",i,((int)(p_val)&128)>>7);
					}
				i++;
			}
                 
}
static int __init hello_init(void)
{
        struct task_struct *task;
		struct task_struct *p;
		//struct task_struct *task_ptr = mytask;
		for_each_process(p)
		{
		   if(p->pid == processid)
		   	task = p;
		}
        print_mem(task);
        return 0;
}
static void __exit hello_exit(void)
{
        printk(KERN_INFO "Goodbye!\n\n");
}
module_init(hello_init);
module_exit(hello_exit);
